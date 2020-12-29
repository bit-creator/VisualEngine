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

#include "GL/shaderprogram.h"
#include "GL/Texture.h"

#include "abstracteventlistener.hpp"
#include "orthographiccamera.h"
#include "perspectivecamera.h"
#include "object3d.h"
#include "window.h"
#include "scene.h"

class Engine
{
    private:
        ScenePtr                        		 _scene;

    private:
        std::vector < EventListenerPtr >		 _eventListeners;

    private:
        Engine() noexcept =default;
        ~Engine() noexcept =default;
        Engine(const Engine&) =delete;
        Engine& operator =(const Engine&) =delete;

        // std::vector<Window>    _window_array;
        inline static const Window     _mainWindow = Window(4.6f, 1366u, 720u, "Visual Engine");

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

        void run(const Window& window = _mainWindow) noexcept;

        void render(Object3D& obj, Camera& cam, LightList lights, ShaderProgram& prg) noexcept;
};

std::string getLightsName(const int index);

#endif // ENGINE_H
