#include <GLFW/glfw3.h>

#include "cameracontrol.h"
#include "constants.hpp"

CameraControl::CameraControl(CameraPtr camera) noexcept
	: _camera(camera)
	, _direction(glm::vec3(0.0f, 0.0f, 0.0f))
	, _eilerAngle(glm::vec3(0.0f, 0.0f, 0.0f))
	, _velocity(0.05f)
{  }

CameraControl::~CameraControl() noexcept {
}

void CameraControl::onRender() noexcept {
    auto posDelta = _velocity * glm::mat3(_camera->getModelMat()) * _direction;
    auto position = _camera->getPosition() + posDelta;

	_camera -> setRotate(_eilerAngle);
    _camera -> setPosition(position);
}

void CameraControl::onKeyPressed (int key, int scancode, int action, int mode) noexcept {
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W) _direction.z = 1;
		if (key == GLFW_KEY_S) _direction.z = -1;
		if (key == GLFW_KEY_A) _direction.x = -1;
		if (key == GLFW_KEY_D) _direction.x = 1;
	}

	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_D || key == GLFW_KEY_A) _direction.x = 0;
		if (key == GLFW_KEY_W || key == GLFW_KEY_S) _direction.z = 0;
	}
}

void CameraControl::onMouseMove (double x, double y) noexcept {
	_eilerAngle += glm::vec3(y * 0.002, x * 0.002, 0.);
	if(_eilerAngle.x > PI / 2) _eilerAngle.x = PI / 2;
	if(_eilerAngle.x < -PI / 2) _eilerAngle.x = -PI / 2;
}

void CameraControl::setVelocity(float velocity) noexcept {
	_velocity = velocity;
}
