#include "camera.h"

Camera::Camera(const glm::mat4& projMatr, CameraType type = CameraType::CAMERA_CUSTOM) noexcept
    : Node(NodeType::NODE_CAMERA)
    , _projectionMatr(projMatr)
    , _type(type)
{  }

void Camera::setProjection(const glm::mat4& projMatr) noexcept
{ _projectionMatr = projMatr; }

glm::mat4 Camera::getProjectionMatrix() const noexcept
{ return _projectionMatr; }

CameraType Camera::getType() const noexcept
{ return _type; }


