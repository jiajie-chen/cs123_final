#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include "Shape.h"

class SphereShape : public Shape
{
public:
    SphereShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                GLuint vertexAttribIndex, GLuint normalAttribIndex);

    virtual ~SphereShape();

    void setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3);

    void makeShapeWithNormals();
};

#endif // SPHERESHAPE_H
