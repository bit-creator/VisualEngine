/**
 * @file camera.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include "node.h"
#include "Ray.h"

enum class CameraType
{
    CAMERA_PERSPECTIVE = 1,
    CAMERA_ORTHOGRAPHIC = 0,
    CAMERA_CUSTOM = 2
};

class Camera : virtual
	public Node,
	public MultiSharedCreator<Camera, Node> {
private:
	glm::mat4                       _projectionMatr;
    const CameraType                _type;

public:
	Camera(const glm::mat4& projMatr, CameraType type) noexcept;

    void setProjection(const glm::mat4& projMatr) noexcept;
        
    glm::mat4 getProjectionMatrix() const noexcept;

    CameraType getType() const noexcept;

  	Ray getRay(glm::vec2 screenPos);
};

class OrthographicCamera : public Camera {
public:
	OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);
};

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(float fovy, float aspect, float near, float far);
};

using CameraPtr = std::shared_ptr<Camera>;

#endif // CAMERA_H
