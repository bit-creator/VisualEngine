/*
 * BumpMaterial.cpp
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#include "BumpMaterial.h"

BumpMaterial::BumpMaterial()
	: PhongMaterial(MaterialType::MATERIAL_BUMP)
{  }

BumpMaterial::~BumpMaterial() noexcept {
}

void BumpMaterial::setUniforms(const ShaderProgram &prg) {
	PhongMaterial::setUniforms(prg);

	prg.setUniform("uScale", _scale);

	if (_normalMap) prg.setUniform("uTexNormal",  (int)TextureUnit::Normal);
	if (_heightMap) prg.setUniform("uTexHeight",  (int)TextureUnit::Height);
}

void BumpMaterial::unbindMaps() {
	PhongMaterial::unbindMaps();

	if (_normalMap) _normalMap -> unbind();
	if (_heightMap) _heightMap -> unbind();
}

void BumpMaterial::setDrawData(Draw &drawData) {
	PhongMaterial::setDrawData(drawData);

	if (_normalMap) drawData._hasNormalMap = true;
	if (_heightMap) drawData._hasHeightMap = true;
}

void BumpMaterial::bindMaps() {
	PhongMaterial::bindMaps();

	if (_normalMap) _normalMap ->bind((int)TextureUnit::Normal);
	if (_heightMap) _heightMap ->bind((int)TextureUnit::Height);
}


void BumpMaterial::setNormalTexture(TexPtr map) {
	_normalMap = map;
}

void BumpMaterial::setHeightTexture(TexPtr map) {
	_heightMap = map;
}

TexPtr BumpMaterial::getNormalTexture() const noexcept {
	return _normalMap;
}


TexPtr BumpMaterial::getHeightTexture() const noexcept {
	return _heightMap;
}
