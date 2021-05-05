/*
 * FrameBuffer.cpp
 *
 *  Created on: 5 трав. 2021 р.
 *      Author: IAbernikhin
 */

#include "FrameBuffer.h"
#include "../engine.h"

FrameBuffer::FrameBuffer(FBAcsessPolytics pol)
	: GLObject(genFB())
	, _polytics(pol)
	, _colorAttachment(GL_COLOR_ATTACHMENT0)
	, _depthBuffer(nullptr)
	, _stencilBuffer(nullptr)
	, _depthStencilBuffer(nullptr)
{
	_colorTextures.reserve(15);
	bind();
	attachNewColorTex();

	HANDLE_GL_ERROR();
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &getID()); HANDLE_GL_ERROR();
}

void FrameBuffer::bind() {
	glBindFramebuffer((GLuint)_polytics, getID());  HANDLE_GL_ERROR();
}

bool FrameBuffer::readyToWork() {
	bool ready = glCheckFramebufferStatus((GLuint)_polytics) == GL_FRAMEBUFFER_COMPLETE; HANDLE_GL_ERROR();
	return ready;
}

void FrameBuffer::unbind() {
	if (readyToWork()) {
		glBindFramebuffer((GLuint)_polytics, 0);  HANDLE_GL_ERROR();
	} else {
		ERROR("FRAMEBUFFER NOT READY")
	}
}

FBAcsessPolytics FrameBuffer::getAcsessPolytics() {
	return _polytics;
}

GLuint FrameBuffer::getNumberOfColorTex() {
	return _colorAttachment - GL_COLOR_ATTACHMENT0;
}

void FrameBuffer::attachNewColorTex() {
	if(_colorAttachment > GL_COLOR_ATTACHMENT15) {
		ERROR("to more Texture attached to framebuffer");
		return;
	}

	TexPtr colorTex = createTexture(GL_RGBA); HANDLE_GL_ERROR();

	colorTex->bind(); HANDLE_GL_ERROR();

	glFramebufferTexture2D (
			(GLuint)_polytics,
			_colorAttachment,
			colorTex->getTarget(),
			colorTex->getID(), 0
	); HANDLE_GL_ERROR();

//	colorTex->unbind(); HANDLE_GL_ERROR();

	++_colorAttachment;

	_colorTextures.push_back(colorTex);

	return;
}

void FrameBuffer::enableDepthBuffer() {
	_depthBuffer = createTexture(GL_DEPTH_COMPONENT); HANDLE_GL_ERROR();

	_depthBuffer->bind(); HANDLE_GL_ERROR();

	glFramebufferTexture2D (
			(GLuint)_polytics,
			GL_DEPTH_ATTACHMENT,
			_depthBuffer->getTarget(),
			_depthBuffer->getID(), 0
	); HANDLE_GL_ERROR();

	_depthBuffer->unbind(); HANDLE_GL_ERROR();
}

void FrameBuffer::enableStencilBuffer() {
	_stencilBuffer = createTexture(GL_STENCIL_INDEX); HANDLE_GL_ERROR();

	_stencilBuffer->bind(); HANDLE_GL_ERROR();

	glFramebufferTexture2D (
			(GLuint)_polytics,
			GL_STENCIL_ATTACHMENT,
			_stencilBuffer->getTarget(),
			_stencilBuffer->getID(), 0
	); HANDLE_GL_ERROR();

	_stencilBuffer->unbind(); HANDLE_GL_ERROR();
}

void FrameBuffer::enableDepthStencilBuffer() {
	_depthStencilBuffer = createTexture(GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8); HANDLE_GL_ERROR();

	_depthStencilBuffer->bind(); HANDLE_GL_ERROR();

	glFramebufferTexture2D (
			(GLuint)_polytics,
			GL_DEPTH_STENCIL_ATTACHMENT,
			_depthStencilBuffer->getTarget(),
			_depthStencilBuffer->getID(), 0
	); HANDLE_GL_ERROR();

	_depthStencilBuffer->unbind(); HANDLE_GL_ERROR();

}

TexPtr FrameBuffer::createTexture(GLenum format, GLenum type) {
	auto [width, height] = Engine::window.getWindowSize();

	auto tex = Texture2D::create(); HANDLE_GL_ERROR();

	tex->bind();
	tex->allocate(width, height, format, type); HANDLE_GL_ERROR();
	tex->unbind();


	return tex;
}

GLuint FrameBuffer::genFB() {
	GLuint fbo;
	glGenFramebuffers(1, &fbo);  HANDLE_GL_ERROR();
	return fbo;
}

std::vector<TexPtr> FrameBuffer::getColorTextures() {
	return _colorTextures;
}
