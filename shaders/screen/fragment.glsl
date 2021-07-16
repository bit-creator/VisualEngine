#ifdef HAS_SCREEN_TARGET
	TARGET(SCREEN_TARGET_LOCATION) vec4 color;
#else
	out vec4 color;
#endif // SCREEN_TARGET_LOCATION

struct DirLight {
	vec3 	 direction;
	vec4 	 color;
};

struct PointLight {
	vec3 	 position;
	vec4 	 color;
};

struct SpotLight {
	float	 angle;
	vec3 	 position;
	vec3 	 direction;
	vec4	 color;
};

uniform DirLight   uDirLights  	[NUM_OF_DIRECTIONAL_LIGHT];
uniform DirLight uPointLights	[NUM_OF_POINT_LIGHT];
uniform DirLight  uSpotLights 	[NUM_OF_SPOT_LIGHT];

in vec2 vTexCoord;

#ifdef HAS_SKYBOX_MAP
	uniform samplerCube uSkyBox;
#endif // HAS_SKYBOX_MAP

uniform sampler2D uAlbedoMap;
uniform sampler2D uNormalMap;
uniform sampler2D uViewMap;
//uniform sampler2D uRoughnessMap;

void main() {
    vec4 fragmentColor = vec4(0.0);
    vec4 normPix = texture(uNormalMap, vTexCoord);
    vec4 viewPix = texture(uViewMap, vTexCoord);
    vec4 albdPix = texture(uAlbedoMap, vTexCoord);

    vec3 normal = normalize(normPix.xyz * 2 - 1);
    float roughness = normPix.a;
//    float roughness = 125;

    vec3 view = normalize(viewPix.xyz * 2 - 1);
    float materialID = viewPix.a;

    vec4 diffuseColor = vec4(albdPix.xyz, 1.0);
    float SpecularIntensity = albdPix.a;

    if(materialID == 0.0) {
    	for (uint i = 0; i < NUM_OF_DIRECTIONAL_LIGHT; ++i) {
    		fragmentColor += calculateDirLighting(0.3 * diffuseColor, diffuseColor, SpecularIntensity * vec4(1.0),
    				(uDirLights[i].direction), normal, view, 1 / roughness) * uDirLights[i].color;
    	}

    	for (uint i = 0; i < NUM_OF_POINT_LIGHT; ++i) {
    		fragmentColor += calculateDirLighting(0.3 * diffuseColor, diffuseColor, SpecularIntensity * vec4(1.0),
    		    	(uPointLights[i].direction), normal, view, 1 / roughness) * uPointLights[i].color;
    	}

    	for (uint i = 0; i < NUM_OF_SPOT_LIGHT; ++i) {
    		fragmentColor += calculateDirLighting(0.3 * diffuseColor, diffuseColor, SpecularIntensity * vec4(1.0),
    		    	(uSpotLights[i].direction), normal, view, 1 / roughness) * uSpotLights[i].color;
    	}
  	}

#	ifdef HAS_SKYBOX_MAP
  	if(materialID == 1.0) {
  		float BrusterAngle = sqrt(1 - (
  					(1.0) /
  					(1.33 * 1.33)));

  			vec3 I = view;
  			vec3 R = refract(I, normal, 1.0 / 1.33);
  			vec3 R_1 = reflect(I, normal);

  		fragmentColor = diffuseColor * mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);
  	}
#	endif // HAS_SKYBOX_MAP

	color = fragmentColor;
//	color = vec4(1.0);
}
