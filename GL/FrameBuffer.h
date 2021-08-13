/*
 * FrameBuffer.h
 *
 *  Created on: 5 ����. 2021 �.
 *      Author: IAbernikhin
 */

#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <map>
#include <vector>

#include <glm/vec2.hpp>

#include "globject.h"
#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer : public GLObject {
private:
	std::map < RenderingTarget, TexPtr >				_colorTextures;
	RenderBuffer										_renderBuffer;

	GLenum												_acsessPolytics	 	=GL_FRAMEBUFFER;

	TexPtr												_depthBuffer	 	=nullptr;
	TexPtr												_stencilBuffer 	 	=nullptr;
	TexPtr												_depthStencilBuffer =nullptr;

	bool												_dirtyHashedData =true;
	mutable bool										_dirtyTargetHash =true;

private: // HASHED_DATA
	mutable GLuint										_targetHash;
	GLuint												_sizeOfAttachment;
	std::vector < GLuint > 								_attachments;

public:
	FrameBuffer(GLenum pol = GL_FRAMEBUFFER);
	virtual ~FrameBuffer();

	void bind();
	void unbind();

	void bindTextures();
	void unbindTextures();

	float getPickerKey(const glm::vec2& mousePosition);

	GLenum getAcsessPolytics() const;
	GLuint getNumberOfTarget() const;
	GLuint TargetHash() const;

	bool readyToWork();

	void enableDepthBuffer();
	void enableStencilBuffer();
	void enableDepthStencilBuffer();
	void useRenderBuffer();

	void attachNewColorTex(RenderingTarget target, GLenum format =GL_RGBA);

private:
	TexPtr createTexture(GLenum format, GLenum internalformat = GL_ZERO, GLenum type = GL_UNSIGNED_BYTE);
	bool   hasTarget(RenderingTarget target) const;
	void   validateHashedData();
};

#endif /* GL_FRAMEBUFFER_H_ */
