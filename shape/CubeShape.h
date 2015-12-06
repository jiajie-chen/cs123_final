#ifndef CUBESHAPE_H
#define CUBESHAPE_H

#include "Shape.h"

class CubeShape : public Shape
{
public:
    CubeShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
              GLuint vertexAttribIndex, GLuint normalAttribIndex, GLuint texCoordAttribIndex);

    virtual ~CubeShape();

    void setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3);

    void makeShapeWithNormals();
};

#endif // CUBESHAPE_H
