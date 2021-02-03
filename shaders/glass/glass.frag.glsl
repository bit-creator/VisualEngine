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

uniform bool uHasSkyBox;

uniform vec3 uCameraPos;

uniform vec4 uSpecularColor;

uniform samplerCube uSkyBox;

uniform uint uLightCount;

uniform float uRoughness;

vec4 SpecColor(vec4 specularColor, vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

void main() {
	vec3 normal = normalize(vNormal);
	vec3 view = normalize(vView);

	vec3 I = normalize(vPos - uCameraPos);
	vec3 R = -reflect(I, normal);

	vec4 _color = texture(uSkyBox, R);

	for (uint i = 0; i < 2; ++i)
		_color += SpecColor(uSpecularColor,
				-(uLights[i].lightDir), normal, vView, uRoughness) * uLights[i].lightColor;

	color = _color;
}

vec4 SpecColor(vec4 specularColor, vec3 lightDir, vec3 normal, vec3 viewDir, float rougness) {
	  vec3 _half = normalize(lightDir + viewDir);

	  float specFactor = pow(max(-dot(_half, normal), 0.0), uRoughness);
	  specFactor = clamp(specFactor, 0.0, 1.0);

	  return specularColor * specFactor;
}
