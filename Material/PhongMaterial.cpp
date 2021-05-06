/*
 * PhongMaterial.cpp
 *
 *  Created on: Apr 26, 2021
 *      Author: bit_creator
 */

#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
	: Material(MaterialType::MATERIAL_PHONG)
	, _ambientMap(nullptr)
	, _diffuseMap(nullptr)
	, _specularMap(nullptr)
	, _ambientColor()
	, _diffuseColor()
	, _specularColor()
{  }

PhongMaterial::PhongMaterial(MaterialType type)
	: Material(type)
	,_ambientMap(nullptr)
	, _diffuseMap(nullptr)
	, _specularMap(nullptr)
	, _ambientColor()
	, _diffuseColor()
	, _specularColor()
{  }

PhongMaterial::~PhongMaterial() noexcept {
}

void PhongMaterial::setUniforms(const ShaderProgram &prg) {
	Material::setUniforms(prg);

    prg.setUniform("uAmbientColor", _ambientColor.getColorSource());
    prg.setUniform("uDiffuseColor", _diffuseColor.getColorSource());
    prg.setUniform("uSpecularColor", _specularColor.getColorSource());

    prg.setUniform("uTexAmbient",  (int)TextureUnit::Ambient);
    prg.setUniform("uTexDiffuse",  (int)TextureUnit::Diffuse);
    prg.setUniform("uTexSpecular", (int)TextureUnit::Specular);
}

void PhongMaterial::bindMaps() {
	Material::bindMaps();

    if (_ambientMap)  _ambientMap->bind(TextureUnit::Ambient);
    if (_diffuseMap)  _diffuseMap->bind(TextureUnit::Diffuse);
    if (_specularMap) _specularMap->bind(TextureUnit::Specular);
}

void PhongMaterial::setDrawData(Draw &drawData) {
	Material::setDrawData(drawData);

	if (_ambientMap)  drawData._hasAmbientMap  = true;
	if (_diffuseMap)  drawData._hasDiffuseMap  = true;
	if (_specularMap) drawData._hasSpecularMap = true;
}

void PhongMaterial::unbindMaps() {
	Material::unbindMaps();

    if (_ambientMap)  _ambientMap ->unbind();
    if (_diffuseMap)  _diffuseMap ->unbind();
    if (_specularMap) _specularMap->unbind();
}

void PhongMaterial::setAmbientColor(const Color color) {
	_ambientColor = color;
}

void PhongMaterial::setDiffuseColor(const Color color) {
	_diffuseColor = color;
}

void PhongMaterial::setSpecularColor(const Color color) {
	_specularColor = color;
}

const Color& PhongMaterial::getAmbientColor() const {
	return _ambientColor;
}

const Color& PhongMaterial::getDiffuseColor() const {
	return _diffuseColor;
}

const Color& PhongMaterial::getSpecularColor() const {
	return _specularColor;
}

void PhongMaterial::setAmbientTexture(TexPtr map) {
	_ambientMap = map;
}

void PhongMaterial::setDiffuseTexture(TexPtr map) {
	_diffuseMap = map;
}

void PhongMaterial::setSpecularTexture(TexPtr map) {
	_specularMap = map;
}

TexPtr PhongMaterial::getAmbientTexture() const {
	return _ambientMap;
}

TexPtr PhongMaterial::getDiffuseTexture() const {
	return _diffuseMap;
}

TexPtr PhongMaterial::getSpecularTexture() const {
	return _specularMap;
}

