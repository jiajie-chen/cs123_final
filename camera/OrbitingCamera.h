#ifndef ORBITINGCAMERA_H
#define ORBITINGCAMERA_H

#include "Camera.h"


/**
 * @class OrbitingCamera
 *
 * Camera that move in response to mouse interaction.
 *
 * You shouldn't need to work on this class. It's there for your convenience, really,
 * and the way this camera is implemented is NOT the way you should be implementing
 * your camera in the Camtrans lab. We hide the real implementation by using OpenGL to
 * perform the camera calculations.
 *
 */
class OrbitingCamera : public Camera
{
public:
    OrbitingCamera();

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
    void updateProjectionMatrix();
    void updateViewMatrix();

    glm::mat4x4 m_viewMatrix;
    glm::mat4x4 m_projectionMatrix;
    float m_aspectRatio, m_angleX, m_angleY, m_zoomZ;
    int m_oldX, m_oldY;
    glm::vec3 m_position;
};

#endif // ORBITINGCAMERA_H
