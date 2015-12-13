#ifndef CYLINDERSHAPE_H
#define CYLINDERSHAPE_H

#include "Shape.h"

class CylinderShape : public Shape
{
public:
    CylinderShape(int shapeParameter1, int shapeParameter2, float shapeParameter3,
                  GLuint vertexAttribIndex, GLuint normalAttribIndex, GLuint texCoordIndex);

    virtual ~CylinderShape();

    void setTesselation(int shapeParameter1, int shapeParameter2, float shapeParameter3);

    void makeShapeWithNormals();
};

#endif // CYLINDERSHAPE_H
