#version 460 core

#define MAX_LIGHT_COUNT 8

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;
in vec2 vTexCoords;

out vec4 color;

struct Light
{
	vec3 lightDir;
	vec4 lightColor;
};

uniform Light uLights[MAX_LIGHT_COUNT];

uniform vec3 uCameraPos;

uniform sampler2D uTexAmbient;
uniform sampler2D uTexDiffuse;
uniform sampler2D uTexSpecular;

//uniform samplerCube uSkyBox;

//uniform bool uHasSkyBox;
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

void main() {
  vec3 normal = normalize(vNormal);
  vec3 view = normalize(vView);

  vec4 _color;

  vec4 ambientColor = uAmbientColor;
  vec4 diffuseColor = uDiffuseColor;
  vec4 specularColor = uSpecularColor;

  if (uHasAmbientMap) ambientColor *= texture(uTexAmbient, vTexCoords);
  if (uHasDiffuseMap) diffuseColor *= texture(uTexDiffuse, vTexCoords);
  if (uHasSpecularMap) specularColor *= texture(uTexSpecular, vTexCoords);

  for (uint i = 0; i < 2; ++i)
		  _color += PhongLighting(ambientColor, diffuseColor, specularColor,
			  -(uLights[i].lightDir), normal, vView, uRoughness) * uLights[i].lightColor;

//  float BrusterAngle = sqrt(1 - (1/(1.52 * 1.52)));
//  vec3 I = normalize(vPos - uCameraPos);
//  vec3 R = refract(I, normal, 1 / 1.52);
//  vec3 R_1 = reflect(I, normal);

//  color = mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);
  color = diffuseColor;
}

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness) {
  vec3 _half = normalize(lightDir + viewDir);

  float diffFactor = dot(normal, lightDir);
  
  float specFactor = pow(max(-dot(_half, normal), 0.0), uRoughness);
  
  if (diffFactor < 0) specFactor = 0; 

  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  return ambientColor + diffuseColor * diffFactor + specularColor * specFactor;
}
