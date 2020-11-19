#include "shadertree.h"


const shaderTree&
ShaderTree::getVertTree() noexcept
{ static ShaderTree tree; return tree._vertexShaderTree; }

const shaderTree&
ShaderTree::getFragTree() noexcept
{ static ShaderTree tree; return tree._fragmentShaderTree; }

ShaderTree&
ShaderTree::get() noexcept
{ static ShaderTree tree; return tree; }

void
ShaderTree::initShaderTree(const std::string& path) noexcept
{
    std::cout << "|    INFO    | start shader compilation process\n";
    for (const auto& filePath : fs::recursive_directory_iterator(path))
    {
        if(filePath.is_directory()) continue;
        auto name = filePath.path();
        for(; !name.extension().empty(); name = name.stem())
        {
            if (name.extension() == ".vert")
            {
                const auto [iterator, insert] = _vertexShaderTree.emplace(std::make_pair
                    (name.string(), std::move(Shader(GL_VERTEX_SHADER))));

                std::cout << "\t\t| SUCCSESSFUL | "<< name << " vertex shader insert\n";

                validate(filePath.path(), iterator);
                
                break;
            }
            if (name.extension() == ".frag")
            {
                const auto [iterator, insert] = _fragmentShaderTree.emplace(std::make_pair
                    (name.string(), std::move(Shader(GL_FRAGMENT_SHADER))));

                std::cout << "\t\t| SUCCSESSFUL | "<< name << " fragment shader insert\n";

                validate(filePath.path(), iterator);

                break;
            }
        }
    }    
}

void ShaderTree::validate(const std::string& filePath, 
    typename shaderTree::const_iterator node) const noexcept
{
    node -> second.addSource(loadShaderFromFile(filePath));
    node -> second.compileShader();
}
