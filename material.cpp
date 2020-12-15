#include "material.h"

Material::Material() noexcept
    : _ambientColor(1.0, 1.0, 1.0, 1.0)
    , _diffuseColor(1.0, 1.0, 1.0, 1.0)
    , _specularColor(1.0, 1.0, 1.0, 1.0)
    , _roughness(0.0)
{  }

Material::~Material() noexcept {  }

void Material::setColor(ColorTarget type, const glm::vec4& color) noexcept
{
    if(type == ColorTarget::Ambient) _ambientColor = color;
    if(type == ColorTarget::Diffuse) _diffuseColor = color;
    if(type == ColorTarget::Specular) _specularColor = color;
}

void Material::setColor(ColorTarget type, const float r, const float g, 
            const float b, const float a) noexcept
{
    if(type == ColorTarget::Ambient) _ambientColor = glm::vec4(r, g, b, a);
    if(type == ColorTarget::Diffuse) _diffuseColor = glm::vec4(r, g, b, a);
    if(type == ColorTarget::Specular) _specularColor = glm::vec4(r, g, b, a);
}

const glm::vec4& Material::getColor(ColorTarget type) const noexcept
{
    if(type == ColorTarget::Ambient) return _ambientColor;
    if(type == ColorTarget::Diffuse) return _diffuseColor;
    if(type == ColorTarget::Specular) return _specularColor;
    return glm::vec4(1.0);
}

void Material::setRoughness(const float roughness) noexcept
{ _roughness = roughness; }

const float Material::getRoughness() const noexcept
{ return _roughness; }

void Material::setPolygonsFillMode(const GLenum mode) noexcept
{ _fillMode = mode; }

bool Material::hasMap(MapTarget type) const noexcept {
    if(type == MapTarget::Ambient) return _ambientMap != nullptr;
    if(type == MapTarget::Diffuse) return _diffuseMap != nullptr;
    if(type == MapTarget::Specular) return _specularMap != nullptr;
    return false;
}

void Material::bindMaps() noexcept {
	if (hasMap(MapTarget::Ambient)) _ambientMap->bind(0);
	if (hasMap(MapTarget::Diffuse)) _diffuseMap->bind(1);
	if (hasMap(MapTarget::Specular)) _specularMap->bind(2);
}

void Material::unbindMaps() noexcept {
	if (hasMap(MapTarget::Ambient)) _ambientMap->unbind();
	if (hasMap(MapTarget::Diffuse)) _diffuseMap->unbind();
	if (hasMap(MapTarget::Specular)) _specularMap->unbind();
}

const int mapUnit(MapTarget type) noexcept {
	return static_cast<GLuint>(type);
}

const GLenum Material::getPolygonsFillMode() const noexcept
{
	return _fillMode;
}

void Material::setMap(MapTarget type, TexPtr map) {
    if(type == MapTarget::Ambient) _ambientMap = map;
    if(type == MapTarget::Diffuse) _diffuseMap = map;
    if(type == MapTarget::Specular) _specularMap = map;
}

TexPtr Material::getMap(MapTarget type) const noexcept {
    if(type == MapTarget::Ambient) return _ambientMap;
    if(type == MapTarget::Diffuse) return _diffuseMap;
    if(type == MapTarget::Specular) return _specularMap;
    return nullptr;
}
