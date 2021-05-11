/**
 * FRAGMENT shader for glossy materaial
 */

//#ifdef GLOSSY

TARGET(SCREEN_TARGET_LOCATION) vec4 color;
TARGET(PICKER_TARGET_LOCATION) PICKER_INTERNAL_TYPE objectColor;

struct Light {
	vec3 lightDir;
	vec4 lightColor;
};

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;

in vec2 vTexCoords;

uniform Light uLights[NUM_OF_LIGHT];

uniform vec4 uSpecularColor;
uniform vec4 uGlossyColor;

uniform vec3 uCameraPos;

uniform float uFirstRefractiveIndex;
uniform float uSecondRefractiveIndex;

#ifdef HAS_SKYBOX_MAP
	uniform samplerCube uSkyBox;
#endif // HAS_SKYBOX_MAP

#ifdef HAS_SPECULAR_MAP 
	uniform sampler2D uTexSpecular;
#endif // HAS_SPECULAR_MAP
#ifdef HAS_ROUGNESS_MAP 
	uniform sampler2D uTexRougness;
#else
	uniform float uRoughness;
#endif // HAS_ROUGNESS_MAP
	
#ifdef HAS_PICKER_TARGET
	uniform vec4 uObjectColor;
#endif // HAS_PICKER_TARGET

void main() {
	vec4 specularColor = uSpecularColor;
	vec4 fragmentColor = vec4(0.0);
	
	float rougness = 1.0;
	
#	ifdef HAS_SPECULAR_MAP 
  		specularColor *= texture(uTexSpecular, texCoord);
#	endif // HAS_SPECULAR_MAP
#	ifdef HAS_ROUGNESS_MAP 
  		rougness *= texture(uTexRougness, texCoord);
#	else
  		rougness *= uRoughness;
#	endif // HAS_ROUGNESS_MAP
	
	vec3 normal = normalize(vNormal);
	vec3 view = normalize(vView);

	float BrusterAngle = sqrt(1 - (
			(uFirstRefractiveIndex * uFirstRefractiveIndex) /
			(uSecondRefractiveIndex * uSecondRefractiveIndex)));
	
	vec3 I = normalize(vPos - uCameraPos);
	vec3 R = refract(I, normal, uFirstRefractiveIndex / uSecondRefractiveIndex);
	vec3 R_1 = reflect(I, normal);
	
	for (uint i = 0; i < NUM_OF_LIGHT; ++i)
		fragmentColor += calculateLighting(vec4(0.0), vec4(0.0), specularColor,
				-(uLights[i].lightDir), normal, view, rougness) * uLights[i].lightColor;
	
	fragmentColor = uGlossyColor * mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);

#	ifdef HAS_SCREEN_TARGET
  		color = fragmentColor;
#	endif // HAS_SCREEN_TARGET
#	ifdef HAS_PICKER_TARGET
  		objectColor = uObjectColor PICKER_SWIZZLE;
#	endif // HAS_PICKER_TARGET
}

//#endif // GLOSSY
