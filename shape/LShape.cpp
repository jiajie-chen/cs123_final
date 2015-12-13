#include "LShape.h"
#include "vector"
#include "lsystem/LSystemGenerator.h"

#define M_SHAPE_P1 10
#define M_SHAPE_P2 10

#define UP_THETA (float) M_PI/12
#define LEFT_THETA (float)M_PI/15.0f
#define H_THETA (float) M_PI/12.0f
#define D_LENGTH (float).01f
#define D_WIDTH (float).01f

LShape::LShape(state start_state,
               LSystemGenerator *lsg,
               int depth,
               GLuint vertexAttribIndex,
               GLuint normalAttribIndex,
               GLuint texCoordAttribIndex) :
    m_vertexIndex(vertexAttribIndex),
    m_normalIndex(normalAttribIndex),
    m_texCoordIndex(texCoordAttribIndex)

{
    // the number of openglshapes to work with
    int numMaterials = lsg->getNumMaterials();

    // init the shapes
    for (int i = 0; i < numMaterials; i++) {
        CS123SceneMaterial m = lsg->getMaterial(i);
        m_shapes.push_back(new LMaterialShape(m));
    }

    //*********BEGIN PARSING RULES***********\\
    m_state_stack = std::vector<state>();
    m_shapes = std::vector<LMaterialShape*>();
    m_current_state = start_state;
    // axes in untransformed objectspace
    glm::vec3 turn_axis = glm::vec3(0, 0, 1);
    glm::vec3 pitch_axis = glm::vec3(1, 0, 0);
    glm::vec3 roll_axis = glm::vec3(0, 1, 0);

    std::string rules = lsg->makeLSystem(depth); //finish the math for the l-system, outputs a string of rules
    // loop through the rules and execute each
    for(char& command : rules) {
        glm::mat4x4 ctm2 = glm::mat4x4(1.0);
        switch(command){
        case 'F':
            //adds a geometric representation of the current state to the appropriate openglshape in m_shapes
            addStateToShape(m_current_state.materialIdx);
            ctm2 *= glm::translate(glm::mat4x4(1.0), glm::vec3(0, m_current_state.length, 0));
            //m_current_state.position += m_current_state.heading*m_current_state.length;
        break;
        case 'f':
            //move forward
            ctm2 *= glm::translate(glm::mat4x4(1.0), glm::vec3(0, m_current_state.length, 0));
            //m_current_state.position += m_current_state.heading*m_current_state.length;
        break;
        case '+':
            //turn left by UP_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), UP_THETA, turn_axis);
            //m_current_state.heading = glm::rotate(m_current_state.heading, UP_THETA, m_current_state.up);
            //m_current_state.left = glm::rotate(m_current_state.left, UP_THETA, m_current_state.up);
        break;
        case '-':
            //turn right by -UP_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), -UP_THETA, turn_axis);
            //m_current_state.heading = glm::rotate(m_current_state.heading, -UP_THETA, m_current_state.up);
            //m_current_state.left = glm::rotate(m_current_state.left, -UP_THETA, m_current_state.up);
        break;
        case '&':
            // pitch down by LEFT_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), LEFT_THETA, pitch_axis);
           //m_current_state.heading = glm::rotate(m_current_state.heading, LEFT_THETA, m_current_state.left);
            //m_current_state.up = glm::rotate(m_current_state.up, LEFT_THETA, m_current_state.left);
        break;
        case '^':
            // pitch up by LEFT_THETA
             ctm2 *= glm::rotate(glm::mat4x4(1.0), -LEFT_THETA, pitch_axis);
            //m_current_state.heading = glm::rotate(m_current_state.heading, -LEFT_THETA, m_current_state.left);
            //m_current_state.up = glm::rotate(m_current_state.up, -LEFT_THETA, m_current_state.left);
        break;
        case '\\':
            // roll left by H_THETA
             ctm2 *= glm::rotate(glm::mat4x4(1.0), H_THETA, roll_axis);
            //m_current_state.left = glm::rotate(m_current_state.left, H_THETA, m_current_state.heading);
            //m_current_state.up = glm::rotate(m_current_state.up, H_THETA, m_current_state.heading);
        break;
        case '/':
            // roll right by -H_THETA
            ctm2 *= glm::rotate(glm::mat4x4(1.0), -H_THETA, roll_axis);
            //m_current_state.left = glm::rotate(m_current_state.left, -H_THETA, m_current_state.heading);
            //m_current_state.up = glm::rotate(m_current_state.up, -H_THETA, m_current_state.heading);
        break;
        case '|':
            // rotate 180ºaround up.

            //lmao can't definte M_PI/float because it makes it a double
            ctm2 *= glm::rotate(glm::mat4x4(1.0),(float) M_PI, turn_axis);
            //m_current_state.heading = glm::rotate(m_current_state.heading, (float)M_PI, m_current_state.up);
            //m_current_state.left = glm::rotate(m_current_state.left, (float) M_PI, m_current_state.up);
        break;
        case '"':
            // increase length by D_LENGTH
            m_current_state.length += D_LENGTH;
        break;
        case '!':
             // increase width by D_WIDTH
            m_current_state.width += D_WIDTH;
        break;
        case '`':
            // decrease length by D_LENGTH
            m_current_state.length -= D_LENGTH;
        break;
        case '~':
            // decrease width by D_WIDTH
            m_current_state.width -= D_WIDTH;
        break;
        case '<':
            // increment the materialIdx (material selection is handled by the lsystem generator)
            // loop around at the ends
            m_current_state.materialIdx++;
            if (m_current_state.materialIdx > numMaterials - 1){
                m_current_state.materialIdx = 0;
            }
        break;
        case '>':
            // decrement the materialIdx
            m_current_state.materialIdx--;

            if (m_current_state.materialIdx < 0){
                m_current_state.materialIdx = numMaterials;
            }
        break;
        case '[':
            // push the current state onto the stack
            m_state_stack.push_back(m_current_state);
        break;
        case ']':
            // pop the state stack and set to the current state
            this->m_current_state = m_state_stack.back();
            m_state_stack.pop_back();
        break;
        }
        // update the current state's ctm
        m_current_state.ctm *= ctm2;
    }
    //*********END PARSING RULES***********\\

    // pass to opengl, now ready to call draw()
    prepareShapes();

}

