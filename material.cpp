#include "material.h"

Material::Material(MaterialType type) noexcept
    : _ambientColor(1.0, 1.0, 1.0, 1.0)
    , _diffuseColor(1.0, 1.0, 1.0, 1.0)
    , _specularColor(1.0, 1.0, 1.0, 1.0)
	, _ambientMap(nullptr)
	, _diffuseMap(nullptr)
	, _specularMap(nullptr)
    , _roughness(0.0)
	, _fillMode(GL_FILL)
{ _type = type; }

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

void Material::setRougnessTexture(TexPtr map) {
	_rougnessMap = map;
}

void Material::setNormalTexture(TexPtr map) {
	_normalMap = map;
}

void Material::setHeightTexture(TexPtr map) {
	_heightMap = map;
}

TexPtr Material::getAmbientTexture() const noexcept {
	return _ambientMap;
}

TexPtr Material::getNormalTexture() const noexcept {
	return _normalMap;
}

TexPtr Material::getDiffuseTexture() const noexcept {
	return _diffuseMap;
}

TexPtr Material::getSpecularTexture() const noexcept {
	return _specularMap;
}

TexPtr Material::getRougnessTexture() const noexcept {
	return _rougnessMap;
}

TexPtr Material::getHeightTexture() const noexcept {
	return _heightMap;
}

MaterialType Material::getType() const {
	return _type;
}

const GLenum Material::getPolygonsFillMode() const noexcept {
	return _fillMode;
}

BumpMaterial::BumpMaterial()
	: Material(MaterialType::MATERIAL_BUMP)
{  }

PhongMaterial::PhongMaterial()
	: Material(MaterialType::MATERIAL_PHONG)
{  }

GlassMaterial::GlassMaterial()
	: Material(MaterialType::MATERIAL_GLASS)
{  }

GlossyMaterial::GlossyMaterial()
	: Material(MaterialType::MATERIAL_GLOSSY)
{
}

