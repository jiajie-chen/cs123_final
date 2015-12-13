#include "POVCamera.h"

#include "Settings.h"
#include <glm/gtx/rotate_vector.hpp>

POVCamera::POVCamera() :
    m_aspect(1),
    m_oldX(0),
    m_oldY(0),
    m_eye(glm::vec3(-1.f, 0.f, 0.f)),
    m_up(glm::vec3(0.f, 1.f, 0.f)),
    m_look(glm::vec3(1.f, 0.f, 0.f))
{
    updateMatrices();
}

void POVCamera::setAspectRatio(float aspectRatio)
{
    m_aspect = aspectRatio;

    updateMatrices();
}

glm::mat4x4 POVCamera::getProjectionMatrix() const
{
    return m_projection;
}

glm::mat4x4 POVCamera::getViewMatrix() const
{
    return m_view;
}

glm::mat4x4 POVCamera::getScaleMatrix() const
{
    return glm::mat4x4(1.f);
}

void POVCamera::mouseDown(int x, int y)
{
    m_oldX = x;
    m_oldY = y;
}

void POVCamera::mouseDragged(int x, int y)
{
    float dU = -1.f * glm::radians(m_oldY - y);
    float dV = glm::radians(m_oldX - x);

    glm::vec3 side = glm::normalize(
                glm::cross(m_up, m_look));

    m_look = glm::rotate(m_look,
                      dU,
                      side);
    m_look = glm::rotate(m_look,
                      dV,
                      m_up);

    m_oldX = x;
    m_oldY = y;

    updateMatrices();
}

void POVCamera::mouseScrolled(int delta)
{

}

void POVCamera::translate(glm::vec3 v)
{
    glm::vec3 side = glm::normalize(
                glm::cross(m_up, m_look));

    m_eye += v.z * m_look +
             v.x * side;

    updateMatrices();
}

void POVCamera::updateMatrices()
{
    float farPlane = std::max(settings.cameraFar, settings.cameraNear + 100.f * FLT_EPSILON);

    m_projection = glm::perspective(glm::radians(settings.cameraFov),
                                    m_aspect,
                                    settings.cameraNear,
                                    farPlane);

    m_view = glm::lookAt(m_eye,
                         m_eye + m_look,
                         m_up);
}
