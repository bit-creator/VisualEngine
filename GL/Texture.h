/*
 * Texture.h
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE_TEXTURE_H_
#define GL_TEXTURE_TEXTURE_H_

#include <memory>

#include "globject.hpp"

enum class SkyBox
{
	right = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	left = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	sky = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	ground = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	near = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	far = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

class Texture : public GLObject {
protected:
	Texture(const GLenum target);

//	Texture(const Texture &other) = delete;
//	Texture& operator=(const Texture &other) = delete;

public:
	~Texture();

	Texture(Texture &&other) = default;
	Texture& operator=(Texture &&other) = default;

	GLenum getTarget();

	void bind(int index);
	void bind();
	void unbind();

protected:
	void loadImage(const char* name, const GLenum target);
	void discard();

private:
	GLuint gentex() noexcept;

private:
	const GLenum								_target;
};	// CLASS_TEXTURE

class Texture2D final : public Texture {
public:
	Texture2D();
	~Texture2D() =default;

	Texture2D(const Texture2D &other) =delete;
	Texture2D(Texture2D &&other) =default;

	Texture2D& operator=(const Texture2D &other) =delete;
	Texture2D& operator=(Texture2D &&other) =default;

	void loadImage(const char* name, const GLenum target = GL_TEXTURE_2D);
};	// CLASS_TEXTURE2D

class TextureCubeMap final : public Texture {
public:
	TextureCubeMap();
	~TextureCubeMap() =default;

	TextureCubeMap(const TextureCubeMap &other) =delete;
	TextureCubeMap(TextureCubeMap &&other) =default;

	TextureCubeMap& operator=(const TextureCubeMap &other) =delete;
	TextureCubeMap& operator=(TextureCubeMap &&other) =default;

	void loadImage(const char* name, const GLenum target);
}; 	// CLASS_TEXTURECUBEMAP

using TexPtr = std::shared_ptr < Texture >;
using Tex2DPtr = std::shared_ptr < Texture2D >;
using CubeMapPtr = std::shared_ptr < TextureCubeMap >;


#endif /* GL_TEXTURE_TEXTURE_H_ */
