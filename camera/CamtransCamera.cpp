/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>
/*
CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = 1.0;
    m_far = 30.0;
    m_hAngle = glm::radians(60.0);
    m_aspect = 1.0;

    orientLook(glm::vec4(2, 2, 2, 1),
               glm::vec4(0, 0, 0, 0),
               glm::vec4(0, 1, 0, 0));
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_aspect = a;
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return getPerspectiveMatrix() * getScaleMatrix();
}

glm::mat4x4 CamtransCamera::getViewMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...
    glm::mat4x4 rotate = glm::mat4x4(
                m_u.x, m_u.y, m_u.z, 0,
                m_v.x, m_v.y, m_v.z, 0,
                m_w.x, m_w.y, m_w.z, 0,
                    0,     0,     0, 1);
    glm::mat4x4 trans = glm::mat4x4(
                1, 0, 0, -m_eye.x,
                0, 1, 0, -m_eye.y,
                0, 0, 1, -m_eye.z,
                0, 0, 0,        1);

    return rotate * trans;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...
    float farTanH = glm::tan(m_hAngle/2);
    float farTanW = m_aspect*farTanH;
    farTanH *= m_far;
    farTanW *= m_far;

    glm::mat4x4 scale = glm::mat4x4(
                1/(farTanW),              0,       0, 0,
                             0, 1/(farTanH),       0, 0,
                             0,           0, 1/m_far, 0,
                             0,           0,       0, 1);

    return scale;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...
    float c = -1 * (m_near/m_far);
    glm::mat4x4 persp = glm::mat4x4(
                1, 0,        0,       0,
                0, 1,        0,       0,
                0, 0, -1/(c+1), c/(c+1),
                0, 0,       -1,       0);
    return persp;
}

glm::vec4 CamtransCamera::getPosition() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return -m_w;
}

glm::vec4 CamtransCamera::getUp() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_v;
}

float CamtransCamera::getAspectRatio() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspect;
}

float CamtransCamera::getHeightAngle() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return glm::degrees(m_hAngle);
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_eye = glm::vec4(eye);

    m_w = -(glm::normalize(look));
    m_v = glm::normalize(up - (glm::dot(up, m_w)*m_w));
    m_u = glm::vec4(glm::cross(glm::vec3(m_v), glm::vec3(m_w)), 0);

    m_eye.w = 1; m_u.w = 0; m_v.w = 0; m_w.w = 0;
}

void CamtransCamera::setHeightAngle(float h)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_hAngle = glm::radians(h);
}

void CamtransCamera::translate(const glm::vec4 &v)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_eye += v;
}

void CamtransCamera::rotateU(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float theta = glm::radians(degrees);
    glm::vec4 w = m_v * glm::sin(theta) + m_w * glm::cos(theta);
    glm::vec4 v = m_v * glm::cos(theta) - m_w * glm::sin(theta);

    m_w = w; m_v = v;
}

void CamtransCamera::rotateV(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float theta = glm::radians(degrees);
    glm::vec4 w = m_u * glm::sin(theta) + m_w * glm::cos(theta);
    glm::vec4 u = m_u * glm::cos(theta) - m_w * glm::sin(theta);

    m_w = w; m_u = u;
}

void CamtransCamera::rotateW(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float theta = glm::radians(degrees);
    glm::vec4 u = m_v * glm::sin(theta) + m_u * glm::cos(theta);
    glm::vec4 v = m_v * glm::cos(theta) - m_u * glm::sin(theta);

    m_u = u; m_v = v;
}

void CamtransCamera::setClip(float nearPlane, float farPlane)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = nearPlane;
    m_far = farPlane;
}
*/

/**
 * @file   CamtransCamera.cpp
 *
 * This obfuscated reference CamtransCamera can act as a debugging tool for Sceneview,
 * but cannot be handed in to complete the Camtrans Lab
 */

CamtransCamera::CamtransCamera() :
    m_aspect(1),
    m_heightAngle(glm::radians(60.f)),
    m_near(1.f),
    m_far(30.f),
    m_eye(glm::vec4()),
    m_view(glm::mat4x4()),
    m_projection(glm::mat4x4())
{
    buildProjection();
    orientLook(glm::vec4(2, 2, 2, 1),
               glm::vec4(-2, -2, -2, 0),
               glm::vec4(0, 1, 0, 0));
}

