#include "LShape.h"
#include "vector"
#include "lsystem/LSystemGenerator.h"

#define M_SHAPE_P1 10
#define M_SHAPE_P2 10

#define UP_THETA (float) M_PI/4
#define LEFT_THETA (float)M_PI/4
#define H_THETA (float) M_PI/2
#define D_LENGTH (float)1.0f
#define D_WIDTH (float)1.0f

LShape::LShape(std::string rules,
               std::vector<CS123SceneMaterial> materials,
               GLuint vertexAttribIndex,
               GLuint normalAttribIndex,
               GLuint texCoordAttribIndex) :
    m_vertexIndex(vertexAttribIndex),
    m_normalIndex(normalAttribIndex),
    m_texCoordIndex(texCoordAttribIndex)

{
    m_current_state = new state();
    m_state_stack = std::list<state *>();
    m_shapes = std::vector<LMaterialShape*>();

    // the number of openglshapes to work with
    int numMaterials = materials.size();

    // init the shapes
    for (CS123SceneMaterial m : materials) {
        m_shapes.push_back(new LMaterialShape(m));
    }

    //*********BEGIN PARSING RULES***********\\

    // loop through the rules and execute each
    for(char& command : rules) {
        glm::mat4x4 ctm2 = glm::mat4x4(1.0);
        switch(command){
        case 'F':
            //adds a geometric representation of the current state to the appropriate openglshape in m_shapes
            addStateToShape(m_current_state->materialIdx);
            ctm2 *= glm::translate(glm::mat4x4(1.0), glm::vec3(0, m_current_state->length, 0));
        break;
        case 'f':
            //move forward
            ctm2 *= glm::translate(glm::mat4x4(1.0), glm::vec3(0, m_current_state->length,0));
        break;
        case '+':
            //turn left by UP_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), UP_THETA, m_current_state->up);
        break;
        case '-':
            //turn right by -UP_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), -UP_THETA, m_current_state->up);
        break;
        case '&':
            // pitch down by LEFT_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), LEFT_THETA, m_current_state->left);
        break;
        case '^':
            // pitch up by LEFT_THETA
             ctm2 *= glm::rotate(glm::mat4x4(1.0), -LEFT_THETA, m_current_state->left);
        break;
        case '\\':
            // roll left by H_THETA
             ctm2 *= glm::rotate(glm::mat4x4(1.0), H_THETA, m_current_state->heading);
        break;
        case '/':
            // roll right by -H_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), -H_THETA, m_current_state->heading);
            //m_current_state->left = glm::rotate(m_current_state->left, -H_THETA, m_current_state->heading);
            //m_current_state->up = glm::rotate(m_current_state->up, -H_THETA, m_current_state->heading);
        break;
        case '|':
            // rotate 180ºaround up.

            //lmao can't definte M_PI/float because it makes it a double
            ctm2 *= glm::rotate(glm::mat4x4(1.0),(float) M_PI, m_current_state->up);
            //m_current_state->heading = glm::rotate(m_current_state->heading, (float)M_PI, m_current_state->up);
            //m_current_state->left = glm::rotate(m_current_state->left, (float) M_PI, m_current_state->up);
        break;
        case '"':
            // increase length by D_LENGTH
            m_current_state->length += D_LENGTH;
        break;
        case '!':
             // increase width by D_WIDTH
            m_current_state->width += D_WIDTH;
        break;
        case '`':
            // decrease length by D_LENGTH
            m_current_state->length -= D_LENGTH;
        break;
        case '~':
            // decrease width by D_WIDTH
            m_current_state->width -= D_WIDTH;
        break;
        case '<':
            // increment the materialIdx (material selection is handled by the lsystem generator)
            // loop around at the ends
            m_current_state->materialIdx++;
            if (m_current_state->materialIdx > numMaterials - 1){
                m_current_state->materialIdx = 0;
            }
        break;
        case '>':
            // decrement the materialIdx
            m_current_state->materialIdx--;

            if (m_current_state->materialIdx < 0){
                m_current_state->materialIdx = numMaterials-1;
            }
        break;
        case '[': {
            // push the current state onto the stack, make a new state starting from here
            glm::mat4x4 old_ctm = m_current_state->ctm;
            m_state_stack.push_front(m_current_state);
            m_current_state = new state(m_current_state);
        }
        break;
        case ']':
            // pop the state stack and set to the current state
            if (m_state_stack.empty()) {
                cout << "LShape: attempted to pop from empty stack" << endl;
            } else {
                m_current_state = m_state_stack.back();
                m_state_stack.pop_back();
            }
        break;
        default:
        break;
        }
        // update the current state's ctm
        m_current_state->ctm *= ctm2;
    }
    //*********END PARSING RULES***********\\

    // pass to opengl, now ready to call draw()
    prepareShapes();

}

