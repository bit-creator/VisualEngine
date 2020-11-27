#include "shaderprogram.h"

ShaderProgram::ShaderProgram() noexcept
    : GLObject(glCreateProgram())
{  }

ShaderProgram::~ShaderProgram() noexcept
{ glDeleteProgram(getID()); }

bool ShaderProgram::attachShader(const Shader& shader) const noexcept
{
    bool res = shader.compileShader();
    glAttachShader(getID(), shader.getID());

    if(glGetError() == GL_NO_ERROR) return res;

    std::cout << "|    EROR     | attach shader\n" << "|             | " << glGetError() << '\n';
    return false;
}

void ShaderProgram::enable() const noexcept
{ glUseProgram(getID()); }

bool ShaderProgram::link() const noexcept
{
    glLinkProgram(getID());

    GLint success;
    GLchar infoLog[512];

    glValidateProgram(getID());

    glGetProgramiv(getID(), GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(getID(), 512, NULL, infoLog);
        std::cout << "|    EROR     | Shader program no linked\n\n";
        std::cout << infoLog << std::endl;
        return false;
    }
    std::cout << "| SUCCSESSFUL | linked shader programm\n";
    return true;
}

void ShaderProgram::setUniform(const std::string& name,
    const float f1, const float f2, 
    const float f3, const float f4) const noexcept
{
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform4f(loc, f1, f2, f3, f4);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat3x3& mat) const noexcept
{
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniformMatrix3fv(loc, 1, false, glm::value_ptr(mat));
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vec) const noexcept
{
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void ShaderProgram::setUniform(const std::string& name, const float flt) const noexcept
{
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform1f(loc, flt);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec4& vec) const noexcept
{
    GLint loc = glGetUniformLocation(getID(), name.c_str());

    glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}