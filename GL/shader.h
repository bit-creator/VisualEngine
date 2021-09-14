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

#include <vector>
#include <memory>
#include <string_view>

#include "RowGraphicObject.h"

class Shader: public RowGraphicObject<
	Creators::shader,
	Deleters::shader
> {
private:
	std::vector < const char* >					_shaderSources;
	std::vector < uint32_t >		  				_shaderLength;

protected:
	Shader(const uint32_t shaderType) noexcept;

public:
    ~Shader() noexcept;

    bool compileShader() const noexcept;
    void addSource(std::string_view source) noexcept;
}; // Shader


struct VertexShader: public Shader {
	VertexShader();
};

struct FragmentShader: public Shader {
	FragmentShader();
};

using ShaderPtr = std::shared_ptr<Shader>;

#endif // SHADER_H
