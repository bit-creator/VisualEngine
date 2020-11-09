#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <tuple>
#include <vector>
#include <fstream>

enum class Shaders
{
    vertex,
    fragment,
    geometry,
    // etc...
};

enum class LoadMethod
{ filePath, sourceCode };

template<Shaders type>
    class Shader
    {
    private:
        GLuint                          _shader;

    public:

        Shader() noexcept : _shader(glCreateShader(getCreateArg())) { }

        constexpr Shader(const char* data, const LoadMethod method = LoadMethod::filePath)
            : Shader()
        {
            if (method == LoadMethod::sourceCode)
                glShaderSource(_shader, 1, &data, NULL);

            if (method == LoadMethod::filePath) loadShaderFromFile(data);
        }

        constexpr Shader(const std::string& data, const LoadMethod& method = LoadMethod::filePath)
            : Shader()
        {
            if (method == LoadMethod::sourceCode)
            {
                const char* source = new char [data.size() + 1];
                source = data.c_str();
                glShaderSource(_shader, 1, &source, NULL);
                delete [] source;
            }

            if (method == LoadMethod::filePath) loadShaderFromFile(data);
        }

        ~Shader() noexcept
        {
            glDeleteShader(_shader);
        }

        const auto&
        get() const noexcept
        { return _shader; }

        void
        compile() const noexcept
        {
            glCompileShader(_shader);

            GLint success;

            GLchar infoLog[512];

            glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

            if(!success)
            {
        	   glGetShaderInfoLog(_shader, 512, NULL, infoLog);
               std::cout << "|    EROR     | Compile shader\n\n" << infoLog << std::endl;
            }
        }

        Shader(const Shader& other) = delete;
        Shader(Shader&& other) = delete;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other) = delete;

    private:
        auto getCreateArg() const noexcept
        {
            if (type == Shaders::vertex)   return GL_VERTEX_SHADER;
            if (type == Shaders::fragment) return GL_FRAGMENT_SHADER;
            if (type == Shaders::geometry) return GL_GEOMETRY_SHADER;
        }

        void loadShaderFromFile(const char* data) const
        {
            std::ifstream in(data, std::ios::in);
            if (in.is_open())
            {
                if (in.peek() != EOF)
                {
                    std::vector<std::string> sourceArray;
                    while (getline(in, *sourceArray.insert(sourceArray.cend(), ""), '\n'))
                        {
                            if(auto line = sourceArray.rbegin(); line -> empty()) sourceArray.pop_back();
                            else line -> push_back('\n');
                        }

                    int counter = 0;
                    const char** source = new const char*[sourceArray.size()];

                    for(auto& sourceLine : sourceArray)
                    {
                        source[counter] = new char[sourceLine.size()];
                        source[counter] = sourceLine.c_str();
                        ++counter;
                    }

                    glShaderSource(_shader, sourceArray.size(), source, NULL);

                    delete [] source;
                    source = nullptr;
                    std::cout << "| SUCCSESSFUL | load shader source\n";
                }
                else std::cout << "|    EROR     | Shader source file is empty\n";
            }
            else  std::cout << "|    EROR     | Shader source file not open\n";
        }
    };

template<typename... types>
    void foo(types...) {  }

template<Shaders... types>
    class ShaderProgram
    {
    private:
        // std::tuple<const Shader<types>...>                     _shaders;
        GLuint                                                 _programm;

    public:
        ShaderProgram(const Shader<types>&... shaders)
            : _programm(glCreateProgram())
            // , _shaders(std::forward_as_tuple(shaders))
        {
            foo(attachShader(shaders)...);
            link();
            foo(deleteShaders(shaders)...);
        }

        void link() const noexcept
        {
            glLinkProgram(_programm);

            GLint success;
            GLchar infoLog[512];

            glValidateProgram(_programm);

            glGetProgramiv(_programm, GL_LINK_STATUS, &success);

            if (!success)
            {
                glGetProgramInfoLog(_programm, 512, NULL, infoLog);
                std::cout << "|    EROR     | Shader program no linked\n\n";
                std::cout << infoLog << std::endl;
            }
            std::cout << "| SUCCSESSFUL | linked shader programm\n";
        }

        void enable() const noexcept
        { glUseProgram(_programm); }

        void disable() const noexcept
        { glUseProgram(NULL); }

    private:
        template < Shaders type >
            Shaders attachShader(const Shader<type>& shader) const noexcept
            {
                shader.compile();
                glAttachShader(_programm, shader.get());
                return type;
            }

        template < Shaders type >
            Shaders deleteShaders(const Shader<type>& shader) const noexcept
            { glDeleteShader(shader.get()); return type; }

    };

using VertexShader   = Shader <  Shaders::vertex  >;
using FragmentShader = Shader < Shaders::fragment >;
using GeometryShader = Shader < Shaders::geometry >;

#endif // SHADERPROGRAM_HPP
