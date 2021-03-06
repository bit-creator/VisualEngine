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

#include <map>

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../CreateAsPointer.hpp"

class ShaderProgram :
	public GLObject,
	public UniqueCreator<ShaderProgram> {
private:
	mutable std::map<std::string, GLuint>						_locations;

public:
	ShaderProgram() noexcept;
    ~ShaderProgram() noexcept;

    void attachShader(const Shader& shader) const noexcept;
    bool link() const noexcept;
    void enable() const noexcept;

private:
    GLuint getLocation(const std::string& name) const noexcept;

public:  // set Uniform //
    void setUniform(const std::string& name,
    	const float f1, const float f2,
		const float f3, const float f4) const noexcept;

	void setUniform(const std::string& name, const glm::mat3& mat) const noexcept;
    void setUniform(const std::string& name, const glm::mat4& mat) const noexcept;

    void setUniform(const std::string& name, const glm::vec3& vec) const noexcept;
    void setUniform(const std::string& name, const glm::vec4& vec) const noexcept;
        
    void setUniform(const std::string& name, const float flt) const noexcept;
    void setUniform(const std::string& name, const int val) const noexcept;
};

using PrgPtr = std::unique_ptr < ShaderProgram >;

#endif // SHADERPROGRAM_H
