#include "camera.h"
#include "engine.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::mat4& projMatr, CameraType type = CameraType::CAMERA_CUSTOM) noexcept
    : Node(NodeType::NODE_CAMERA)
    , _projectionMatr(projMatr)
    , _type(type)
{  }

void Camera::setProjection(const glm::mat4& projMatr) noexcept {
	_projectionMatr = projMatr;
}

glm::mat4 Camera::getProjectionMatrix() const noexcept {
	return _projectionMatr;
}

CameraType Camera::getType() const noexcept {
	return _type;
}

Ray Camera::getRay(glm::vec2 screenPos) {
	Ray viewRay;

	auto vec = glm::inverse(_projectionMatr) * glm::vec4(screenPos, -1, 1);
	vec /= vec.w;
	glm::vec3 dir = glm::vec3(getWorldMat() * vec) - _position;

	viewRay.setOrigin(_position);
	viewRay.setDirection(dir);

	return viewRay;
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    : Camera(glm::ortho(left, right, bottom, top, near, far) *
        glm::mat4(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, -1,0,
                  0, 0, 0, 1), CameraType::CAMERA_ORTHOGRAPHIC)
{  }

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
    : Camera(glm::perspective(fovy, aspect, near, far) *
        glm::mat4(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, -1,0,
                  0, 0, 0, 1), CameraType::CAMERA_PERSPECTIVE)
{  }
