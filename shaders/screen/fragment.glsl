//#ifdef HAS_SCREEN_TARGET
	TARGET(SCREEN_TARGET_LOCATION) vec4 color;
//#else
//	out vec4 color;
//#endif // SCREEN_TARGET_LOCATION

struct Light {
	vec3 lightDir;
	vec4 lightColor;
};

uniform Light uLights[NUM_OF_LIGHT];

in vec2 vTexCoord;

#ifdef HAS_SKYBOX_MAP
	uniform samplerCube uSkyBox;
#endif // HAS_SKYBOX_MAP

uniform sampler2D uAlbedoMap;
uniform sampler2D uNormalMap;
uniform sampler2D uViewMap;
uniform sampler2D uRoughnessMap;
//uniform sampler2D uPickerMap;

void main() {
    vec4 fragmentColor = vec4(0.0);

    vec3 normal = texture(uNormalMap, vTexCoord).xyz * 2 - 1;
    vec3 view   = texture(uViewMap,   vTexCoord).xyz * 2 - 1;

    vec4 diffuseColor = vec4(texture(uAlbedoMap, vTexCoord).xyz, 1.0);
    float SpecularIntensity = texture(uAlbedoMap, vTexCoord).a;

    float roughness = texture(uRoughnessMap, vTexCoord).r;

  	for (uint i = 0; i < NUM_OF_LIGHT; ++i) {
//  		if (texture(uPickerMap, vTexCoord).r == 0.0) fragmentColor = diffuseColor; else
  		fragmentColor += calculateLighting(vec4(0.1), diffuseColor, SpecularIntensity * vec4(1.0),
  			(uLights[i].lightDir), normal, view, roughness) * uLights[i].lightColor;
  	}

#	ifdef GLOSSY

//  	fragmentColor += uGlossyColor * mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);
#	endif // GLOSSY
//  	fragmentColor.a = 0.0;

	color = fragmentColor;
}
