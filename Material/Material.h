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

#include "../Color.h"

#include "../GL/Texture.h"
#include "MaterialTypes.hpp"
#include "../GL/shaderprogram.h"
#include "../Draw.h"

class Material {
protected:
	MaterialType						_type;

	TexPtr								_rougnessMap =nullptr;
    float                               _roughness =1.0f;

    //bump
//	TexPtr								_normalMap   =nullptr;
//	TexPtr								_heightMap   =nullptr;


    //this

    //this
    GLenum                              _fillMode;

protected:
    Material(MaterialType type) noexcept;

public:
    virtual ~Material() noexcept;

    MaterialType getType() const;
    virtual void setUniforms(const ShaderProgram& prg);
    virtual void unbindMaps();
    virtual void bindMaps();
    virtual void setDrawData(Draw& drawData);

    void setRougnessTexture(TexPtr map);
    TexPtr getRougnessTexture() const noexcept;

    void setRoughness(const float roughness) noexcept;
    const float getRoughness() const noexcept;

//    void setNormalTexture(TexPtr map);
//    void setHeightTexture(TexPtr map);
//
//    TexPtr getNormalTexture() const noexcept;
//    TexPtr getHeightTexture() const noexcept;

        
    void setPolygonsFillMode(const GLenum mode) noexcept;
    const GLenum getPolygonsFillMode() const noexcept;
};

class GlassMaterial :
		public Material,
		public SharedCreator<GlassMaterial, Material> {
public:
	GlassMaterial();
	virtual ~GlassMaterial() noexcept override;
	void setUniforms(const ShaderProgram& prg) override;
	void unbindMaps() override;
};

using MaterialPtr = std::shared_ptr < Material >;

#endif // MATERIAL_H
