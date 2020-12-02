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

#include <glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

enum class CameraType
{
    PERSPECTIVE = 1,
    ORTHOGRAPHIC = 0
};

class Camera
{
    private:
        float                           _nearPlane;
        float                           _farPlane;
        glm::mat4                       _projectionMatr;
        CameraType                      _type;

    public:
        Camera(CameraType type, const glm::mat4& projMatr, const float near, const float far) noexcept;

        void setProjection(CameraType type, const glm::mat4& projMatr, const float near, const float far) noexcept;
        glm::mat4 getProjectionMatrix() const noexcept;

        float getNearPlane() const;

        float getFarPlane() const;

        CameraType getType() const noexcept;
};

#endif // CAMERA_H
