#include "SphereShape.h"

#define GLM_FORCE_RADIANS
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

#define PI 3.14159265f

SphereShape::SphereShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                         GLuint vertexAttribIndex, GLuint normalAttribIndex)
    : Shape(vertexAttribIndex, normalAttribIndex)
{
    setTesselation(shapeParameter1, shapeParameter2, shapeParameter3);
}

SphereShape::~SphereShape()
{
}

void SphereShape::setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3)
{
    // rectify parameters
    int p1 = std::max(shapeParameter1, 2);
    int p2 = std::max(shapeParameter2, 3);
    float p3 = shapeParameter3;

    // don't update values if haven't changed
    if ((m_shapeP1 == p1) &&
        (m_shapeP2 == p2))
    {
        return;
    }

    // set tesselations values to new values
    //Shape::setTesselation(p1, p2, p3);
    Shape::setTesselation(p1, p2, p3);
}

void SphereShape::makeShapeWithNormals()
{
    // calculate total vertices needed (# tri per slice * # slices)
    int numTriangles = (2 * (m_shapeP1 - 1)) * m_shapeP2;
    m_numVertices = numTriangles * 3;

    // make vertex array
    m_vertexData = new GLfloat[2 * m_numVertices * m_dimensions];

    //initialize data, going by rows of subsquares
    int offset = 0;
    int quadStride = 48;
    int triStride = 24;

    float dLat = PI/m_shapeP1;
    float dLon = 2*PI/m_shapeP2;

    // go by horizontal slices
    for (int i = 0 ; i < m_shapeP1; i++) {
        // go by slices
        GLfloat vMin = 1.f / m_shapeP1 * i;
        GLfloat vMax = 1.f / m_shapeP1 * (i + 1);
        for (int j = 0; j < m_shapeP2; j++) {
            float urX = 0.5 * glm::sin(dLat*i) * glm::cos(dLon*j);
            float urY = 0.5 * glm::cos(dLat*i);
            float urZ = 0.5 * glm::sin(dLat*i) * glm::sin(dLon*j);

            float brX = 0.5 * glm::sin(dLat*(i+1)) * glm::cos(dLon*j);
            float brY = 0.5 * glm::cos(dLat*(i+1));
            float brZ = 0.5 * glm::sin(dLat*(i+1)) * glm::sin(dLon*j);

            float ulX = 0.5 * glm::sin(dLat*i) * glm::cos(dLon*(j+1));
            float ulY = 0.5 * glm::cos(dLat*i);
            float ulZ = 0.5 * glm::sin(dLat*i) * glm::sin(dLon*(j+1));

            float blX = 0.5 * glm::sin(dLat*(i+1)) * glm::cos(dLon*(j+1));
            float blY = 0.5 * glm::cos(dLat*(i+1));
            float blZ = 0.5 * glm::sin(dLat*(i+1)) * glm::sin(dLon*(j+1));

            glm::vec3 ul = glm::vec3(ulX, ulY, ulZ);
            glm::vec3 bl = glm::vec3(blX, blY, blZ);
            glm::vec3 ur = glm::vec3(urX, urY, urZ);
            glm::vec3 br = glm::vec3(brX, brY, brZ);

            GLfloat uMin = 1.f / m_shapeP2 * j;
            GLfloat uMax = 1.f / m_shapeP2 * (j + 1);

            // handle top cap and bottom cap
            if (i == 0) {
                makeTriangle(offset,
                             ul, glm::normalize(ul),
                             bl, glm::normalize(bl),
                             br, glm::normalize(br),
                             uMin, vMin,
                             uMin, vMax,
                             uMax, vMax);
                offset += triStride;
            } else if (i == m_shapeP1-1) {
                makeTriangle(offset,
                             ul, glm::normalize(ul),
                             bl, glm::normalize(bl),
                             ur, glm::normalize(ur),
                             uMin, vMin,
                             uMin, vMax,
                             uMax, vMin);
                offset += triStride;
            } else {
                makeQuad(offset,
                         ul, glm::normalize(ul),
                         ur, glm::normalize(ur),
                         bl, glm::normalize(bl),
                         br, glm::normalize(br),
                         uMin, uMax,
                         vMin, vMax);
                offset += quadStride;
            }
        }
    }

    // call super class to set m_shape
    Shape::makeShapeWithNormals();
}
