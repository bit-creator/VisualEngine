/*
 * Texture.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../3rdparty/stb_image.h"

Texture::Texture(const GLenum target)
	: GLObject(gentex())
	, _target(target)
{
	glBindTexture(getTarget(), getID());
}

Texture::~Texture() {
	glDeleteTextures(1, &getID());
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
}

void Texture::unbind() {
	glBindTexture(getTarget(), 0);
}

void Texture::loadImage(const char *name) {
	int width, height, nrChannels;

	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);

	bind();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	auto format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(getTarget(), 0, format, width, height, 0, format,  GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(getTarget());

	unbind();

	delete [] data;
}

GLuint Texture::gentex() noexcept {
    GLuint ID;
    glGenTextures(1, &ID);
    return ID;
}
