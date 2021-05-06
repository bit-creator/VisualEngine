/*
 * RenderBuffer.cpp
 *
 *  Created on: May 6, 2021
 *      Author: bit_creator
 */

#include "RenderBuffer.h"
#include "../engine.h"

RenderBuffer::RenderBuffer()
	: GLObject(genRB())
{ HANDLE_GL_ERROR(); }

RenderBuffer::~RenderBuffer() {
	glDeleteRenderbuffers(1, &getID()); HANDLE_GL_ERROR();
}

void RenderBuffer::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, getID());
}

void RenderBuffer::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::allocate() {
	auto [width, height] = Engine::window.getWindowSize();

	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); HANDLE_GL_ERROR();
	unbind();
}

int RenderBuffer::genRB() {
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);  HANDLE_GL_ERROR();
	return rbo;
}

