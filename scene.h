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
#include "CreateAsPointer.hpp"
#include "object3d.h"
#include "Light.h"

#include "constants.hpp"


using DrawList = std::vector < Object3D* >;
using LightList = std::vector < Light* >;

class Scene : public SharedCreator < Scene > {
private:
	glm::vec4									 _background;
    Camera					                     _camera;
    NodePtr			                             _root;
    TexPtr										 _skyBox;

public:
    Scene() noexcept;
    Scene(const Scene&) noexcept =delete;
    Scene& operator =(const Scene&) noexcept =delete;
    ~Scene() noexcept =default;

public:
    void setCamera(Camera camera) noexcept;
    Camera* getCamera() noexcept;

    void setBackgroundColor(const glm::vec4& color) noexcept;
    const glm::vec4& getBackgroundColor() const noexcept;

    void loadSkyboxImage(BoxSide side, TexPtr skyBox, std::string filename);

    void disableSkyBox();
    bool useSkyBox() const;

    void setSkyBox(TexPtr skyBox);
    TexPtr getSkyBox() const;

    NodePtr getRoot() const noexcept;

    DrawList getDrawList() const noexcept;
    LightList getLightList() const noexcept;


private:
    void getDrawListImpl(DrawList& list, const NodePtr& obj) const noexcept;
    void getLightListImpl(LightList& list, const NodePtr& obj) const noexcept;
};

using ScenePtr = std::shared_ptr < Scene >;

#endif // SCENE_H
