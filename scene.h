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
#include <vector>

#include "camera.h"
#include "perspectivecamera.h"
#include "object3d.h"

using DrawList = std::vector < Object3D* >;

class Scene
{
private:
	glm::vec4									 _background;
    CameraPtr				                     _camera;
    NodePtr			                             _root;

public:
    Scene() noexcept;
    Scene(const Scene&) noexcept =delete;
    Scene& operator =(const Scene&) noexcept =delete;
    ~Scene() noexcept =default;

    void setCamera(CameraPtr camera) noexcept;
    CameraPtr getCamera() const noexcept;

    void setBackgroundColor(const glm::vec4& color) noexcept;
    const glm::vec4& getBackgroundColor() const noexcept;

    NodePtr getRoot() const noexcept;

    DrawList getDrawList() const noexcept;

private:
    void getDrawListImpl(DrawList& list, const NodePtr& obj) const noexcept;
};

using ScenePtr = std::shared_ptr < Scene >;

#endif // SCENE_H
