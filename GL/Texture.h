/*
 * Texture.h
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE_TEXTURE_H_
#define GL_TEXTURE_TEXTURE_H_

#include <memory>

#include "../CreateAsPointer.hpp"

#include "RowGraphicObject.h"

constexpr static int NUM_TEXTURE_UNIT = 7;
constexpr static int NUM_RENDERING_TARGET = 5;

enum class TextureUnit {
	Ambient  =0,
	Diffuse  =1,
	Specular =2,
	Rougness =3,
	SkyBox   =4,
	Normal   =5,
	Height   =6
};

enum class RenderingTarget {
	SCREEN = 0,
	ALBEDO,
	NORMAL,
	VIEW,
	PICKER,
};

enum class BoxSide {
	SIDE_RIGHT  = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	SIDE_LEFT   = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	SIDE_TOP    = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	SIDE_BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	SIDE_FRONT  = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	SIDE_BACK   = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

class Texture: public RowGraphicObject <
	Creators::texture,
	Deleters::texture
> {
protected:
	Texture(const uint32_t target);

public:
	~Texture();

	Texture(Texture &&other) = default;
	Texture& operator=(Texture &&other) = default;

	GLenum getTarget();

	void bind(RenderingTarget target);
	void bind(TextureUnit unit);
	void bind();
	void unbind();

protected:
	void loadImage(const char* name, const uint32_t target);
	void setEmpty();
	void allocate(uint32_t width, uint32_t height, uint32_t format, uint32_t internalFormat, uint32_t type);

private:
	void bind(uint32_t index);

private:
	const uint32_t								_target;
};	// CLASS_TEXTURE

class Texture2D final : public Texture,
	public SharedCreator< Texture2D > {
public:
	Texture2D();
	Texture2D(const char* name);
	~Texture2D() =default;

	Texture2D(Texture2D &&other) =default;
	Texture2D& operator=(Texture2D &&other) =default;

	void loadImage(const char* name);
	void allocate(uint32_t width, uint32_t height, uint32_t format, uint32_t internalFormat, uint32_t type);
};	// CLASS_TEXTURE2D

class TextureCubeMap final : public Texture,
	public SharedCreator < TextureCubeMap > {
public:
	TextureCubeMap();
	~TextureCubeMap() =default;

	TextureCubeMap(TextureCubeMap &&other) =default;
	TextureCubeMap& operator=(TextureCubeMap &&other) =default;

	void loadImage(const char* name, const BoxSide side);
}; 	// CLASS_TEXTURECUBEMAP

using TexPtr = std::shared_ptr < Texture >;
using Tex2DPtr = std::shared_ptr < Texture2D >;
using CubeMapPtr = std::shared_ptr < TextureCubeMap >;


#endif /* GL_TEXTURE_TEXTURE_H_ */
