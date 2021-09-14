/*
 * Creators.cpp
 *
 *  Created on: 14 вер. 2021 р.
 *      Author: IAbernikhin
 */

#include "Creators.h"
#include <GL/glew.h>
#include "../Macro.hpp"

void GL::Creators::shaderPrg(uint32_t *obj) {
	*obj = glCreateProgram(); HANDLE_GL_ERROR();
}

void GL::Creators::renderBuff(uint32_t *obj) {
	glGenRenderbuffers(1, obj);  HANDLE_GL_ERROR();
}

void GL::Creators::frameBuff(uint32_t *obj) {
	glGenFramebuffers(1, obj);  HANDLE_GL_ERROR();
}

void GL::Creators::buffer(uint32_t *obj) {
	glGenBuffers(1, obj); HANDLE_GL_ERROR();
}

void GL::Creators::texture(uint32_t *obj) {
	glGenTextures(1, obj); HANDLE_GL_ERROR();
}

void GL::Creators::vertexArray(uint32_t *obj) {
	glGenVertexArrays(1, obj); HANDLE_GL_ERROR();
}

void GL::Creators::shader(uint32_t *obj, uint32_t type) {
	*obj = glCreateShader(type); HANDLE_GL_ERROR();
}

