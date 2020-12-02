/**
 * @file perspectivecamera.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

class PerspectiveCamera : public Camera
{
    public:
        PerspectiveCamera(float fovy, float aspect, float near, float far);

};

#endif // PERSPECTIVECAMERA_H