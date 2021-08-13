/*
 * Texture.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#include "Texture.h"
#include "bindguard.h"

#include "../3rdparty/stb_image.h"

//		TEXTURE_BASE		//
Texture::Texture(const GLenum target)
	: GLObject(
		// Creator
		[] () -> ObjectID {
    		GLuint ID;
    		glGenTextures(1, &ID); HANDLE_GL_ERROR();
    		return ID;
		},

		// Deleter
		[] (ObjectID& obj) {
			glDeleteTextures(1, &obj); HANDLE_GL_ERROR();
		}
	)
	, _target(target)
{
	bind();
}

Texture::~Texture() {
}

GLenum Texture::getTarget() {
	return _target;
}

void Texture::bind(TextureUnit unit) {
	bind((int)unit);
}

void Texture::bind(RenderingTarget target) {
	bind((int)target);
}


void Texture::bind() {
	glBindTexture(getTarget(), getID()); HANDLE_GL_ERROR();
}

void Texture::unbind() {
	glBindTexture(getTarget(), 0); HANDLE_GL_ERROR();
}

void Texture::loadImage(const char *name, const GLenum target) {
	int width, height, nrChannels;

	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);

	if(data == NULL) std::cout << "Couldn\'t load image" << std::endl;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);  HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);   HANDLE_GL_ERROR();

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR); HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR); HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);     HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);     HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);     HANDLE_GL_ERROR();

	auto format = GL_RGB;
	if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(target, 0, format, width, height, 0, format,  GL_UNSIGNED_BYTE, data); HANDLE_GL_ERROR();

	stbi_image_free(data);
}

void Texture::setEmpty() {
	bind_guard bd(*this);

	unsigned char data[3] = {
			0, 0, 0
	};

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);  HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); HANDLE_GL_ERROR();
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);   HANDLE_GL_ERROR();

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST); HANDLE_GL_ERROR();

	glTexImage2D(getTarget(), 0, GL_RGB, 2, 2, 0, GL_RGB,  GL_UNSIGNED_BYTE, data); HANDLE_GL_ERROR();
	glGenerateMipmap(getTarget()); HANDLE_GL_ERROR();
}

void Texture::allocate(GLuint width, GLuint height, GLenum format,  GLenum internalFormat, GLenum type) {
	bind_guard bd(*this);

	glTexImage2D(getTarget(), 0, internalFormat, width, height, 0, format,  type, NULL); HANDLE_GL_ERROR();

	glTexParameteri(getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//		TEXTURE_IMPL		//

Texture2D::Texture2D()
	: Texture(GL_TEXTURE_2D)
{ setEmpty(); }

TextureCubeMap::TextureCubeMap()
	: Texture(GL_TEXTURE_CUBE_MAP)
{  }

void Texture2D::loadImage(const char* name) {
//	bind();
	bind_guard bd(*this);
	Texture::loadImage(name, GL_TEXTURE_2D);
	glGenerateMipmap(getTarget()); HANDLE_GL_ERROR();
//	unbind();
}

void TextureCubeMap::loadImage(const char* name, const BoxSide side) {
//	bind();
	bind_guard bd(*this);

	Texture::loadImage(name, (GLuint)side);

	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); HANDLE_GL_ERROR();
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); HANDLE_GL_ERROR();

//	unbind();
}

Texture2D::Texture2D(const char *name)
	: Texture(GL_TEXTURE_2D) {
	setEmpty();
	loadImage(name);
}

void Texture2D::allocate(GLuint width, GLuint height, GLenum format, GLenum internalFormat, GLenum type) {
	if(internalFormat == GL_ZERO) internalFormat = format;
	Texture::allocate(width, height, format, internalFormat, type);
}

void Texture::bind(GLuint index) {
	if (index > 31) {
		ERROR("texture not bind, to many textures");
		return;
	}

	glActiveTexture(GL_TEXTURE0 + index); HANDLE_GL_ERROR();
	bind();
}
