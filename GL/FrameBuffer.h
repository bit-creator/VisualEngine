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

#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer: public RowGraphicObject <
	Creators::frameBuff,
	Deleters::frameBuff
> {
private:
	std::map < RenderingTarget, TexPtr >				_colorTextures;
	RenderBuffer										_renderBuffer;

	uint32_t											_acsessPolytics;

	TexPtr												_depthBuffer	 	=nullptr;
	TexPtr												_stencilBuffer 	 	=nullptr;
	TexPtr												_depthStencilBuffer =nullptr;

	bool												_dirtyHashedData =true;
	mutable bool										_dirtyTargetHash =true;

private: // HASHED_DATA
	mutable uint32_t										_targetHash;
	uint32_t												_sizeOfAttachment;
	std::vector < uint32_t > 								_attachments;

public:
	FrameBuffer(uint32_t pol);
	virtual ~FrameBuffer();

	void bind();
	void unbind();

	void bindTextures();
	void unbindTextures();

	float getPickerKey(const glm::vec2& mousePosition);

	uint32_t getAcsessPolytics() const;
	uint32_t getNumberOfTarget() const;
	uint32_t TargetHash() const;

	bool readyToWork();

	void enableDepthBuffer();
	void enableStencilBuffer();
	void enableDepthStencilBuffer();
	void useRenderBuffer();

	void attachNewColorTex(RenderingTarget target, uint32_t format);

private:
	TexPtr createTexture(uint32_t format, uint32_t internalformat, uint32_t type);
	bool   hasTarget(RenderingTarget target) const;
	void   validateHashedData();
};

#endif /* GL_FRAMEBUFFER_H_ */
