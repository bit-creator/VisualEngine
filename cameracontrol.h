/**
 *
 *
 */

#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <glm/glm.hpp>

#include "abstracteventlistener.hpp"
#include "camera.h"
#include "CreateAsPointer.hpp"

class CameraControl : virtual
	public EventListener,
	public SharedCreator < CameraControl > {
private:
	Entity::reference							_camera;

private:		// move param
	glm::vec3 							_direction;
    glm::vec3 							_eilerAngle;
    float 								_velocity;

public:
	CameraControl(Entity::reference camera) noexcept;
    virtual ~CameraControl() noexcept override;

    void setVelocity(float velocity) noexcept;

private:
	void onRender() noexcept override;
    void onKeyPressed(int key, int scancode, int action, int mode) noexcept override;
    void onMouseMove(double x, double y) noexcept override;
};

#endif // CAMERACONTROL_H
