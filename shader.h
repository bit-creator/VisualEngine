/**
 * @file shader.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "globject.hpp"

/**
 * @brief impliment work with single shader
 *        inherit GLObject properties
 */
class Shader : public GLObject
{
    public:
        /**
         * @brief Construct a new Shader object
         *        copy/move operations with shader
         *        prohibited
         */
        Shader(const GLuint shaderType) noexcept;

        ~Shader() noexcept;

        /**
         * @brief impliment compile process for
         *        shader (use OGL func)
         * 
         * @return true if compile sucessesfull
         */
        bool
        compileShader() const noexcept;

        /**
         * @brief load shader in memory use 
         *        source string of chapters
         * 
         * @param source string with shader
         */
        void 
        addSource(const std::string& source) const noexcept;
}; // Shader

std::string loadShaderFromFile(const std::string& path) noexcept;

using VertexShader = Shader;
using FragmentShader = Shader;

#endif // SHADER_H