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