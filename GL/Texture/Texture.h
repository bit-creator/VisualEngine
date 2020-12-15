/*
 * Texture.h
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE_TEXTURE_H_
#define GL_TEXTURE_TEXTURE_H_

#include <memory>

#include "../globject.hpp"

class Texture : public GLObject {
public:
	Texture(const GLenum target);
	~Texture();
	Texture(const Texture &other) = delete;
	Texture(Texture &&other) = default;
	Texture& operator=(const Texture &other) = delete;
	Texture& operator=(Texture &&other) = default;

	GLenum getTarget();

	void bind(int index);
	void bind();
	void unbind();

	void loadImage(const char* name);

private:
	GLuint gentex() noexcept;

private:
	const GLenum								_target;
};

using TexPtr = std::shared_ptr < Texture >;

#endif /* GL_TEXTURE_TEXTURE_H_ */
