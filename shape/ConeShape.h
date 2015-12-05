#ifndef CONESHAPE_H
#define CONESHAPE_H

#include "Shape.h"

class ConeShape : public Shape
{
public:
    ConeShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
              GLuint vertexAttribIndex, GLuint normalAttribIndex);

    virtual ~ConeShape();

    void setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3);

    void makeShapeWithNormals();
};

#endif // CONESHAPE_H
