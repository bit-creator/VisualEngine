/**
 * @file material.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

enum class ColorTarget
{
    Ambient,
    Diffuse,
    Specular
};

class Material
{
    private:
        glm::vec4                           _ambientColor;
        glm::vec4                           _diffuseColor;
        glm::vec4                           _specularColor;
        float                               _roughness;
        GLenum                              _fillMode;

    public:
        Material() noexcept;
        ~Material() noexcept;

        void setColor(ColorTarget type, const glm::vec4& color) noexcept;
        void setColor(ColorTarget type, const float& r, const float& g, 
            const float& b, const float& a) noexcept;

        const glm::vec4& getColor(ColorTarget type) const noexcept;

        void setRoughness(const float& roughness) noexcept;
        const float& getRoughness() const noexcept;
        
        void setFill(const GLenum mode) noexcept;
        const GLenum getFill() const noexcept;
};

using MaterialPtr = std::shared_ptr<Material>;

#endif // MATERIAL_H