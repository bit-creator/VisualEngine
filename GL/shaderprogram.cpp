#include "shaderprogram.h"

ShaderProgram::ShaderProgram() noexcept
    : GLObject(glCreateProgram())
{ CHECK_GL_ERROR(); }

ShaderProgram::~ShaderProgram() noexcept {
	glDeleteProgram(getID()); CHECK_GL_ERROR();
}

void ShaderProgram::attachShader(const Shader& shader) const noexcept {
    if (shader.compileShader()) {
    	glAttachShader(getID(), shader.getID()); CHECK_GL_ERROR();
    }
}

void ShaderProgram::enable() const noexcept {
	glUseProgram(getID()); CHECK_GL_ERROR();
}

bool ShaderProgram::link() const noexcept {
    glLinkProgram(getID()); CHECK_GL_ERROR();

    GLint success;
    GLchar infoLog[512];

    glValidateProgram(getID()); CHECK_GL_ERROR();

    glGetProgramiv(getID(), GL_LINK_STATUS, &success); CHECK_GL_ERROR();

    if (!success) {
        glGetProgramInfoLog(getID(), 512, NULL, infoLog); CHECK_GL_ERROR();
        std::cout << "\n| ERROR | Shader program no linked, problems:\n" << infoLog << '\n' << std::endl;

        return false;
    }
    return true;
}

void ShaderProgram::setUniform(const std::string& name,
    const float f1, const float f2, 
    const float f3, const float f4) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform4f(loc, f1, f2, f3, f4);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat3x3& mat) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniformMatrix3fv(loc, 1, false, glm::value_ptr(mat));
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vec) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void ShaderProgram::setUniform(const std::string& name, const float flt) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform1f(loc, flt);
}

void ShaderProgram::setUniform(const std::string& name, const int val) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform1i(loc, val);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec4& vec) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& mat) const noexcept {
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(mat));
}