LShape::~LShape() {
    m_state_stack.clear();
}

// add the geometery for the current state to the appropriate shape
void LShape::addStateToShape(int materialIdx){
    LMaterialShape *lmshape = m_shapes.at(materialIdx);
    // get the triangles for the new shape
    std::vector<triangle *> newTris = getCylinder(m_current_state.length, m_current_state.width);

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
    double stackStep = 1.0 / M_SHAPE_P2;
    float u1,v1,u2,v2,u3,v3,u4,v4,u5,v5,u6,v6;

    for (int i = 0 ; i < M_SHAPE_P2; i++) {
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

        normal *topn1 = new normal(topx1, topy1, topz1);
        normal *topn2 = new normal(topx2, topy2, topz2);
        normal *topn3 = new normal(topx3, -topy3, topz3);

        normal *botn1 = new normal(topx1, -topy1, topz1);
        normal *botn2 = new normal(topx2, -topy2, topz2);
        normal *botn3 = new normal(topx3, -topy3, topz3);

        vertex *topv1 = new vertex(topx1, topy1, topz1, topn1, u1, v1);
        vertex *topv2 = new vertex(topx2, topy2, topz2, topn2, u2, v2);
        vertex *topv3 = new vertex(topx3, topy3, topz3, topn3, u3, v3);

        vertex *botv1 = new vertex(topx1, -topy1, topz1, botn1, u1, v1);
        vertex *botv2 = new vertex(topx2, -topy2, topz2, botn2, u2, v2);
        vertex *botv3 = new vertex(topx3, -topy3, topz3, botn3, u3, v3);

        triangle * t1 = new triangle(topv3, topv2, topv1);
        triangle * t2 = new triangle(botv1, botv2, botv3);

        // apply the transformation for this state to the triangles
        t1->transform(m_current_state.ctm);
        t2->transform(m_current_state.ctm);

        triangles.push_back(t1);
        triangles.push_back(t2);

        // tesselate the sides
        for (int j = 0; j < M_SHAPE_P2; j++) {
            float uStride = 1.f / M_SHAPE_P2;
            float vStride = 1.f / M_SHAPE_P2;

            double x1 = cos(angleStep * i) * width;
            double y1 = (j * stackStep) - length;
            double z1 = sin(angleStep * i) * width;
            u1 = j * uStride;
            v1 = i * vStride;

            double x2 = cos(angleStep * (i+1)) * width;
            double y2 = (j  * stackStep) - length;
            double z2 = sin(angleStep * (i+1)) * width;
            u2 = j * uStride;
            v2 = (i + 1) * vStride;

            double x3 = cos(angleStep * (i+1)) * width;
            double y3 = ((j+1) * stackStep) - length;
            double z3 = sin(angleStep * (i+1)) * width;
            u3 = (j + 1) * uStride;
            v3 = (i + 1) * vStride;

            double x4 = cos(angleStep * i) * width;
            double y4 = ((j+1) * stackStep) - length;
            double z4 = sin(angleStep * i) * width;
            u4 = (j + 1) * uStride;
            v4 = i * vStride;

            double x5 = cos(angleStep * i) * width;
            double y5 = (j * stackStep) - length;
            double z5 = sin(angleStep * i) * width;
            u5 = j * uStride;
            v5 = i * vStride;

            double x6 = cos(angleStep * (i+1)) * width;
            double y6 = ((j+1) * stackStep) - length;
            double z6 = sin(angleStep * (i+1)) * width;
            u6 = (j + 1) * uStride;
            v6 = (i + 1) * vStride;

            normal *n1 = new normal(x1, y1, z1);
            normal *n2 = new normal(x2, y2, z2);
            normal *n3 = new normal(x3, y3, z3);

            normal *n4 = new normal(x4, y4, z4);
            normal *n5 = new normal(x5, y5, z5);
            normal *n6 = new normal(x6, y6, z6);

            vertex *vert1 = new vertex(x1, y1, z1, n1, u1, v1);
            vertex *vert2 = new vertex(x2, y2, z2, n2, u2, v2);
            vertex *vert3 = new vertex(x3, y3, z3, n3, u3, v3);

            vertex *vert4 = new vertex(x4, y4, z4, n4, u4, v4);
            vertex *vert5 = new vertex(x5, y5, z5, n5, u5, v5);
            vertex *vert6 = new vertex(x6, y6, z6, n6, u6, v6);

            t1 = new triangle(vert3, vert2, vert1);
            t2 = new triangle(vert6, vert5, vert4);

            // apply the transformation for this state to the triangles
            t1->transform(m_current_state.ctm);
            t2->transform(m_current_state.ctm);

            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    }
    return triangles;
}

// go from triangles to vertexData for OpenGLShape to consume.
void LShape::prepareShapes(){

    int vertexSize = sizeof(GLfloat) * 3; // *dimensions
    int texSize = sizeof(GLfloat) * 2; //*texcoords
    int stride = 2 * vertexSize + texSize;
    for (LMaterialShape *lmshape : m_shapes) {
        float numVerts = lmshape->m_triangles.size() * 3;
        int dataSize = numVerts * stride;
        GLfloat vertexData[dataSize];
        for (int i = 0; i < lmshape->m_triangles.size() / 3; i++) {
             triangle* tri = lmshape->m_triangles[i];
             vertexData[i* stride * 3 + 0] = tri->v1->x;
             vertexData[i* stride * 3 + 1] = tri->v1->y;
             vertexData[i* stride * 3 + 2] = tri->v1->z;
             vertexData[i* stride * 3 + 3] = tri->v1->n->x;
             vertexData[i* stride * 3 + 4] = tri->v1->n->y;
             vertexData[i* stride * 3 + 5] = tri->v1->n->z;
             vertexData[i* stride * 3 + 6] = tri->v1->u;
             vertexData[i* stride * 3 + 7] = tri->v1->v;

             vertexData[i* stride * 3 + 8] = tri->v2->x;
             vertexData[i* stride * 3 + 9] = tri->v2->y;
             vertexData[i* stride * 3 + 10] = tri->v2->z;
             vertexData[i* stride * 3 + 11] = tri->v2->n->x;
             vertexData[i* stride * 3 + 12] = tri->v2->n->y;
             vertexData[i* stride * 3 + 13] = tri->v2->n->z;
             vertexData[i* stride * 3 + 14] = tri->v2->u;
             vertexData[i* stride * 3 + 15] = tri->v2->v;

             vertexData[i* stride * 3 + 16] = tri->v3->x;
             vertexData[i* stride * 3 + 17] = tri->v3->y;
             vertexData[i* stride * 3 + 18] = tri->v3->z;
             vertexData[i* stride * 3 + 19] = tri->v3->n->x;
             vertexData[i* stride * 3 + 20] = tri->v3->n->y;
             vertexData[i* stride * 3 + 21] = tri->v3->n->z;
             vertexData[i* stride * 3 + 22] = tri->v3->u;
             vertexData[i* stride * 3 + 23] = tri->v3->v;
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

void LShape::draw(){
    for (LMaterialShape *lmshape : m_shapes) {
        lmshape->shape->draw();
    }
}

