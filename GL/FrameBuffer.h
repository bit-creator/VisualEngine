/*
 * FrameBuffer.h
 *
 *  Created on: 5 ����. 2021 �.
 *      Author: IAbernikhin
 */

#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <map>

#include "globject.h"
#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer final : public GLObject {
private:
	RenderBuffer										_renderBuffer;
	GLenum												_polytics;
	TexPtr												_depthBuffer;
	TexPtr												_stencilBuffer;
	TexPtr												_depthStencilBuffer;
	std::map < RenderingTarget, TexPtr >				_colorTextures;

public:
	FrameBuffer(GLenum pol = GL_FRAMEBUFFER);
	~FrameBuffer();

	void bind();
	void unbind();

	void bindTextures();
	void unbindTextures();

	GLenum getAcsessPolytics() const;
	GLuint getNumberOfTarget() const;

	bool readyToWork();

	void enableDepthBuffer();
	void enableStencilBuffer();
	void enableDepthStencilBuffer();
	void useRenderBuffer();

	void attachNewColorTex(RenderingTarget target);

private:
	GLuint genFB();
	TexPtr createTexture(GLenum format, GLenum type = GL_UNSIGNED_BYTE);

};

#endif /* GL_FRAMEBUFFER_H_ */
