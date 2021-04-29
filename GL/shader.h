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

/**
 * !!!! refactoring !!!!
 * 1) common pieces of shader code must contained in one file.
 * 2) attribute location must synchronized with buffer and contained in one file
 * 3) defaines and macroses must contained in including file
 * 4) ??? how its chenged factory code???
 * 5) create Draw Data structure ??? what this structure must contained ???
 * 6) synchronize scene param and defines contained in shader
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
//	VertexShader(const VertexShader &other) = delete;
	VertexShader(VertexShader &&other) = default;
//	VertexShader& operator=(const VertexShader &other) = delete;
	VertexShader& operator=(VertexShader &&other) = default;
};

class FragmentShader final : public Shader
{
public:
	FragmentShader();
	~FragmentShader() = default;
//	FragmentShader(const FragmentShader &other) = delete;
	FragmentShader(FragmentShader &&other) = default;
//	FragmentShader& operator=(const FragmentShader &other) = delete;
	FragmentShader& operator=(FragmentShader &&other) = default;
};

using ShaderPtr = std::shared_ptr<Shader>;

#endif // SHADER_H
