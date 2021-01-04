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
#include "Light.h"

using DrawList = std::vector < Object3D* >;
using LightList = std::vector < Light* >;

class Scene
{
private:
	glm::vec4									 _background;
    CameraPtr				                     _camera;
    NodePtr			                             _root;
    TexPtr										 _skyBox;
    bool 										 _useSkyBox;

public:
    Light										 _light;

    Scene() noexcept;
    Scene(const Scene&) noexcept =delete;
    Scene& operator =(const Scene&) noexcept =delete;
    ~Scene() noexcept =default;

    void setCamera(CameraPtr camera) noexcept;
    CameraPtr getCamera() const noexcept;

    void setBackgroundColor(const glm::vec4& color) noexcept;
    const glm::vec4& getBackgroundColor() const noexcept;

    void loadSkyboxImage(SkyBox side, TexPtr skyBox, std::string filename);

    void enableSkyBox();
    void disableSkyBox();
    bool useSkyBox() const;

    NodePtr getRoot() const noexcept;

    DrawList getDrawList() const noexcept;
    LightList getLightList() const noexcept;


private:
    void getDrawListImpl(DrawList& list, const NodePtr& obj) const noexcept;
    void getLightListImpl(LightList& list, const NodePtr& obj) const noexcept;
};

using ScenePtr = std::shared_ptr < Scene >;

#endif // SCENE_H
