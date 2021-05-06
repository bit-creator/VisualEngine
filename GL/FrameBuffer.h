/*
 * FrameBuffer.h
 *
 *  Created on: 5 ����. 2021 �.
 *      Author: IAbernikhin
 */

#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <vector>

#include "globject.h"
#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer final : public GLObject {
private:
	RenderBuffer						_renderBuffer;
	GLenum								_polytics;
	GLuint								_colorAttachment;
	TexPtr								_depthBuffer;
	TexPtr								_stencilBuffer;
	TexPtr								_depthStencilBuffer;
	std::vector < TexPtr >				_colorTextures;

public:
	FrameBuffer(GLenum pol = GL_FRAMEBUFFER);
	~FrameBuffer();

	void bind();
	void unbind();

	GLenum getAcsessPolytics() const;
	GLuint getNumberOfColorTex() const;

	const std::vector < TexPtr >&
	getColorTextures() const;

	bool readyToWork();

	void enableDepthBuffer();
	void enableStencilBuffer();
	void enableDepthStencilBuffer();
	void useRenderBuffer();

	void attachNewColorTex();

private:
	GLuint genFB();
	TexPtr createTexture(GLenum format, GLenum type = GL_UNSIGNED_BYTE);

};

#endif /* GL_FRAMEBUFFER_H_ */
