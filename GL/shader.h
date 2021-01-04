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

class Shader : public GLObject {
public:
	Shader(const GLuint shaderType) noexcept;
    ~Shader() noexcept;

    bool compileShader() const noexcept;
    void addSource(const std::string& source) const noexcept;
}; // Shader

std::string loadShaderFromFile(const std::string& path) noexcept;

using VertexShader = Shader;
using FragmentShader = Shader;

#endif // SHADER_H
