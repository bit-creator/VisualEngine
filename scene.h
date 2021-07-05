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

#include "AbstractNodePool.h"

#include "constants.hpp"


class Scene : public SharedCreator < Scene > {
private:
	glm::vec4									 _background;
    Camera					                     _camera;
    Node::reference			                     _root;
    TexPtr										 _skyBox;

public:
    ObjectPool					   objects;
    LightPool					   lights;
    NodePool					   nodes;

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

    Node::reference getRoot() const noexcept;

    Node::reference searchID(size_t ID);

    template < typename NodeT >
    NodeT* getPool();

    Node* getPool(NodeType type);
};

using ScenePtr = std::shared_ptr < Scene >;

template<typename NodeT>
inline NodeT* Scene::getPool() {
	if constexpr (std::same_as<NodeT, Camera>)   return getCamera();
 	if constexpr (std::same_as<NodeT, Object3D>) return objects.undegroundArray();
	if constexpr (std::same_as<NodeT, Light>)	 return lights.undegroundArray();
	if constexpr (std::same_as<NodeT, Node>) 	 return nodes.undegroundArray();
	return nullptr;
}

#endif // SCENE_H
