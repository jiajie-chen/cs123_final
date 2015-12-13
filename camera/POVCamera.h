#ifndef POVCAMERA_H
#define POVCAMERA_H

#include "Camera.h"

class POVCamera : public Camera
{
public:
    POVCamera();

    virtual void setAspectRatio(float aspectRatio);

    virtual glm::mat4x4 getProjectionMatrix() const;
    virtual glm::mat4x4 getViewMatrix() const;
    virtual glm::mat4x4 getScaleMatrix() const;

    virtual void mouseDown(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mouseScrolled(int delta);
    virtual void translate(glm::vec3 v);

    void updateMatrices();

private:
    float m_aspect;

    float m_oldX;
    float m_oldY;

    glm::vec3 m_eye;
    glm::vec3 m_up;
    glm::vec3 m_look;

    glm::mat4x4 m_view;
    glm::mat4x4 m_projection;
};

#endif // POVCAMERA_H
