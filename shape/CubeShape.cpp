#include "CubeShape.h"

#define GLM_FORCE_RADIANS
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

#define PI 3.14159265f

CubeShape::CubeShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                     GLuint vertexAttribIndex, GLuint normalAttribIndex)
    : Shape(vertexAttribIndex, normalAttribIndex)
{
    setTesselation(shapeParameter1, shapeParameter2, shapeParameter3);
}

CubeShape::~CubeShape()
{
}

void CubeShape::setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3)
{
    // rectify parameters, only first tesselation value matters for cube
    int p1 = std::max(shapeParameter1, 1);
    int p2 = shapeParameter2;
    float p3 = shapeParameter3;

    // don't update if settings haven't changed
    if (m_shapeP1 == p1) {
        return;
    }

    // else, call super
    Shape::setTesselation(p1, p2, p3);
}

void CubeShape::makeShapeWithNormals()
{
    // calculate total vertices needed
    int numTriangles = 2 * m_shapeP1 * m_shapeP1 * 6;
    m_numVertices = numTriangles * 3;

    // make vertex array
    m_vertexData.reset(new GLfloat[2 * m_numVertices * m_dimensions]);

    //initialize data, going by rows of subsquares
    int offset = 0;
    int quadStride = 36;
    for (int i = 0 ; i < m_shapeP1; i++) {
        float a1 = static_cast<float>(i)/m_shapeP1 - 0.5;
        float a2 = static_cast<float>(i+1)/m_shapeP1 - 0.5;

        for (int j = 0; j < m_shapeP1; j++) {
            float b1 = static_cast<float>(j)/m_shapeP1 - 0.5;
            float b2 = static_cast<float>(j+1)/m_shapeP1 - 0.5;

            // +xy plane
            glm::vec3 ul = glm::vec3(  a1,   b2, 0.5f);
            glm::vec3 ur = glm::vec3(  a2,   b2, 0.5f);
            glm::vec3 bl = glm::vec3(  a1,   b1, 0.5f);
            glm::vec3 br = glm::vec3(  a2,   b1, 0.5f);
            glm::vec3 nm = glm::vec3(0.0f, 0.0f, 1.0f);

            makeQuad(offset,
                     ul, nm,
                     ur, nm,
                     bl, nm,
                     br, nm);
            offset += quadStride;

            // -xy plane
            makeQuad(offset,
                     glm::rotateY(ul, PI), glm::rotateY(nm, PI),
                     glm::rotateY(ur, PI), glm::rotateY(nm, PI),
                     glm::rotateY(bl, PI), glm::rotateY(nm, PI),
                     glm::rotateY(br, PI), glm::rotateY(nm, PI));
            offset += quadStride;

            // +xz plane
            makeQuad(offset,
                     glm::rotateY(ul, PI/2), glm::rotateY(nm, PI/2),
                     glm::rotateY(ur, PI/2), glm::rotateY(nm, PI/2),
                     glm::rotateY(bl, PI/2), glm::rotateY(nm, PI/2),
                     glm::rotateY(br, PI/2), glm::rotateY(nm, PI/2));
            offset += quadStride;

            // -xz plane
            makeQuad(offset,
                     glm::rotateY(ul, -PI/2), glm::rotateY(nm, -PI/2),
                     glm::rotateY(ur, -PI/2), glm::rotateY(nm, -PI/2),
                     glm::rotateY(bl, -PI/2), glm::rotateY(nm, -PI/2),
                     glm::rotateY(br, -PI/2), glm::rotateY(nm, -PI/2));
            offset += quadStride;

            // +yz plane
            makeQuad(offset,
                     glm::rotateX(ul, PI/2), glm::rotateX(nm, PI/2),
                     glm::rotateX(ur, PI/2), glm::rotateX(nm, PI/2),
                     glm::rotateX(bl, PI/2), glm::rotateX(nm, PI/2),
                     glm::rotateX(br, PI/2), glm::rotateX(nm, PI/2));
            offset += quadStride;

            // -yz plane
            makeQuad(offset,
                     glm::rotateX(ul, -PI/2), glm::rotateX(nm, -PI/2),
                     glm::rotateX(ur, -PI/2), glm::rotateX(nm, -PI/2),
                     glm::rotateX(bl, -PI/2), glm::rotateX(nm, -PI/2),
                     glm::rotateX(br, -PI/2), glm::rotateX(nm, -PI/2));
            offset += quadStride;
        }
    }

    // call super class to set m_shape
    Shape::makeShapeWithNormals();
}
