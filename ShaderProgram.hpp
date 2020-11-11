/**
 *
 * license
 *
 *
 * issues: need thread safety impliment
 *         need another shader types impliment
 *         need shader tree impliment
 *         need RAII wraper for Shaders
 *         need realise correct copy/move operations with shaders
 */

//////////////////////////////////////////////////
//                                              //
//       !!!WARNING: not thread safety          //
//                                              //
//////////////////////////////////////////////////

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <tuple>
#include <vector>
#include <fstream>

/**
 * @brief enumeration with types of shaders, generaly must have all type of shaders
 * need add other shader types
 */
enum class Shaders
{
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER,
    geometry = GL_GEOMETRY_SHADER,
    // etc...
};

/**
 * @brief enumeration with load method factor
 */
enum class LoadMethod
{ filePath, sourceCode };

/**
 * @class Shader is impliment interface for all shader types
 */
template<Shaders type>
    class Shader
    {
    private:
        GLuint                          _shader;                // shader ref

    public:
        /**
         * @brief default (constructor) init shader ref
         */
        Shader() noexcept : _shader(glCreateShader(static_cast<GLuint>(type))) { }

        /**
         * @brief (constructor) have load politics, path to file with shader,
         * @brief or source code, default load politics is path to file, also
         * @brief shader (constructor) have overloading for c-string
         * @need add enother string types (maybe string_view?)
         */
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

        /**
         * @brief (destructor) clear shader use OpenGL methods
         */
        ~Shader() noexcept
        { glDeleteShader(_shader); }

        /**
         * @brief returns reference to current shaders
         */
        const auto&
        get() const noexcept
        { return _shader; }

        /**
         * @brief imoliment compile processe, if shader load unsuccsesful have UB
         * @need rewrite for detach unssucsesful loading
         */
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
            else std::cout << "| SUCCSESSFUL | compile shader\n";
        }

        /**
         * @brief all copy/move operations blocked
         * @comment I dont know how realized correct copy for shaders, and move
         * @comment operstions relevant only in shaderr tree
         */
        Shader(const Shader& other) = delete;
        Shader(Shader&& other) = delete;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other) = delete;

    private:
        /**
         * @brief loading shader source code use path to file
         * @comment have many way to optimisation
         * @comment need check memory leaking
         */
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

template<typename... types>    //dikyi kostyl
    void foo(types...) {  }

/**
 * @class ShaderProgram realize dynamic shader linking, use pack of shader
 *        types using in this program, need init this type pack only if used default
 *        (constructor) in other situations shader types pack will be generate use
 *        (constructor) paramenrs, for use this get all shaders to (constructor)
 * @brief using setShaders after (constructor) with parametrs - UB
 * @brief double using setShaders - UB
 * @brief change shaders order - UB
 * @need  rewrite linkProgram & setShaders aka "use only first time" (maybe use singleton functor)
 */
template<Shaders... types>
    class ShaderProgram
    {
    private:
        // std::tuple<const Shader<types>...>                     _shaders;
        GLuint                                                 _programm;

    public:
        /**
         * @brief default (constructor) only create programm no attach shader
         */
        ShaderProgram()
            : _programm(glCreateProgram())
        {  }

        /**
         * @brief (constructor) work "in box"
         * @param shaders - shader pack in correct order
         */
        ShaderProgram(const Shader<types>&... shaders)
            : ShaderProgram()
            // , _shaders(std::forward_as_tuple(shaders))
        { linkProgram(shaders...); }

        /**
         * @brief seter for shaders work only if use default (constructor)
         * @param shaders - parametr pack with Shader objects in order equal
         *        order parametr pack in initialisation ShaderProgram
         */
        void setShaders(const Shader<types>&... shaders)
        { linkProgram(shaders...); }

        /**
         * @brief enable current shaderProgram
         * @brief automaticaly disable other shaderProgram
         */
        void enable() const noexcept
        { glUseProgram(_programm); }

        /**
         * @brief manual disabling shaderProgram
         */
        void disable() const noexcept
        { glUseProgram(NULL); }

    private:
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

        void
        linkProgram(const Shader<types>&... shaders) const noexcept
        {
            foo(attachShader(shaders)...);
            link();
            foo(deleteShaders(shaders)...);
        }

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
// etc..

#endif // SHADERPROGRAM_HPP
