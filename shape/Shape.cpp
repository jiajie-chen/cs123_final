#include "Shape.h"

#include "OpenGLShape.h"
#include "OpenGLScene.h"

Shape::Shape(GLuint vertexAttribIndex, GLuint normalAttribIndex) :
    m_shape(new OpenGLShape()),
    m_vertexData(new GLfloat[0]),
    m_numVertices(0),
    m_shapeP1(0),
    m_shapeP2(0),
    m_shapeP3(0.f),
    m_vertexIndex(vertexAttribIndex),
    m_normalIndex(normalAttribIndex)
{
}

Shape::~Shape()
{
}

void Shape::setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3)
{
    m_shapeP1 = shapeParameter1;
    m_shapeP2 = shapeParameter2;
    m_shapeP3 = shapeParameter3;

    makeShapeWithNormals();
}

void Shape::makeTriangle(int dataOffset,
                         const glm::vec3 &up, const glm::vec3 &upN,
                         const glm::vec3 &bl, const glm::vec3 &blN,
                         const glm::vec3 &br, const glm::vec3 &brN)
{
    m_vertexData[dataOffset + 0] =  up.x; m_vertexData[dataOffset + 1] =  up.y; m_vertexData[dataOffset + 2] =  up.z;
    m_vertexData[dataOffset + 3] = upN.x; m_vertexData[dataOffset + 4] = upN.y; m_vertexData[dataOffset + 5] = upN.z;

    m_vertexData[dataOffset + 6] =  bl.x; m_vertexData[dataOffset +  7] =  bl.y; m_vertexData[dataOffset +  8] =  bl.z;
    m_vertexData[dataOffset + 9] = blN.x; m_vertexData[dataOffset + 10] = blN.y; m_vertexData[dataOffset + 11] = blN.z;

    m_vertexData[dataOffset + 12] =  br.x; m_vertexData[dataOffset + 13] =  br.y; m_vertexData[dataOffset + 14] =  br.z;
    m_vertexData[dataOffset + 15] = brN.x; m_vertexData[dataOffset + 16] = brN.y; m_vertexData[dataOffset + 17] = brN.z;
}

void Shape::makeQuad(int dataOffset,
                     const glm::vec3 &ul, const glm::vec3 &ulN,
                     const glm::vec3 &ur, const glm::vec3 &urN,
                     const glm::vec3 &bl, const glm::vec3 &blN,
                     const glm::vec3 &br, const glm::vec3 &brN)
{
    makeTriangle(dataOffset, ur, urN, ul, ulN, br, brN);
    makeTriangle(dataOffset + 18, bl, blN, br, brN, ul, ulN);
}

void Shape::makeShapeWithNormals()
{
    // reinitialize shape
    // m_shape.reset(new OpenGLShape());

    int vertexSize = sizeof(GLfloat) * m_dimensions;
    int stride = 2 * vertexSize;
    int dataSize = stride * m_numVertices;

    // bind array data
    m_shape->setVertexData(m_vertexData, dataSize, GL_TRIANGLES, m_numVertices);
    // set vertex attribute
    m_shape->setAttribute(m_vertexIndex, m_dimensions, GL_FLOAT, GL_FALSE, stride, 0);
    // set normal attribute
    m_shape->setAttribute(m_normalIndex, m_dimensions, GL_FLOAT, GL_TRUE, stride, vertexSize);
}

void Shape::setNormalRenderer(NormalRenderer *normalRenderer)
{
    int vertexSize = sizeof(GLfloat) * m_dimensions;
    int stride = 2 * vertexSize;

    // add normal rendering
    normalRenderer->generateArrays(
                m_vertexData,          // Pointer to vertex data
                stride,        // Stride (distance between consecutive vertices/normals in BYTES
                0,             // Offset of first position in BYTES
                vertexSize,    // Offset of first normal in BYTES
                m_numVertices);  // Number of vertices
}

void Shape::draw()
{
    m_shape->draw();
}
