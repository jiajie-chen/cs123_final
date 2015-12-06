#include "CylinderShape.h"

#define GLM_FORCE_RADIANS
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

#define PI 3.14159265f

CylinderShape::CylinderShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                             GLuint vertexAttribIndex, GLuint normalAttribIndex)
    : Shape(vertexAttribIndex, normalAttribIndex)
{
    setTesselation(shapeParameter1, shapeParameter2, shapeParameter3);
}

CylinderShape::~CylinderShape()
{
}

void CylinderShape::setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3)
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

void CylinderShape::makeShapeWithNormals()
{
    // calculate total vertices needed
    int numTriangles = (2 * m_shapeP1 * m_shapeP2) + (2 * m_shapeP2); // triangles are equal to # tri on barrel + 2*# tris on cap
    m_numVertices = numTriangles * 3;

    // make vertex array
    m_vertexData = new GLfloat[2 * m_numVertices * m_dimensions];

    // initialize data
    int offset = 0;
    int quadStride = 48;
    int triStride = 24;

    float dRad = 2*PI/m_shapeP2;

    // cylinder caps, by slices
    glm::vec3 center = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 left = glm::vec3(0.0f, 0.5f, 0.5f);
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < m_shapeP2; i++) {
        glm::vec3 right = glm::rotateY(left, dRad);
        GLfloat uL = 1.f / m_shapeP2 * i;
        GLfloat uR =;
        GLfloat uC;
        GLfloat vL;
        GLfloat vR;
        GLfloat vC;

        makeTriangle(offset,
                     center, normal,
                     left, normal,
                     right, normal,
                     uC, vC,
                     uL, vL,
                     uR, vR);
        offset += triStride;

        makeTriangle(offset,
                     glm::rotateZ(center, PI), glm::rotateZ(normal, PI),
                     glm::rotateZ(left, PI), glm::rotateZ(normal, PI),
                     glm::rotateZ(right, PI), glm::rotateZ(normal, PI),
                     uC, vC,
                     uL, vL,
                     uR, vR);
        offset += triStride;

        left = right;
    }

    // cylinder sides, going by rings
    for (int i = 0 ; i < m_shapeP1; i++) {
        float a1 = static_cast<float>(i)/m_shapeP1 - 0.5;
        float a2 = static_cast<float>(i+1)/m_shapeP1 - 0.5;

        glm::vec3 ul = glm::vec3(0.0f,   a2, 0.5f);
        glm::vec3 bl = glm::vec3(0.0f,   a1, 0.5f);
        glm::vec3 lN = glm::vec3(0.0f, 0.0f, 1.0f);
        for (int j = 1; j <= m_shapeP2; j++) {
            glm::vec3 ur = glm::rotateY(ul, dRad);
            glm::vec3 br = glm::rotateY(bl, dRad);
            glm::vec3 rN = glm::rotateY(lN, dRad);

            makeQuad(offset,
                     ul, lN,
                     ur, rN,
                     bl, lN,
                     br, rN);
            offset += quadStride;

            ul = ur;
            bl = br;
            lN = rN;
        }
    }

    // set data to shape
   Shape::makeShapeWithNormals();
}
