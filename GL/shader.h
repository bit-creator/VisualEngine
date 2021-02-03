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
#include <memory>

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


class VertexShader final : public Shader
{
public:
	VertexShader();
	~VertexShader() = default;
	VertexShader(const VertexShader &other) = delete;
	VertexShader(VertexShader &&other) = default;
	VertexShader& operator=(const VertexShader &other) = delete;
	VertexShader& operator=(VertexShader &&other) = default;
};

class FragmentShader final : public Shader
{
public:
	FragmentShader();
	~FragmentShader() = default;
	FragmentShader(const FragmentShader &other) = delete;
	FragmentShader(FragmentShader &&other) = default;
	FragmentShader& operator=(const FragmentShader &other) = delete;
	FragmentShader& operator=(FragmentShader &&other) = default;
};

std::string loadShaderFromFile(const std::string& path) noexcept;

using ShaderPtr = std::shared_ptr<Shader>;

#endif // SHADER_H
