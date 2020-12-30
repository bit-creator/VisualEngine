/*
 * Texture.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"

//		TEXTURE_BASE		//

Texture::Texture(const GLenum target)
	: GLObject(gentex())
	, _target(target)
{
	bind();
}

Texture::~Texture() {
	glDeleteTextures(1, &getID());
	CHECK_ERROR();
}

GLenum Texture::getTarget() {
	return _target;
}

void Texture::bind(int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	bind();
}

void Texture::bind() {
	glBindTexture(getTarget(), getID());
	CHECK_ERROR();
}

void Texture::unbind() {
	glBindTexture(getTarget(), 0);
	CHECK_ERROR();
}

void Texture::loadImage(const char *name, const GLenum target) {
	int width, height, nrChannels;

	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);

	glBindTexture(target, getID());

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_REPEAT);

	auto format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(target, 0, format, width, height, 0, format,  GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);

	CHECK_ERROR();

	unbind();

	stbi_image_free(data);
}

void Texture::discard() {
	glBindTexture(getTarget(), getID());

	unsigned char data[3] = {
			0, 0, 0
	};

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(getTarget(), 0, GL_RGB, 2, 2, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(getTarget());

	unbind();
}

GLuint Texture::gentex() noexcept {
    GLuint ID;
    glGenTextures(1, &ID);
    CHECK_ERROR();
    return ID;
}

//		TEXTURE_IMPL		//

Texture2D::Texture2D()
	: Texture(GL_TEXTURE_2D)
{ discard(); }

TextureCubeMap::TextureCubeMap()
	: Texture(GL_TEXTURE_CUBE_MAP)
{
	discard();
}

void Texture2D::loadImage(const char* name, const GLenum target) {
	int width, height, nrChannels;

	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);

	glBindTexture(target, getID());

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	auto format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(target, 0, format, width, height, 0, format,  GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);

	unbind();

	delete [] data;
}

void TextureCubeMap::loadImage(const char* name, const GLenum target) {
	int width, height, nrChannels;

	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);

	bind();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	auto format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(target, 0, format, width, height, 0, format,  GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);

	unbind();

	delete [] data;
}
