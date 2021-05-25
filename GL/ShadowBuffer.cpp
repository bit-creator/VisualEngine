/*
 * ShadowBuffer.cpp
 *
 *  Created on: 21 ����. 2021 �.
 *      Author: IAbernikhin
 */

#include "ShadowBuffer.h"

ShadowBuffer::ShadowBuffer(GLenum pol)
	: FrameBuffer(pol)
{
	enableDepthBuffer();
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	bind();
}

ShadowBuffer::~ShadowBuffer() {
}
