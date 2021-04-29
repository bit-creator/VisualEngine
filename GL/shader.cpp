#include "shader.h"

Shader::Shader(const GLuint shaderType) noexcept
    : GLObject(glCreateShader(shaderType))
{ HANDLE_GL_ERROR(); }

Shader::~Shader() noexcept {
	glDeleteShader(getID()); HANDLE_GL_ERROR();
}

bool Shader::compileShader() const noexcept {
	glShaderSource(getID(), _shaderSources.size(), &_shaderSources[0], _shaderLength.data()); HANDLE_GL_ERROR();

    glCompileShader(getID()); HANDLE_GL_ERROR();

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(getID(), GL_COMPILE_STATUS, &success); HANDLE_GL_ERROR();

    if(!success) {
	   glGetShaderInfoLog(getID(), 512, NULL, infoLog); HANDLE_GL_ERROR();
	   ERROR("Shader not compile, problems:");
       std::cout << infoLog << '\n' << std::endl;

	   std::cout << _shaderSources[0];
	   std::cout << _shaderSources[1];
	   std::cout << _shaderSources[2];
	   std::raise(SIGTERM);
       return false;
    }

    return true;
}

void Shader::addSource(std::string_view source) noexcept {
    _shaderSources.push_back(source.data());
    _shaderLength.push_back(source.size());
}

VertexShader::VertexShader()
	: Shader(GL_VERTEX_SHADER)
{  }

FragmentShader::FragmentShader()
	: Shader(GL_FRAGMENT_SHADER)
{  }
