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

#include "Color.h"

#include "GL/Texture.h"

class Material
{
    private:
		TexPtr								_ambientMap;
		TexPtr								_diffuseMap;
		TexPtr								_specularMap;

        Color       	                    _ambientColor;
        Color   	                        _diffuseColor;
        Color	                            _specularColor;
        float                               _roughness;
        GLenum                              _fillMode;

    public:
        Material() noexcept;
        ~Material() noexcept;

        void setAmbientColor(const Color color) noexcept;
        void setDiffuseColor(const Color color) noexcept;
        void setSpecularColor(const Color color) noexcept;

        const Color& getAmbientColor() const noexcept;
        const Color& getDiffuseColor() const noexcept;
        const Color& getSpecularColor() const noexcept;

        void setAmbientTexture(TexPtr map);
        void setDiffuseTexture(TexPtr map);
        void setSpecularTexture(TexPtr map);

        TexPtr getAmbientTexture() const noexcept;
        TexPtr getDiffuseTexture() const noexcept;
        TexPtr getSpecularTexture() const noexcept;

        void setRoughness(const float roughness) noexcept;
        const float getRoughness() const noexcept;
        
        void setPolygonsFillMode(const GLenum mode) noexcept;
        const GLenum getPolygonsFillMode() const noexcept;

};

using MaterialPtr = std::shared_ptr<Material>;

#endif // MATERIAL_H
