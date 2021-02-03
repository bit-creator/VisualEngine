#include "camera.h"
#include "engine.h"

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
{
	return _type;
}

Ray Camera::getRay(glm::vec2 screenPos) {
	Ray viewRay;

//	float near = 0.1;

	auto vec = glm::inverse(_projectionMatr) * glm::vec4(screenPos, -1, 1);

//	auto vec = glm::vec4(0.0, 0.0, near, 10);

	vec /= vec.w;

//	std::cout << glm::to_string(glm::vec3(vec)) << std::endl;

	viewRay.setOrigin(_position);

	glm::vec3 dir = glm::vec3(getWorldMat() * vec) - _position;
//	std::cout << glm::to_string(dir) << std::endl;

	viewRay.setDirection(dir);

	return viewRay;
}
