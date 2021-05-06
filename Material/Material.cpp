#include "Material.h"

Material::Material(MaterialType type) noexcept
	: _type(type)
	, _rougnessMap(nullptr)
//	, _normalMap  (nullptr)
//	, _heightMap  (nullptr)
    , _roughness(1.0)
	, _fillMode(GL_FILL)
{  }

Material::~Material() noexcept {  }

void Material::setUniforms(const ShaderProgram &prg) {
	if(_rougnessMap) prg.setUniform("uTexRougness",(int)TextureUnit::Rougness);
	else 			 prg.setUniform("uRoughness", _roughness);
}

void Material::unbindMaps() {
	if(_rougnessMap) _rougnessMap->unbind();
}

void Material::setDrawData(Draw &drawData) {
	drawData._type = (int)_type;
	if(_rougnessMap) drawData._hasRougnessMap = true;
}

void Material::bindMaps() {
	if(_rougnessMap) _rougnessMap->bind(TextureUnit::Rougness);
}

void Material::setRoughness(const float roughness) noexcept
{ _roughness = roughness; }

const float Material::getRoughness() const noexcept
{ return _roughness; }

void Material::setPolygonsFillMode(const GLenum mode) noexcept
{ _fillMode = mode; }

void Material::setRougnessTexture(TexPtr map) {
	_rougnessMap = map;
}
//
//void Material::setNormalTexture(TexPtr map) {
//	_normalMap = map;
//}
//
//void Material::setHeightTexture(TexPtr map) {
//	_heightMap = map;
//}
//
//TexPtr Material::getNormalTexture() const noexcept {
//	return _normalMap;
//}
//
//
//TexPtr Material::getHeightTexture() const noexcept {
//	return _heightMap;
//}

TexPtr Material::getRougnessTexture() const noexcept {
	return _rougnessMap;
}
MaterialType Material::getType() const {
	return _type;
}


const GLenum Material::getPolygonsFillMode() const noexcept {
	return _fillMode;
}









GlassMaterial::GlassMaterial()
	: Material(MaterialType::MATERIAL_GLASS)
{  }

GlassMaterial::~GlassMaterial() noexcept {
}

void GlassMaterial::setUniforms(const ShaderProgram &prg) {
}

void GlassMaterial::unbindMaps() {
}

