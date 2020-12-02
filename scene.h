/**
 * @file scene.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "camera.h"
#include "object3d.h"

struct Scene
{
    std::shared_ptr<Camera>                     _camera;
    std::shared_ptr<Object3D>                   _object;
};

#endif // SCENE_H