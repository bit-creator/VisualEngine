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
#include "object3d.h"
#include "window.h"

class Engine
{
    private:
        Engine() noexcept =default;
        ~Engine() noexcept =default;
        Engine(const Engine&) =delete;
        Engine& operator =(const Engine&) =delete;

        // std::vector<Window>    _window_array;
        inline static const Window     _mainWindow = Window(4.6f, "Visual Engine");

    public:
        static const Engine& 
        engine() noexcept;
        
        void run(const Object3D* tr, const Window& window = _mainWindow) const noexcept;
};

#endif // ENGINE_H