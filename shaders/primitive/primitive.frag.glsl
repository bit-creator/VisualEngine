#version 460 core

#define MAX_LIGHT_COUNT 8

in vec3 vNormal;
in vec3 vView;
out vec4 color;

uniform uint uLightCount;
uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;
//uniform vec3 uLightDir;
uniform float uRoughness;

struct Light
{
	vec3 lightDir;
	vec4 lightColor;
};
uniform Light uLights[MAX_LIGHT_COUNT];

vec4 PhongLighting(vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

void main()
{
  vec3 normal = normalize(vNormal);

  vec4 _color;

  for(uint i = 0; i < uLightCount; ++i)
  {
	  _color = PhongLighting(-(uLights[i].lightDir), normal, vView, uRoughness) * uLights[i].lightColor;
  }

  color = _color;
}

vec4 PhongLighting(vec3 lightDir, vec3 normal, vec3 viewDir, float rougness)
{
  vec3 _half = normalize(lightDir + viewDir);

  float diffFactor = dot(normal, lightDir);
  
  float specFactor = pow(max(-dot(_half, normal), 0.0), uRoughness);
  
  if (diffFactor < 0) specFactor = 0; 

  float ambiFactor = 0.1; 

  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  return uAmbientColor * ambiFactor + uDiffuseColor * diffFactor + uSpecularColor * specFactor;
}
