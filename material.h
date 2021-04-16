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

#include <glm/glm.hpp>

#include "Color.h"

#include "GL/Texture.h"

enum class MaterialType {
	MATERIAL_BUMP,
	MATERIAL_PHONG,
	MATERIAL_GLASS,
	MATERIAL_GLOSSY
};

class Material {
private:
	MaterialType						_type;

	TexPtr								_ambientMap;
	TexPtr								_diffuseMap;
	TexPtr								_specularMap;
	TexPtr								_normalMap;
	TexPtr								_heightMap;

    Color       	                    _ambientColor;
    Color   	                        _diffuseColor;
    Color	                            _specularColor;

    float                               _roughness;
    GLenum                              _fillMode;

protected:
    Material(MaterialType type) noexcept;

public:
    ~Material() noexcept;

    MaterialType getType() const;
//    void setType(MaterialType type);

    void setAmbientColor(const Color color) noexcept;
    void setDiffuseColor(const Color color) noexcept;
    void setSpecularColor(const Color color) noexcept;

    const Color& getAmbientColor() const noexcept;
    const Color& getDiffuseColor() const noexcept;
    const Color& getSpecularColor() const noexcept;

    void setAmbientTexture(TexPtr map);
    void setDiffuseTexture(TexPtr map);
    void setSpecularTexture(TexPtr map);
    void setNormalTexture(TexPtr map);
    void setHeightTexture(TexPtr map);

    TexPtr getAmbientTexture() const noexcept;
    TexPtr getDiffuseTexture() const noexcept;
    TexPtr getSpecularTexture() const noexcept;
    TexPtr getNormalTexture() const noexcept;
    TexPtr getHeightTexture() const noexcept;

    void setRoughness(const float roughness) noexcept;
    const float getRoughness() const noexcept;
        
    void setPolygonsFillMode(const GLenum mode) noexcept;
    const GLenum getPolygonsFillMode() const noexcept;
};

class BumpMaterial : public Material {
public:
	BumpMaterial();
	float 				_scale = 0.2;
};

class PhongMaterial : public Material {
public:
	PhongMaterial();
};

class GlassMaterial : public Material {
public:
	GlassMaterial();
};

class GlossyMaterial : public Material {
public:
	GlossyMaterial();
};

using MaterialPtr = std::shared_ptr<Material>;

#endif // MATERIAL_H
