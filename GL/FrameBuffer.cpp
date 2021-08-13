/*
 * FrameBuffer.cpp
 *
 *  Created on: 5 ����. 2021 �.
 *      Author: IAbernikhin
 */

#include "FrameBuffer.h"
#include "../engine.h"
#include "bindguard.h"

FrameBuffer::FrameBuffer(GLenum pol)
	: GLObject(
		// Creator
		[] () -> ObjectID {
			GLuint fbo;
			glGenFramebuffers(1, &fbo);  HANDLE_GL_ERROR();
			return fbo;
		},

		// Deleter
		[] (ObjectID& obj) {
			glDeleteFramebuffers(1, &obj); HANDLE_GL_ERROR();
		}
	)
	, _acsessPolytics(pol)
	, _depthBuffer(nullptr)
	, _stencilBuffer(nullptr)
	, _depthStencilBuffer(nullptr)
{
	bind();

	HANDLE_GL_ERROR();
}

FrameBuffer::~FrameBuffer() {
	unbind();
}

void FrameBuffer::bind() {
	glBindFramebuffer(_acsessPolytics, getID());  HANDLE_GL_ERROR();

	if(_dirtyHashedData) {
		_attachments.clear();
		for(auto& [target, tex] : _colorTextures) {
			_attachments.push_back(GL_COLOR_ATTACHMENT0 + (int)target);
		}
		_sizeOfAttachment = _attachments.size();

		_dirtyHashedData = false;
	}

	glDrawBuffers(_sizeOfAttachment, _attachments.data());
}

bool FrameBuffer::readyToWork() {
	bind_guard bd(*this);
	bool ready = glCheckFramebufferStatus(_acsessPolytics) == GL_FRAMEBUFFER_COMPLETE; HANDLE_GL_ERROR();
	return ready;
}

void FrameBuffer::unbind() {
		glBindFramebuffer(_acsessPolytics, 0);  HANDLE_GL_ERROR();
}

GLenum FrameBuffer::getAcsessPolytics() const {
	return _acsessPolytics;
}

GLuint FrameBuffer::getNumberOfTarget() const {
	return _colorTextures.size();
}

void FrameBuffer::attachNewColorTex(RenderingTarget target, GLenum format) {
	GLuint attachment = GL_COLOR_ATTACHMENT0 + (int)target;

	if(attachment > GL_COLOR_ATTACHMENT15) {
		ERROR("to more Texture attached to framebuffer");
		return;
	}

	bind_guard bd(*this);

	TexPtr colorTex = createTexture(format); HANDLE_GL_ERROR();

	bind_guard tex(*colorTex);

	glFramebufferTexture2D (
			_acsessPolytics,
			attachment,
			colorTex->getTarget(),
			colorTex->getID(), 0
	); HANDLE_GL_ERROR();

	_colorTextures[target] = colorTex;

	_dirtyHashedData = true;
	_dirtyTargetHash = true;


	return;
}

void FrameBuffer::enableDepthBuffer() {
	bind();

	_depthBuffer = createTexture(GL_DEPTH_COMPONENT); HANDLE_GL_ERROR();

	bind_guard guard(*_depthBuffer);

	glFramebufferTexture2D (
			_acsessPolytics,
			GL_DEPTH_ATTACHMENT,
			_depthBuffer->getTarget(),
			_depthBuffer->getID(), 0
	); HANDLE_GL_ERROR();
}

void FrameBuffer::enableStencilBuffer() {
	bind();

	_stencilBuffer = createTexture(GL_STENCIL_INDEX, GL_STENCIL_INDEX8); HANDLE_GL_ERROR();

	bind_guard guard(*_stencilBuffer);

	glFramebufferTexture2D (
			_acsessPolytics,
			GL_STENCIL_ATTACHMENT,
			_stencilBuffer->getTarget(),
			_stencilBuffer->getID(), 0
	); HANDLE_GL_ERROR();
}

void FrameBuffer::enableDepthStencilBuffer() {
	bind();

	_depthStencilBuffer = createTexture(GL_DEPTH_STENCIL, GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8); HANDLE_GL_ERROR();

	bind_guard guard(*_depthStencilBuffer);

	glFramebufferTexture2D (
			_acsessPolytics,
			GL_DEPTH_STENCIL_ATTACHMENT,
			_depthStencilBuffer->getTarget(),
			_depthStencilBuffer->getID(), 0
	); HANDLE_GL_ERROR();
}

void FrameBuffer::useRenderBuffer() {
	bind();

	_renderBuffer.allocate(); HANDLE_GL_ERROR();

	bind_guard guard(_renderBuffer);

	glFramebufferRenderbuffer(
			_acsessPolytics,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			_renderBuffer.getID()
	); HANDLE_GL_ERROR();

}

void FrameBuffer::bindTextures() {
	for (auto [target, texture] : _colorTextures)
		texture->bind(target);
}

void FrameBuffer::unbindTextures() {
	for (auto [target, texture] : _colorTextures)
		texture->unbind();
}

GLuint FrameBuffer::TargetHash() const {
	if (!_dirtyTargetHash) return _targetHash;

	std::bitset<NUM_RENDERING_TARGET> hash;
	auto setTarget = [&hash, this] (RenderingTarget target) mutable -> void {
		hash.set((int)target, hasTarget(target));
	};

	setTarget(RenderingTarget::SCREEN);
	setTarget(RenderingTarget::ALBEDO);
	setTarget(RenderingTarget::NORMAL);
	setTarget(RenderingTarget::VIEW);
//	setTarget(RenderingTarget::ROUGHNESS);
	setTarget(RenderingTarget::PICKER);

	_targetHash = hash.to_ullong();
	_dirtyTargetHash = false;

	return _targetHash;
}

TexPtr FrameBuffer::createTexture(GLenum format, GLenum internalformat, GLenum type) {
	auto [width, height] = Engine::window.getWindowSize();

	auto tex = Texture2D::create(); HANDLE_GL_ERROR();

	bind_guard guard(*tex);

	tex->allocate(width, height, format, internalformat, type); HANDLE_GL_ERROR();

	return tex;
}

bool FrameBuffer::hasTarget(RenderingTarget target) const {
	return _colorTextures.contains(target);
}

float FrameBuffer::getPickerKey(const glm::vec2& mousePosition) {
	if(!hasTarget(RenderingTarget::PICKER)) {
		ERROR("Picker image not attached");
		return 0.0;
	}

	auto [width, height] = Engine::window.getWindowSize();
	GLubyte data[sizeof(Object3D::ID_t)];

	bind_guard bd(*this);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + (int)RenderingTarget::PICKER); HANDLE_GL_ERROR();

	_colorTextures[RenderingTarget::PICKER]->bind();

	glReadPixels(width / 2, height / 2, 1, 1, Object3D::getColorKeyFormat(), GL_UNSIGNED_BYTE, &data);  HANDLE_GL_ERROR();  // NEED FIX

	Object3D::ID_t id;
	memcpy(&id, data, sizeof(Object3D::ID_t));

	return id;
}

void FrameBuffer::validateHashedData() {
	_attachments.clear();
	for(auto& [target, tex] : _colorTextures) {
		_attachments.push_back(GL_COLOR_ATTACHMENT0 + (int)target);
	}
	_sizeOfAttachment = _attachments.size();

	_dirtyHashedData = false;
}
