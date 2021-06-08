/**
 * @file engine.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "abstracteventlistener.hpp"
#include "AbstractNodePool.h"
#include "camera.h"
#include "ShaderFactory.h"
#include "object3d.h"
#include "window.h"
#include "scene.h"

#include "GL/shaderprogram.h"
#include "GL/Texture.h"
#include "GL/FrameBuffer.h"
#include "GL/ShadowBuffer.h"

#include "Geometry/Primitive/cube.h"
#include "Geometry/Primitive/rect.h"


class Engine {
	friend Object3D;
	friend Node;
	friend Light;

private:
	ScenePtr                        		 _scene;
    Cube	   								 _skyBox;
    Rect									 _screen;
    ShaderFactory							 _factory;
    FrameBuffer								 _FBO;
    ShadowBuffer							 _SBO;
    glm::mat3								 _postProcesingKernel;

private:
    std::vector < EventListenerPtr >		 _eventListeners;

private:
    Engine() noexcept;
    ~Engine() noexcept =default;
    Engine(const Engine&) =delete;
    Engine& operator =(const Engine&) =delete;

    void renderSkyBox();
    void renderScreen();
    void lightPass(LightList lights);
    void geometryPass(Object3D& obj) noexcept;

public:
    inline static const Window     window = Window(4.6f, 1920u, 1080u, "Visual Engine");

public:
    ObjectPool					   objects;
    LightPool					   lights;
    NodePool					   nodes;

public:
    static Engine&
    engine() noexcept;

    void addEventListener(EventListenerPtr eventListener);

    std::vector < EventListenerPtr >&
	getListeners() noexcept;

    void setScene(ScenePtr scene) noexcept;
    ScenePtr getScene() const noexcept;

    std::pair<int32_t, int32_t>
    getWindowSize() noexcept;

    void run(const Window& window = window) noexcept;

    template < typename NodeT >
    static inline NodeT* getPool() {
    	if constexpr (std::same_as<NodeT, Object3D>) return Engine::engine().objects.undegroundArray();
    	if constexpr (std::same_as<NodeT, Light>)	 return Engine::engine().lights.undegroundArray();
    	if constexpr (std::same_as<NodeT, Node>) 	 return Engine::engine().nodes.undegroundArray();
    	return nullptr;
    }

    float getPickerKey(const glm::vec2& mousePosition);

	const glm::mat3& getPostProcesingKernel() const;
	void setPostProcesingKernel(const glm::mat3 &postProcesingKernel);
};

#endif // ENGINE_H
