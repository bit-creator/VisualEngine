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

void Material::setColor(ColorTarget type, const float& r, const float& g, 
            const float& b, const float& a) noexcept
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
}

void Material::setRoughness(const float& roughness) noexcept
{ _roughness = roughness; }

const float& Material::getRoughness() const noexcept
{ return _roughness; }

void Material::setFill(const GLenum mode) noexcept
{ _fillMode = mode; }

const GLenum Material::getFill() const noexcept
{ return _fillMode; }









