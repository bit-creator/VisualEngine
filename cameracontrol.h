/**
 *
 *
 */

#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "abstracteventlistener.hpp"
#include "camera.h"

class CameraControl : public EventListener
{
	private:
		CameraPtr							_camera;

	private:		// move param
    	glm::vec3 							_direction;
    	glm::vec3 							_eilerAngle;
    	float 								_velocity;

	public:
    	CameraControl(CameraPtr camera) noexcept;
    	virtual ~CameraControl() noexcept override;

    	void setVelocity(float velocity) noexcept;

    	void onRender() noexcept override;
    	void onKeyPressed(int key, int scancode, int action, int mode) noexcept override;
    	void onMouseMove(double x, double y) noexcept override;
};

#endif // CAMERACONTROL_H
