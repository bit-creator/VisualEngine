#include "material.h"

Material::Material() noexcept
    : _ambientColor(1.0, 1.0, 1.0, 1.0)
    , _diffuseColor(1.0, 1.0, 1.0, 1.0)
    , _specularColor(1.0, 1.0, 1.0, 1.0)
    , _roughness(0.0)
{  }

Material::~Material() noexcept {  }

void Material::setColor(ColorType type, const glm::vec4& color) noexcept
{
    if(type == ColorType::Ambient) _ambientColor = color;
    if(type == ColorType::Diffuse) _diffuseColor = color;
    if(type == ColorType::Specular) _specularColor = color;
}

void Material::setColor(ColorType type, const float& r, const float& g, 
            const float& b, const float& a) noexcept
{
    if(type == ColorType::Ambient) _ambientColor = glm::vec4(r, g, b, a);
    if(type == ColorType::Diffuse) _diffuseColor = glm::vec4(r, g, b, a);
    if(type == ColorType::Specular) _specularColor = glm::vec4(r, g, b, a);
}

const glm::vec4& Material::getColor(ColorType type) const noexcept
{
    if(type == ColorType::Ambient) return _ambientColor;
    if(type == ColorType::Diffuse) return _diffuseColor;
    if(type == ColorType::Specular) return _specularColor;
}

void Material::setRoughness(const float& roughness) noexcept
{ _roughness = roughness; }

const float& Material::getRoughness() const noexcept
{ return _roughness; }








