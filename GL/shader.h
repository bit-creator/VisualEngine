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
#include <string_view>

#include "globject.h"

class Shader : public GLObject {
private:
	std::vector < const char* >					_shaderSources;
	std::vector < GLint >		  			_shaderLength;

public:
	Shader(const GLuint shaderType) noexcept;
    ~Shader() noexcept;

    bool compileShader() const noexcept;
    void addSource(std::string_view source) noexcept;
}; // Shader


class VertexShader final : public Shader
{
public:
	VertexShader();
	~VertexShader() = default;
	VertexShader(VertexShader &&other) = default;
	VertexShader& operator=(VertexShader &&other) = default;
};

class FragmentShader final : public Shader
{
public:
	FragmentShader();
	~FragmentShader() = default;
	FragmentShader(FragmentShader &&other) = default;
	FragmentShader& operator=(FragmentShader &&other) = default;
};

using ShaderPtr = std::shared_ptr<Shader>;

#endif // SHADER_H
