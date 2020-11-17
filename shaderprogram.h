/**
 * @file shaderprogram.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "globject.hpp"
#include "shader.h"

class ShaderProgram : public GLObject
{
    public:
        ShaderProgram() noexcept;
        ShaderProgram(const ShaderProgram&) =delete;
        ShaderProgram& operator=(const ShaderProgram&) =delete;
        ~ShaderProgram() noexcept;

        bool attachShader(const Shader& shader) const noexcept;
        bool link() const noexcept;
        void enable() const noexcept;

        // set Uniform //

        void setUniform(const std::string& name,
            const float& f1, const float& f2, 
            const float& f3, const float& f4) const noexcept;
};

#endif // SHADERPROGRAM_H