#include "camera.h"

float Camera::getNearPlane() const
{ return _nearPlane; }

float Camera::getFarPlane() const
{ return _farPlane; }

Camera::Camera(const glm::mat4& projMatr, const float near, const float far) noexcept
    : _projectionMatr(projMatr)
    , _nearPlane(near)
    , _farPlane(far)
{  }

void Camera::setProjection(const glm::mat4& projMatr, const float near, const float far) noexcept
{
    _projectionMatr = projMatr;
    _nearPlane = near;
    _farPlane = far;
}

glm::mat4 Camera::getProjectionMatrix() const noexcept
{ return _projectionMatr; }



