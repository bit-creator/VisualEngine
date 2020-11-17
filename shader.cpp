#include "shader.h"

Shader::Shader(const GLuint shaderType) noexcept
    : GLObject(glCreateShader(shaderType))
{  }

Shader::~Shader() noexcept
{ glDeleteShader(getID()); }

bool Shader::compileShader() const noexcept
{
    glCompileShader(getID());
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(getID(), GL_COMPILE_STATUS, &success);
    if(!success)
    {
	   glGetShaderInfoLog(getID(), 512, NULL, infoLog);
       std::cout << "\t\t|    EROR     | Compile shader\n\n" << infoLog << std::endl;
             
       return false;
    }
    else std::cout << "\t\t| SUCCSESSFUL | compile shader\n";
    return true;
}

void Shader::addSource(const std::string& source) const noexcept
{
    auto sourceArray = source.c_str();
    glShaderSource(getID(), 1, &sourceArray, NULL); 
}

std::string loadShaderFromFile(const std::string& path) noexcept
{
    std::ifstream in(path, std::ios::in);
    if (in.is_open())
    {
        if (in.peek() != EOF)
        {
            std::string source = "", sourceline = "\n";
            while (getline(in, sourceline, '\n'))
                {
                    if(!sourceline.empty()) source.append(sourceline);
                    else source.push_back('\n');
                }
            std::cout << "\t\t| SUCCSESSFUL | load shader source\n";
            return source.c_str();
        }
        else std::cout << "\t\t|    EROR     | Shader source file is empty\n";
    }
    else  std::cout << "\t\t|    EROR     | Shader source file not open\n";
    return std::string("").c_str();
}
