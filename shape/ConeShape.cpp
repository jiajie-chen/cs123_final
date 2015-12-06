#include "ConeShape.h"

#define GLM_FORCE_RADIANS
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

#define PI 3.14159265f

ConeShape::ConeShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                     GLuint vertexAttribIndex, GLuint normalAttribIndex)
    : Shape(vertexAttribIndex, normalAttribIndex)
{
    setTesselation(shapeParameter1, shapeParameter2, shapeParameter3);
}

ConeShape::~ConeShape()
{
}

void ConeShape::setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3)
{
    // rectify parameters
    int p1 = std::max(shapeParameter1, 1);
    int p2 = std::max(shapeParameter2, 3);
    float p3 = shapeParameter3;

    // don't update values if haven't changed
    if ((m_shapeP1 == p1) &&
        (m_shapeP2 == p2))
    {
        return;
    }

    // set tesselations values to new values
    Shape::setTesselation(p1, p2, p3);
}

void ConeShape::makeShapeWithNormals()
{
    // calculate total vertices needed
    int numTriangles = (((2 * m_shapeP1) - 1) * m_shapeP2) + (m_shapeP2); // triangles are equal to # tri on barrel + # tris on cap
    m_numVertices = numTriangles * 3;

    // make vertex array
    m_vertexData = new GLfloat[2 * m_numVertices * m_dimensions];

    // initialize data
    int offset = 0;
    int quadStride = 36;
    int triStride = 18;

    float dRad = 2*PI/m_shapeP2;

    // cone bottom cap, by slices
    glm::vec3 bottom = glm::vec3(0.0f, -0.5f, 0.0f);
    glm::vec3 right = glm::vec3(0.0f, -0.5f, 0.5f);
    glm::vec3 normal = glm::vec3(0.0f, -1.0f, 0.0f);
    for (int i = 0; i < m_shapeP2; i++) {
        glm::vec3 left = glm::rotateY(right, dRad);

        makeTriangle(offset,
                     bottom, normal,
                     left, normal,
                     right, normal);
        offset += triStride;

        right = left;
    }

    //cone sides, by rings
    glm::vec3 top = glm::vec3(0.0f, 0.5f, 0.0f);
    for (int i = 0 ; i < m_shapeP1; i++) {
        float y1 = 0.5 - static_cast<float>(i)/m_shapeP1;
        float y2 = 0.5 - static_cast<float>(i+1)/m_shapeP1;

        float z1 = 0.25 - y1*0.5;
        float z2 = 0.25 - y2*0.5;

        glm::vec3 ul = glm::vec3(0.0f,   y1,   z1);
        glm::vec3 bl = glm::vec3(0.0f,   y2,   z2);

        glm::vec3 topN = glm::rotateY(
                    glm::normalize(
                        glm::vec3(0.0f, 0.5f, 1.0f)),
                    dRad/2);

        glm::vec3 ulN = glm::normalize(
                    glm::vec3(0.0f, 0.5f, 1.0f));
        glm::vec3 blN = glm::normalize(
                        glm::vec3(0.0f, 0.5f, 1.0f));
        // go by slices
        for (int j = 1; j <= m_shapeP2; j++) {
            glm::vec3 ur = glm::rotateY(ul, dRad);
            glm::vec3 br = glm::rotateY(bl, dRad);

            glm::vec3 urN = glm::rotateY(ulN, dRad);
            glm::vec3 brN = glm::rotateY(blN, dRad);

            // handle top cap
            if (i == 0) {
                makeTriangle(offset,
                             top, topN,
                             bl, blN,
                             br, brN);
                offset += triStride;

                topN = glm::rotateY(topN, dRad);
            } else {
                makeQuad(offset,
                         ul, ulN,
                         ur, urN,
                         bl, blN,
                         br, brN);
                offset += quadStride;
            }

            ul = ur;
            bl = br;
            ulN = urN;
            blN = brN;
        }
    }

    // set data to shape
   Shape::makeShapeWithNormals();
}
