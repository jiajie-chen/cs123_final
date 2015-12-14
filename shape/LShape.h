#ifndef LSHAPE_H
#define LSHAPE_H
#define GLM_FORCE_RADIANS
#include "lsystem/LSystemGenerator.h"
#include "OpenGLShape.h"
#include "CS123SceneData.h"
#include "OpenGLScene.h"
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

struct normal {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    normal() : x(0), y(0), z(0) {}
    normal(GLfloat a, GLfloat b, GLfloat c)
        :x(a), y(b), z(c) {
        glm::vec3 v = glm::normalize(glm::vec3(x, y, z));
        x = v.x;
        y = v.y;
        z = v.z;
    }
    void rotateX(float angle) {
        glm::vec3 v = glm::rotateX(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
    }

    void rotateY(float angle) {
        glm::vec3 v = glm::rotateY(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
    }

    void rotateZ(float angle) {
        glm::vec3 v = glm::rotateZ(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
    }

     void transform(glm::mat4x4 cfm) {
         glm::vec4 v = cfm * glm::vec4(x, y, z, 0);
         x = v.x;
         y = v.y;
         z = v.z;
     }
};

// vertex struct for easier indexiing and automatic normal creation
struct vertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    GLfloat u;
    GLfloat v;

    normal* n;

    vertex() : x(0), y(0), z(0), n(NULL) {}
    vertex(GLfloat a, GLfloat b, GLfloat c, normal* norm, GLfloat d, GLfloat e)
        :x(a), y(b), z(c), n(norm), u(d), v(e)
    {

    }

    ~vertex()
    {
        delete n;
    }

    void rotateX(float angle) {
        glm::vec3 v = glm::rotateX(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
        n->rotateX(angle);
    }

    void rotateY(float angle) {
        glm::vec3 v = glm::rotateY(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
        n->rotateY(angle);
    }

    void rotateZ(float angle) {
        glm::vec3 v = glm::rotateZ(glm::vec3(x, y, z), angle);
        x = v.x;
        y = v.y;
        z = v.z;
        n->rotateZ(angle);
    }

    void transform(glm::mat4x4 cfm) {
        glm::vec4 v = cfm * glm::vec4(x, y, z, 1);
        x = v.x;
        y = v.y;
        z = v.z;
        n->transform(cfm);
    }
};

struct triangle {
    vertex* v1;
    vertex* v2;
    vertex* v3;

    triangle(): v1(NULL), v2(NULL), v3(NULL) {}
    triangle(vertex* vec1, vertex* vec2, vertex* vec3)
        : v1(vec1), v2(vec2), v3(vec3) {}
    triangle(vertex* vec1, vertex* vec2, vertex* vec3, glm::mat4x4 ctm)
        : v1(vec1), v2(vec2), v3(vec3) {
        this->transform(ctm);
    }
    ~triangle() {
        delete v1;
        delete v2;
        delete v3;
    }

    void rotateX(float angle) {
        v1->rotateX(angle);
        v2->rotateX(angle);
        v3->rotateX(angle);
    }

    void rotateY(float angle) {
        v1->rotateY(angle);
        v2->rotateY(angle);
        v3->rotateY(angle);
    }

    void rotateZ(float angle) {
        v1->rotateZ(angle);
        v2->rotateZ(angle);
        v3->rotateZ(angle);
    }

    void transform(glm::mat4x4 ctm) {
        v1->transform(ctm);
        v2->transform(ctm);
        v3->transform(ctm);
    }
};

struct state {
    int id;
    glm::vec3 heading;
    glm::vec3 left;
    glm::vec3 up;
    glm::mat4x4 ctm;
    float length;
    float width;
    int materialIdx;

    state() :
      id(0),
      heading(glm::vec3(0,-1,0)), // default heading to y axis
      left(glm::vec3(-1,0,0)),
      up(glm::vec3(0,0, 1)),
      ctm(glm::mat4x4(1.0)),
      length(.5),
      width(.1),
      materialIdx(0){}
    state(state &s):
        id(s.id+1),
        heading(s.heading),
        left(s.left),
        up(s.up),
        ctm(s.ctm),
        length(s.length),
        width(s.width),
        materialIdx(s.materialIdx){

    }
};

struct LMaterialShape {
    OpenGLShape *shape;
    std::vector<triangle *> m_triangles;
    int numVertices;
    CS123SceneMaterial material;
    LMaterialShape(CS123SceneMaterial material)
        : shape(new OpenGLShape()), m_triangles(std::vector<triangle *>()), material(material) {}
    ~LMaterialShape() {
        delete shape;
        for(triangle *t : m_triangles) {
            delete t;
        }
        m_triangles.clear();
    }
};

class LShape
{
public:
    LShape(std::string rules, std::vector<CS123SceneMaterial> materials, GLuint vertexAttribIndex, GLuint normalAttribIndex, GLuint texCoordAttribIndex);
    virtual ~LShape();
    void prepareShape(LMaterialShape * lmshape);
    std::vector<LMaterialShape*> getShapes();


private:
    std::vector<LMaterialShape*> m_shapes;
    std::list<state *> m_state_stack;
    state *m_current_state;
    void addStateToShape(int materialIdx);
    std::vector<triangle *> getCylinder(float length, float width);

    // gl stuff
    GLuint m_vertexIndex;
    GLuint m_normalIndex;
    GLuint m_texCoordIndex;

};

#endif // LShape_H