LShape::~LShape() {
    for (state * s : m_state_stack){
        delete s;
    }
    m_state_stack.clear();
    for (LMaterialShape *s : m_shapes){
        delete s;
    }
    m_shapes.clear();
}

// add the geometery for the current state to the appropriate shape
void LShape::addStateToShape(int materialIdx){
    LMaterialShape *lmshape = m_shapes.at(materialIdx);
    // get the triangles for the new shape
    std::vector<triangle *> newTris = getCylinder(m_current_state->length, m_current_state->width);

    // store the combined triangles in the LMaterialShape
    std::vector<triangle *> combinedTris;
    combinedTris.reserve(lmshape->m_triangles.size() + newTris.size()); // preallocate memory
    combinedTris.insert(combinedTris.end(), lmshape->m_triangles.begin(), lmshape->m_triangles.end() );
    combinedTris.insert(combinedTris.end(), newTris.begin(), newTris.end());
    lmshape->m_triangles = combinedTris;
    // can't believe ^ is how you combine two vectors...
}


// returns the triangles for the cylinder representation of the current state
std::vector<triangle *> LShape::getCylinder(float length, float width) {
    std::vector<triangle *> triangles = std::vector<triangle *>();
    double angleStep = 2 * (M_PI / M_SHAPE_P1);
    double stackStep = 2 * length / M_SHAPE_P2;
    float u1,v1,u2,v2,u3,v3;

    float dRad = angleStep;

    glm::vec3 center = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 left = glm::vec3(0.0f, 0.5f, 0.5f);
    glm::vec3 norm = glm::vec3(0.0f, 1.0f, 0.0f);
    for (int i = 0 ; i < M_SHAPE_P1; i++) {
        glm::vec3 right = glm::rotateY(left, dRad);
        GLfloat uL = 0.5f + left.x;
        GLfloat vL = 0.5f + left.z;

        GLfloat uR = 0.5f + right.x;
        GLfloat vR = 0.5f + right.z;

        GLfloat uC = 0.5f;
        GLfloat vC = 0.5f;

        // top and bottom first
        double topx1 = cos(angleStep * i) * width;
        double topy1 = length;
        double topz1 = sin(angleStep * i) * width;
        u1 = 0;
        v1 = 0;

        double topx2 = cos(angleStep * (i+1)) * width;
        double topy2 = length;
        double topz2 = sin(angleStep * (i+1)) * width;
        u2 = 0;
        v2 = 0;

        double topx3 = 0;
        double topy3 = length;
        double topz3 = 0;
        u3 = 0;
        v3 = 0;

        normal *topn1 = new normal(0, 1, 0);
        normal *topn2 = new normal(0, 1, 0);
        normal *topn3 = new normal(0, 1, 0);

        normal *botn1 = new normal(0, -1, 0);
        normal *botn2 = new normal(0, -1, 0);
        normal *botn3 = new normal(0, -1, 0);

        vertex *topv1 = new vertex(topx1, topy1, topz1, topn1, u1, v1);
        vertex *topv2 = new vertex(topx2, topy2, topz2, topn2, u2, v2);
        vertex *topv3 = new vertex(topx3, topy3, topz3, topn3, u3, v3);

        vertex *botv1 = new vertex(topx1, -topy1, topz1, botn1, u1, v1);
        vertex *botv2 = new vertex(topx2, -topy2, topz2, botn2, u2, v2);
        vertex *botv3 = new vertex(topx3, -topy3, topz3, botn3, u3, v3);

        triangles.push_back(new triangle(topv3, topv2, topv1, m_current_state->ctm));
        triangles.push_back(new triangle(botv1, botv2, botv3,  m_current_state->ctm));

        left = right;
    }

        // tesselate the sides
     for (int i = 0 ; i < M_SHAPE_P1; i++) {

        float a1 = i * stackStep;
        float a2 = (i + 1) * stackStep;
        GLfloat vMin = 1.f - static_cast<float>(i+1)/M_SHAPE_P2;
        GLfloat vMax = 1.f - static_cast<float>(i)/M_SHAPE_P2;

        glm::vec3 ul = glm::vec3(0.0f,   a2, width);
        glm::vec3 bl = glm::vec3(0.0f,   a1, width);
        glm::vec3 lN = glm::vec3(0.0f, 0.0f, 1.0f);

        for (int j = 0; j < M_SHAPE_P2; j++) {

            glm::vec3 ur = glm::rotateY(ul, dRad);
            glm::vec3 br = glm::rotateY(bl, dRad);
            glm::vec3 rN = glm::rotateY(lN, dRad);

            GLfloat uMin = static_cast<float>(j)/M_SHAPE_P2;
            GLfloat uMax = static_cast<float>(j+1)/M_SHAPE_P2;

            normal *n1 = new normal(lN.x, lN.y, lN.z);
            normal *n2 = new normal(rN.x, rN.y, rN.z);
            normal *n3 = new normal(rN.x, rN.y, rN.z);

            normal *n4 = new normal(lN.x, lN.y, lN.z);
            normal *n5 = new normal(rN.x, rN.y, rN.z);
            normal *n6 = new normal(lN.x, lN.y, lN.z);

            vertex *vert1 = new vertex(ul.x, ul.y, ul.z, n1, uMin, vMin);
            vertex *vert2 = new vertex(ur.x, ur.y, ur.z, n2, uMax, vMin);
            vertex *vert3 = new vertex(br.x, br.y, br.z, n3, uMax, vMax);

            vertex *vert4 = new vertex(bl.x, bl.y, bl.z, n4, uMin, vMax);
            vertex *vert5 = new vertex(br.x, br.y, br.z, n5, uMax, vMax);
            vertex *vert6 = new vertex(ul.x, ul.y, ul.z, n6, uMin, vMin);

            // apply the transformation for this state to the triangles
            triangles.push_back(new triangle(vert3, vert2, vert1, m_current_state->ctm));
            triangles.push_back(new triangle(vert4, vert5, vert6, m_current_state->ctm));

            ul = ur;
            bl = br;
            lN = rN;
        }
    }
    return triangles;
}

