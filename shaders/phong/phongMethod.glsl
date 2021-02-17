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

uniform bool uHasAmbientMap;
uniform bool uHasDiffuseMap;
uniform bool uHasSpecularMap;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;

uniform uint uLightCount;
uniform float uRoughness;

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness) {
	float diffFactor = dot(normal, -lightDir);

	vec3 _half = -normalize(lightDir + viewDir);
	float specFactor = pow(max(dot(_half, normal), 0.0), uRoughness);

	if (diffFactor < 0) specFactor = 0;

	diffFactor = clamp(diffFactor, 0.0, 1.0);
	specFactor = clamp(specFactor, 0.0, 1.0);

	return ambientColor + diffuseColor * diffFactor + specularColor * specFactor;
}
