#include "camera.h"

float Camera::getNearPlane() const
{ return _nearPlane; }

float Camera::getFarPlane() const
{ return _farPlane; }

Camera::Camera(CameraType type, const glm::mat4& projMatr, const float near, const float far) noexcept
    : _projectionMatr(projMatr)
    , _nearPlane(near)
    , _farPlane(far)
    , _type(type)
{  }

void Camera::setProjection(CameraType type, const glm::mat4& projMatr, const float near, const float far) noexcept
{
    _projectionMatr = projMatr;
    _nearPlane = near;
    _farPlane = far;
    _type = type;
}

glm::mat4 Camera::getProjectionMatrix() const noexcept
{ return _projectionMatr; }

CameraType Camera::getType() const noexcept
{ return _type; }


