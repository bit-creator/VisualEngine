/*
 * Deleters.cpp
 *
 *  Created on: 14 вер. 2021 р.
 *      Author: IAbernikhin
 */

#include "Deleters.h"
#include "../Macro.hpp"
#include <GL/glew.h>

void GL::Deleters::shaderPrg(uint32_t *obj) {
	glDeleteProgram(*obj); HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::renderBuff(uint32_t *obj) {
	glDeleteRenderbuffers(1, (GLuint*)obj);  HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::frameBuff(uint32_t *obj) {
	glDeleteFramebuffers(1, (GLuint*)obj);  HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::buffer(uint32_t *obj) {
	glDeleteBuffers(1, (GLuint*)obj); HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::texture(uint32_t *obj) {
	glDeleteTextures(1, (GLuint*)obj); HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::vertexArray(uint32_t *obj) {
	glDeleteVertexArrays(1, (GLuint*)obj); HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();std::numeric_limits<uint32_t>::max();
}

void GL::Deleters::shader(uint32_t *obj) {
	glDeleteShader(*obj); HANDLE_GL_ERROR();
	*obj = std::numeric_limits<uint32_t>::max();
}