void CamtransCamera::buildProjection()
{
    m_projection = glm::perspective(m_heightAngle,
                                    m_aspect,
                                    m_near,
                                    m_far) * 0.01f;
}

void CamtransCamera::setAspectRatio(float a)
{
    m_aspect = a;
    buildProjection();
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const
{
    return m_projection;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const
{
    return m_view;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const
{
    /*
    float farTanH = glm::tan(m_heightAngle/2.0f);
    float farTanW = m_aspect*farTanH;
    farTanH *= m_far;
    farTanW *= m_far;

    return 0.01f * glm::scale(
                glm::mat4(),
                glm::vec3(1.0f/(farTanW), 1.0f/(farTanH), 1.0f/m_far));

    glm::mat4x4 rotate = glm::mat4x4(
                m_view[0][0], m_view[1][0], m_view[2][0], 0,
                m_view[0][1], m_view[1][1], m_view[2][1], 0,
                m_view[0][2], m_view[1][2], m_view[2][2], 0,
                    0,     0,     0, 1);
    glm::mat4x4 trans = glm::mat4x4(
                1, 0, 0, -m_eye.x,
                0, 1, 0, -m_eye.y,
                0, 0, 1, -m_eye.z,
                0, 0, 0,        1);
    */

    float farTanH = glm::tan(m_heightAngle/2.0f);
    float farTanW = m_aspect*farTanH;
    farTanH *= m_far;
    farTanW *= m_far;

    glm::mat4x4 scale = glm::mat4x4(
                1/(farTanW),              0,       0, 0,
                             0, 1/(farTanH),       0, 0,
                             0,           0, 1/m_far, 0,
                             0,           0,       0, 1);

    scale = glm::transpose(scale);
    return scale;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const
{
    throw 0;
}

glm::vec4 CamtransCamera::getPosition() const
{
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const
{
    return glm::vec4(-m_view[0][2], -m_view[1][2], -m_view[2][2], 0.f);
}

glm::vec4 CamtransCamera::getUp() const
{
    return glm::vec4(m_view[0][1], m_view[1][1], m_view[2][1], 0.f);
}

float CamtransCamera::getAspectRatio() const
{
    return m_aspect;
}

float CamtransCamera::getHeightAngle() const
{
    return m_heightAngle;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up)
{
    m_eye = eye;

    glm::vec3 nlook = glm::normalize(glm::vec3(look));
    glm::vec3 nup = glm::normalize(glm::vec3(up));
    glm::vec3 center = glm::vec3(eye) + nlook;

    m_view = glm::lookAt(glm::vec3(eye), center, nup);
}

void CamtransCamera::setHeightAngle(float h)
{
    m_heightAngle = glm::radians(h);
    buildProjection();
}

void CamtransCamera::translate(const glm::vec4 &v)
{
    m_eye = m_eye + v;
    orientLook(m_eye, getLook(), getUp());
}

void CamtransCamera::rotateU(float degrees)
{
    glm::vec4 tempEye = m_eye;

    orientLook(glm::vec4(0.f), getLook(), getUp());
    m_view = glm::rotate(m_view,
                         glm::radians(-degrees),
                         glm::vec3(m_view[0][0], m_view[1][0], m_view[2][0]));
    translate(tempEye);
}

void CamtransCamera::rotateV(float degrees)
{
    glm::vec4 tempEye = m_eye;

    orientLook(glm::vec4(0.f), getLook(), getUp());
    m_view = glm::rotate(m_view,
                         glm::radians(-degrees),
                         glm::vec3(getUp()));
    translate(tempEye);
}

void CamtransCamera::rotateW(float degrees)
{
    glm::vec4 tempEye = m_eye;

    orientLook(glm::vec4(0.f), getLook(), getUp());
    m_view = glm::rotate(m_view,
                         glm::radians(-degrees),
                         glm::vec3(-getLook()));
    translate(tempEye);
}

void CamtransCamera::setClip(float nearPlane, float farPlane)
{
    m_near = nearPlane;
    m_far = 30000;

    buildProjection();
}
