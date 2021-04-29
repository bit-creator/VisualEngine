#include "shaderprogram.h"

ShaderProgram::ShaderProgram() noexcept
    : GLObject(glCreateProgram())
{ HANDLE_GL_ERROR(); }

ShaderProgram::~ShaderProgram() noexcept {
	glDeleteProgram(getID()); HANDLE_GL_ERROR();
}

void ShaderProgram::attachShader(const Shader& shader) const noexcept {
    if (shader.compileShader()) {
    	glAttachShader(getID(), shader.getID()); HANDLE_GL_ERROR();
    }
}

void ShaderProgram::enable() const noexcept {
	glUseProgram(getID()); HANDLE_GL_ERROR();
}

bool ShaderProgram::link() const noexcept {
    glLinkProgram(getID()); HANDLE_GL_ERROR();

    GLint success;
    GLchar infoLog[512];

    glValidateProgram(getID()); HANDLE_GL_ERROR();

    glGetProgramiv(getID(), GL_LINK_STATUS, &success); HANDLE_GL_ERROR();

    if (!success) {
        glGetProgramInfoLog(getID(), 512, NULL, infoLog); HANDLE_GL_ERROR();
        ERROR(" Shader program no linked, problems:");
        std::cout << infoLog << '\n' << std::endl;

        return false;
    }

    return true;
}

GLuint ShaderProgram::getLocation(const std::string &name) const noexcept {
	if (!_locations.contains(name)) {
		_locations[name] = glGetUniformLocation(getID(), name.c_str());
	}
	return _locations[name];
}

// set Uniform //

void ShaderProgram::setUniform(const std::string& name,
		const float f1, const float f2,
		const float f3, const float f4) const noexcept {
    glUniform4f(getLocation(name), f1, f2, f3, f4);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat3x3& mat) const noexcept {
    glUniformMatrix3fv(getLocation(name), 1, false, glm::value_ptr(mat));
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vec) const noexcept {
    glUniform3f(getLocation(name), vec.x, vec.y, vec.z);
}

void ShaderProgram::setUniform(const std::string& name, const float flt) const noexcept {
    glUniform1f(getLocation(name), flt);
}

void ShaderProgram::setUniform(const std::string& name, const int val) const noexcept {
    glUniform1i(getLocation(name), val);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec4& vec) const noexcept {
    glUniform4f(getLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& mat) const noexcept {
    glUniformMatrix4fv(getLocation(name), 1, false, glm::value_ptr(mat));
}

