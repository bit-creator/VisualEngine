/**
 * @file shadertree.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SHADERTREE_H
#define SHADERTREE_H

#include <map>
#include <filesystem>
#include <iostream>
#include <string>

#include "shader.h"

namespace fs = std::filesystem;

using shaderTree = std::map<std::string, Shader>;

class ShaderTree
{
    private:
        shaderTree              _vertexShaderTree;
        shaderTree              _fragmentShaderTree;
        
        ShaderTree() noexcept =default;
        ShaderTree(const ShaderTree&) =delete;
        ShaderTree& operator =(const ShaderTree&) =delete;
        ~ShaderTree() noexcept =default;

        void validate(const std::string& filePath, 
            typename shaderTree::const_iterator node) const noexcept;

    public:
        void initShaderTree(const std::string& path) noexcept;
        static ShaderTree& get() noexcept;
        static const shaderTree& getVertTree() noexcept;
        static const shaderTree& getFragTree() noexcept;
};

#endif // SHADERTREE_H