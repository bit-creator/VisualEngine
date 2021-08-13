/*
 * RenderBuffer.cpp
 *
 *  Created on: May 6, 2021
 *      Author: bit_creator
 */

#include "RenderBuffer.h"
#include "../engine.h"
#include "bindguard.h"

RenderBuffer::RenderBuffer()
	: GLObject(
		// Creator
		[] () -> ObjectID {
			GLuint rbo;
			glGenRenderbuffers(1, &rbo);  HANDLE_GL_ERROR();
			return rbo;
		},

		// Deleter
		[] (ObjectID& obj) {
			glDeleteRenderbuffers(1, &obj); HANDLE_GL_ERROR();
		}
	)
{ HANDLE_GL_ERROR(); }

RenderBuffer::~RenderBuffer() {
}

void RenderBuffer::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, getID());
}

void RenderBuffer::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::allocate() {
	auto [width, height] = Engine::window.getWindowSize();

	bind_guard bd(*this);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); HANDLE_GL_ERROR();
}

