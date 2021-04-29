/*
 * GlossyMaterialt.cpp
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#include "GlossyMaterial.h"

GlossyMaterial::GlossyMaterial()
	: Material(MaterialType::MATERIAL_GLOSSY)
	, _color(glm::vec4(1.0))
	, _1RefInd(1.0f)
	, _2RefInd(1.52f)
{
}

GlossyMaterial::~GlossyMaterial() noexcept {
}

void GlossyMaterial::setUniforms(const ShaderProgram &prg) {
	prg.setUniform("uGlossyColor", _color);
    prg.setUniform("uFirstRefractiveIndex", _1RefInd);
    prg.setUniform("uSecondRefractiveIndex", _2RefInd);
}


void GlossyMaterial::unbindMaps() {
	Material::unbindMaps();
}

void GlossyMaterial::setDrawData(Draw &drawData) {
	Material::setDrawData(drawData);
}

void GlossyMaterial::bindMaps() {
	Material::bindMaps();
}

float GlossyMaterial::get1RefInd() const {
	return _1RefInd;
}

void GlossyMaterial::set1RefInd(float firstRefInd) {
	_1RefInd = firstRefInd;
}

float GlossyMaterial::get2RefInd() const {
	return _2RefInd;
}

void GlossyMaterial::set2RefInd(float secondRefInd) {
	_2RefInd = secondRefInd;
}

const glm::vec4& GlossyMaterial::getColor() const {
	return _color;
}

void GlossyMaterial::setColor(const glm::vec4 &color) {
	_color = color;
}
