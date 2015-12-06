#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include "GL/glew.h"
#include <glm/vec3.hpp>


class OpenGLShape;
class NormalRenderer;

class Shape
{
public:
    Shape(GLuint vertexAttribIndex, GLuint normalAttribIndex);

    virtual ~Shape();

    virtual void setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3);

    void setNormalRenderer(NormalRenderer *normalRenderer);

    virtual void draw();

protected:
    void makeTriangle(int dataOffset,
                      const glm::vec3 &up, const glm::vec3 &upN,
                      const glm::vec3 &bl, const glm::vec3 &blN,
                      const glm::vec3 &br, const glm::vec3 &brN,
                      const GLfloat upU, const GLfloat upV,
                      const GLfloat blU, const GLfloat blV,
                      const GLfloat brU, const GLfloat brV);

    void makeQuad(int dataOffset,
                  const glm::vec3 &ul, const glm::vec3 &ulN,
                  const glm::vec3 &ur, const glm::vec3 &urN,
                  const glm::vec3 &bl, const glm::vec3 &blN,
                  const glm::vec3 &br, const glm::vec3 &brN,
                  const GLfloat uMin, const GLfloat uMax,
                  const GLfloat vMin, const GLfloat vMax);

    virtual void makeShapeWithNormals();

    static const int m_dimensions = 3;

    OpenGLShape *m_shape;
    GLfloat *m_vertexData;
    int m_numVertices;

    int m_shapeP1;
    int m_shapeP2;
    float m_shapeP3;

private:
    GLuint m_vertexIndex;
    GLuint m_normalIndex;
};

#endif // SHAPE_H
