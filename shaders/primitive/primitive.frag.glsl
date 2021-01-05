#version 460 core

#define MAX_LIGHT_COUNT 8

in vec3 vNormal;
in vec3 vView;
in vec2 vTexCoord;

out vec4 color;

struct Light
{
	vec3 lightDir;
	vec4 lightColor;
};

uniform Light uLights[MAX_LIGHT_COUNT];

uniform sampler2D uTexAmbient;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSpecular;

uniform bool uHasAmbientMap;
uniform bool uHasDiffuseMap;
uniform bool uHasSpecularMap;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;

uniform uint uLightCount;
uniform float uRoughness;


vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

void main()
{
  vec3 normal = normalize(vNormal);

  vec4 _color;

  vec4 ambientColor = uAmbientColor;
  vec4 diffuseColor = uDiffuseColor;
  vec4 specularColor = uSpecularColor;

  if (uHasAmbientMap) ambientColor *= texture(uTexAmbient, vTexCoord);
  if (uHasDiffuseMap) diffuseColor *= texture(uTexDiffuse, vTexCoord);
  if (uHasSpecularMap) specularColor *= texture(uTexSpecular, vTexCoord);

  for (uint i = 0; i < 2; ++i)
		  _color += PhongLighting(ambientColor, diffuseColor, specularColor,
			  -(uLights[i].lightDir), normal, vView, uRoughness) * uLights[i].lightColor;

  color = _color;
}

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness)
{
  vec3 _half = normalize(lightDir + viewDir);

  float diffFactor = dot(normal, lightDir);
  
  float specFactor = pow(max(-dot(_half, normal), 0.0), uRoughness);
  
  if (diffFactor < 0) specFactor = 0; 

  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  return ambientColor + diffuseColor * diffFactor + specularColor * specFactor;
}