// go from triangles to vertexData for OpenGLShape to consume.
void LShape::prepareShapes(){

    int vertexSize = sizeof(GLfloat) * 3; // *dimensions
    int texSize = sizeof(GLfloat) * 2; //*texcoords
    int stride = 2 * vertexSize + texSize;
    int posn = 0;
    for (LMaterialShape *lmshape : m_shapes) {
        float numVerts = lmshape->m_triangles.size() * 3;
        int dataSize = numVerts * stride;
        GLfloat vertexData[dataSize];
        for (int i = 0; i < lmshape->m_triangles.size(); i++) {
             triangle* tri = lmshape->m_triangles[i];
             vertexData[posn++] = tri->v1->x;
             vertexData[posn++] = tri->v1->y;
             vertexData[posn++] = tri->v1->z;
             vertexData[posn++] = tri->v1->n->x;
             vertexData[posn++] = tri->v1->n->y;
             vertexData[posn++] = tri->v1->n->z;
             vertexData[posn++] = tri->v1->u;
             vertexData[posn++] = tri->v1->v;

             vertexData[posn++] = tri->v2->x;
             vertexData[posn++] = tri->v2->y;
             vertexData[posn++] = tri->v2->z;
             vertexData[posn++] = tri->v2->n->x;
             vertexData[posn++] = tri->v2->n->y;
             vertexData[posn++] = tri->v2->n->z;
             vertexData[posn++] = tri->v2->u;
             vertexData[posn++] = tri->v2->v;

             vertexData[posn++] = tri->v3->x;
             vertexData[posn++] = tri->v3->y;
             vertexData[posn++] = tri->v3->z;
             vertexData[posn++] = tri->v3->n->x;
             vertexData[posn++] = tri->v3->n->y;
             vertexData[posn++] = tri->v3->n->z;
             vertexData[posn++] = tri->v3->u;
             vertexData[posn++] = tri->v3->v;
         }
        // bind array data
        lmshape->shape->setVertexData(vertexData, dataSize, GL_TRIANGLES, numVerts);
        // set vertex attribute
        lmshape->shape->setAttribute(m_vertexIndex, 3, GL_FLOAT, GL_FALSE, stride, 0);
        // set normal attribute
        lmshape->shape->setAttribute(m_normalIndex, 3, GL_FLOAT, GL_TRUE, stride, vertexSize);
        // set texCoord attribute
        lmshape->shape->setAttribute(m_texCoordIndex, 2, GL_FLOAT, GL_FALSE, stride, 2 * vertexSize);
    }
}

std::vector<LMaterialShape*> LShape::getShapes() {
    return m_shapes;
}


