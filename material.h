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

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "GL/Texture/Texture.h"

enum class ColorTarget
{
    Ambient,
    Diffuse,
    Specular
};

enum class MapTarget
{
    Ambient =0,
    Diffuse =1,
    Specular =2,
	Normal
};

class Material
{
    private:
		TexPtr								_ambientMap;
		TexPtr								_diffuseMap;
		TexPtr								_specularMap;

        glm::vec4                           _ambientColor;
        glm::vec4                           _diffuseColor;
        glm::vec4                           _specularColor;
        float                               _roughness;
        GLenum                              _fillMode;

    public:
        Material() noexcept;
        ~Material() noexcept;

        void setColor(ColorTarget type, const glm::vec4& color) noexcept;
        void setColor(ColorTarget type, const float r, const float g, 
            const float b, const float a) noexcept;

        const glm::vec4& getColor(ColorTarget type) const noexcept;

        void setMap(MapTarget type, TexPtr map);
        TexPtr getMap(MapTarget type) const noexcept;
        bool hasMap(MapTarget type) const noexcept;
        void bindMaps() noexcept;
        void unbindMaps() noexcept;

        void setRoughness(const float roughness) noexcept;
        const float getRoughness() const noexcept;
        
        void setPolygonsFillMode(const GLenum mode) noexcept;
        const GLenum getPolygonsFillMode() const noexcept;

};

const int mapUnit(MapTarget type) noexcept;

using MaterialPtr = std::shared_ptr<Material>;

#endif // MATERIAL_H
