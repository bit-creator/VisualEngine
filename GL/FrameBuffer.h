/*
 * FrameBuffer.h
 *
 *  Created on: 5 трав. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <vector>

#include "globject.h"
#include "Texture.h"

enum class FBAcsessPolytics {
	READ = GL_READ_FRAMEBUFFER,
	WRITE = GL_DRAW_FRAMEBUFFER,
	READ_WRITE = GL_FRAMEBUFFER
};

class FrameBuffer final : public GLObject {
private:
	FBAcsessPolytics					_polytics;
	GLuint								_colorAttachment;
	TexPtr								_depthBuffer;
	TexPtr								_stencilBuffer;
	TexPtr								_depthStencilBuffer;
	std::vector < TexPtr >				_colorTextures;

public:
	FrameBuffer(FBAcsessPolytics pol = FBAcsessPolytics::READ_WRITE);
	~FrameBuffer();

	void bind();
	void unbind();

	FBAcsessPolytics getAcsessPolytics();
	GLuint getNumberOfColorTex();
	std::vector < TexPtr > getColorTextures();

	bool readyToWork();

	void enableDepthBuffer();
	void enableStencilBuffer();
	void enableDepthStencilBuffer();
	void attachNewColorTex();

private:
	GLuint genFB();
	TexPtr createTexture(GLenum format, GLenum type = GL_UNSIGNED_BYTE);

};

#endif /* GL_FRAMEBUFFER_H_ */
