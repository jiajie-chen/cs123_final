#include "Shape.h"

#include "OpenGLShape.h"
#include "OpenGLScene.h"

Shape::Shape(GLuint vertexAttribIndex, GLuint normalAttribIndex, GLuint texCoordAttribIndex) :
    m_shape(new OpenGLShape()),
    m_vertexData(new GLfloat[0]),
    m_numVertices(0),
    m_shapeP1(0),
    m_shapeP2(0),
    m_shapeP3(0.f),
    m_vertexIndex(vertexAttribIndex),
    m_normalIndex(normalAttribIndex),
    m_texCoordIndex(texCoordAttribIndex)
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
                         const glm::vec3 &br, const glm::vec3 &brN,
                         const GLfloat upU, const GLfloat upV,
                         const GLfloat blU, const GLfloat blV,
                         const GLfloat brU, const GLfloat brV)
{
    m_vertexData[dataOffset++] =  up.x; m_vertexData[dataOffset++] =  up.y; m_vertexData[dataOffset++] =  up.z;
    m_vertexData[dataOffset++] = upN.x; m_vertexData[dataOffset++] = upN.y; m_vertexData[dataOffset++] = upN.z;
    m_vertexData[dataOffset++] =   upU; m_vertexData[dataOffset++] =   upV;

    m_vertexData[dataOffset++] =  bl.x; m_vertexData[dataOffset++] =  bl.y; m_vertexData[dataOffset++] =  bl.z;
    m_vertexData[dataOffset++] = blN.x; m_vertexData[dataOffset++] = blN.y; m_vertexData[dataOffset++] = blN.z;
    m_vertexData[dataOffset++] =   blU; m_vertexData[dataOffset++] =   blV;

    m_vertexData[dataOffset++] =  br.x; m_vertexData[dataOffset++] =  br.y; m_vertexData[dataOffset++] =  br.z;
    m_vertexData[dataOffset++] = brN.x; m_vertexData[dataOffset++] = brN.y; m_vertexData[dataOffset++] = brN.z;
    m_vertexData[dataOffset++] =   brU; m_vertexData[dataOffset++]   = brV;
}

void Shape::makeQuad(int dataOffset,
                     const glm::vec3 &ul, const glm::vec3 &ulN,
                     const glm::vec3 &ur, const glm::vec3 &urN,
                     const glm::vec3 &bl, const glm::vec3 &blN,
                     const glm::vec3 &br, const glm::vec3 &brN,
                     const GLfloat uMin, const GLfloat uMax,
                     const GLfloat vMin, const GLfloat vMax)
{
    makeTriangle(dataOffset, ur, urN, ul, ulN, br, brN, uMax, vMin, uMin, vMin, uMax, vMax);
    makeTriangle(dataOffset + 24, bl, blN, br, brN, ul, ulN, uMin, vMax, uMax, vMax, uMin, vMin);
}

void Shape::makeShapeWithNormals()
{
    // reinitialize shape
    // m_shape.reset(new OpenGLShape());

    int vertexSize = sizeof(GLfloat) * m_dimensions;
    int texSize = sizeof(GLfloat) * m_texDimensions;
    int stride = 2 * vertexSize + texSize;
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
