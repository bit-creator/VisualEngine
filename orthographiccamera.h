/**
 * @file orthographicCamera.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "camera.h"

class OrthographicCamera : public Camera
{
    private:

    public:
        OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);
};

#endif // ORTHOGRAPHICCAMERA_H