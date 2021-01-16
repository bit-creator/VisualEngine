#include "camera.h"
#include "engine.h"

Camera::Camera(const glm::mat4& projMatr, CameraType type = CameraType::CAMERA_CUSTOM) noexcept
    : Node(NodeType::NODE_CAMERA)
    , _projectionMatr(projMatr)
    , _type(type)
{ getRay(); }

void Camera::setProjection(const glm::mat4& projMatr) noexcept
{ _projectionMatr = projMatr; }

glm::mat4 Camera::getProjectionMatrix() const noexcept
{ return _projectionMatr; }

CameraType Camera::getType() const noexcept
{
	return _type;
}

Ray Camera::getRay() {
	if(! _dirtyTransform && ! _dirtyWorldTransform) return _viewRay;

	_viewRay.setOrigin(_position);

	_viewRay.setDirection(glm::normalize(glm::vec3(glm::inverse(_projectionMatr)
			* glm::vec4(0, 0, -1, 1)) - _position));

	return _viewRay;
}
