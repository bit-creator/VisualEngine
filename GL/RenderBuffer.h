/*
 * RenderBuffer.h
 *
 *  Created on: May 6, 2021
 *      Author: bit_creator
 */

#ifndef GL_RENDERBUFFER_H_
#define GL_RENDERBUFFER_H_

#include "globject.h"

class RenderBuffer final : public GLObject {
public:
	RenderBuffer();
	~RenderBuffer();

	void bind();
	void unbind();

	void allocate();
};

#endif /* GL_RENDERBUFFER_H_ */
