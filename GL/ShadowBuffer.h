/*
 * ShadowBuffer.h
 *
 *  Created on: 21 трав. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef GL_SHADOWBUFFER_H_
#define GL_SHADOWBUFFER_H_

#include "FrameBuffer.h"

class ShadowBuffer final : public FrameBuffer {
public:
	ShadowBuffer(GLenum pol = GL_FRAMEBUFFER);
	~ShadowBuffer() override;
};

#endif /* GL_SHADOWBUFFER_H_ */
