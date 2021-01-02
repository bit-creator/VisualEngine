#include "material.h"

Material::Material() noexcept
    : _ambientColor(1.0, 1.0, 1.0, 1.0)
    , _diffuseColor(1.0, 1.0, 1.0, 1.0)
    , _specularColor(1.0, 1.0, 1.0, 1.0)
    , _roughness(0.0)
	, _fillMode(GL_FILL)
{  }

Material::~Material() noexcept {  }

void Material::setRoughness(const float roughness) noexcept
{ _roughness = roughness; }

const float Material::getRoughness() const noexcept
{ return _roughness; }

void Material::setPolygonsFillMode(const GLenum mode) noexcept
{ _fillMode = mode; }

void Material::setAmbientColor(const Color color) noexcept {
	_ambientColor = color;
}

void Material::setDiffuseColor(const Color color) noexcept {
	_diffuseColor = color;
}

void Material::setSpecularColor(const Color color) noexcept {
	_specularColor = color;
}

const Color& Material::getAmbientColor() const noexcept {
	return _ambientColor;
}

const Color& Material::getDiffuseColor() const noexcept {
	return _diffuseColor;
}

const Color& Material::getSpecularColor() const noexcept {
	return _specularColor;
}

void Material::setAmbientTexture(TexPtr map) {
	_ambientMap = map;
}

void Material::setDiffuseTexture(TexPtr map) {
	_diffuseMap = map;
}

void Material::setSpecularTexture(TexPtr map) {
	_specularMap = map;
}

TexPtr Material::getAmbientTexture() const noexcept {
	return _ambientMap;
}

TexPtr Material::getDiffuseTexture() const noexcept {
	return _diffuseMap;
}

TexPtr Material::getSpecularTexture() const noexcept {
	return _specularMap;
}

const GLenum Material::getPolygonsFillMode() const noexcept
{
	return _fillMode;
}
