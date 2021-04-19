#ifdef GLOSSY

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
uniform vec4 uAmbientColor;

uniform samplerCube uSkyBox;

uniform uint uLightCount;

uniform float uRoughness;
uniform float uFirstRefractiveIndex;
uniform float uSecondRefractiveIndex;

vec4 SpecColor(vec4 specularColor, vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

void main() {
	vec3 normal = normalize(vNormal);
	vec3 view = normalize(vView);

	float BrusterAngle = sqrt(1 - (
			(uFirstRefractiveIndex * uFirstRefractiveIndex) /
			(uSecondRefractiveIndex * uSecondRefractiveIndex)));
	vec3 I = normalize(vPos - uCameraPos);
	vec3 R = refract(I, normal, 1 / 1.52);
	vec3 R_1 = reflect(I, normal);

	vec4 _color = mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);

	color = _color * uAmbientColor;
}

#endif // GLOSSY