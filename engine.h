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

#include "GL/shaderprogram.h"
#include "object3d.h"
#include "window.h"

#include "perspectivecamera.h"


class EventListener
{
    public:
        virtual void onRender() noexcept =0;

        virtual ~EventListener(){
        }
};

using EventPointer = std::shared_ptr<EventListener>;

class Engine
{
    public:
        EventPointer                    _eventListener;

    private:
        Engine() noexcept =default;
        ~Engine() noexcept =default;
        // Engine(const Engine&) =delete;
        // Engine& operator =(const Engine&) =delete;

        // std::vector<Window>    _window_array;
        inline static const Window     _mainWindow = Window(4.6f, 720u, 720u, "Visual Engine");

    public:
        static Engine& 
        engine() noexcept;

        void addEventListener(EventPointer eventListener);

        std::pair<int32_t, int32_t> 
        getWindowSize() noexcept;

        void run(Object3D* tr, const Window& window = _mainWindow) noexcept;


};

#endif // ENGINE_H