#include "shader.h"

Shader::Shader(const GLuint shaderType) noexcept
    : GLObject(glCreateShader(shaderType))
{ CHECK_GL_ERROR(); }

Shader::~Shader() noexcept {
	glDeleteShader(getID()); CHECK_GL_ERROR();
}

bool Shader::compileShader() const noexcept {
	std::vector<char*> cstrings;
	cstrings.reserve(_shaderSources.size());

	for(size_t i = 0; i < _shaderSources.size(); ++i)
		cstrings.push_back(const_cast<char*>(_shaderSources[i].c_str()));

	glShaderSource(getID(), _shaderSources.size(), &cstrings[0], _shaderLength.data()); CHECK_GL_ERROR();

    glCompileShader(getID()); CHECK_GL_ERROR();

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(getID(), GL_COMPILE_STATUS, &success); CHECK_GL_ERROR();

    if(!success) {
	   glGetShaderInfoLog(getID(), 512, NULL, infoLog); CHECK_GL_ERROR();
       std::cout << "\n| ERROR | Shader not compile, problems:\n" << infoLog << '\n' << std::endl;

       return false;
    }

    return true;
}

void Shader::addSource(const std::string& source) noexcept {
    _shaderSources.push_back(source);
    _shaderLength.push_back(source.size());
}

VertexShader::VertexShader()
	: Shader(GL_VERTEX_SHADER)
{  }

FragmentShader::FragmentShader()
	: Shader(GL_FRAGMENT_SHADER)
{  }
