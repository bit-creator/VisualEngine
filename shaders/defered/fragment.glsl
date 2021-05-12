//#ifdef DEFERED

TARGET(ALBEDO_TARGET_LOCATION)	  vec4  tAlbedo;
TARGET(NORMAL_TARGET_LOCATION)	  vec3  tNormal;
TARGET(VIEW_TARGET_LOCATION)	  vec3  tView;

TARGET(ROUGHNESS_TARGET_LOCATION) float tRoughness;

#ifdef HAS_PICKER_TARGET
	TARGET(PICKER_TARGET_LOCATION) PICKER_INTERNAL_TYPE objectColorKey;
#endif // HAS_PICKER_TARGET

#ifdef HAS_AMBIENT_MAP
	uniform sampler2D uTexAmbient;
#endif // HAS_AMBIENT_MAP
#ifdef HAS_DIFFUSE_MAP
	uniform sampler2D uTexDiffuse;
#endif // HAS_DIFFUSE_MAP
#ifdef HAS_SPECULAR_MAP
	uniform sampler2D uTexSpecular;
#else
	uniform float uSpecularIntensivity;
#endif // HAS_SPECULAR_MAP
#ifdef HAS_NORMAL_MAP
	uniform sampler2D uTexNormal;
#endif // HAS_NORMAL_MAP
#ifdef HAS_HEIGHT_MAP
	uniform sampler2D uTexHeight;
#endif // HAS_HEIGHT_MAP
#ifdef HAS_ROUGNESS_MAP
	uniform sampler2D uTexRougness;
#else
	uniform float uRoughness;
#endif // HAS_ROUGNESS_MAP

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
//uniform vec4 uSpecularColor;

#ifdef BUMP
	uniform float uScale;
#endif // BUMP

#ifdef GLOSSY
	uniform vec4 uGlossyColor;
#endif // GLOSSY

#ifdef HAS_PICKER_TARGET
	uniform vec4 uObjectColorKey;
#endif // HAS_PICKER_TARGET

in GEOMETRY_PASS {
	#ifdef BUMP
		mat3 gTBNMat;
	#endif // BUMP

	vec3 gNormal;
	vec3 gView;

	vec2 gTexCoords;
} g_in;

void main() {
	vec4 albedo = vec4(0.0);
	vec3 normal = g_in.gNormal;
	vec3 view   = normalize(g_in.gView);

	float rougness = 1.0;

	vec4 ambientColor = uAmbientColor;
	vec4 albedoColor = vec4(0.0);

#	ifdef GLOSSY
	albedoColor = uGlossyColor;
#	else
	albedoColor = uDiffuseColor;
#endif // GLOSSY

	float specularColor = 1.0;

	vec2 texCoord = g_in.gTexCoords;


#	ifdef HAS_HEIGHT_MAP
		texCoord = paralax(uTexHeight, view * g_in.gTBNMat, texCoord, uScale);
#	endif // HAS_HEIGHT_MAP
#	ifdef HAS_NORMAL_MAP
		normal = (texture(uTexNormal, texCoord).xyz * 2 - 1);
		normal.xy *= uScale;
		normal = g_in.gTBNMat * normal;
#	endif // HAS_NORMAL_MAP
#	ifdef HAS_AMBIENT_MAP
  		ambientColor *= texture(uTexAmbient, texCoord);
#	endif // HAS_AMBIENT_MAP
#	ifdef HAS_DIFFUSE_MAP
  		albedoColor *= texture(uTexDiffuse, texCoord);
#	endif // HAS_DIFFUSE_MAP
#	ifdef HAS_SPECULAR_MAP
  		specularColor = texture(uTexSpecular, texCoord).r;
#	else
  		specularColor = uSpecularIntensivity;
#	endif // HAS_SPECULAR_MAP
#	ifdef HAS_ROUGNESS_MAP
  		rougness *= texture(uTexRougness, texCoord);
#	else
  		rougness *= uRoughness;
#	endif // HAS_ROUGNESS_MAP

  	albedo.xyz = albedoColor.xyz;
  	albedo.a   = specularColor;
  	normal = normalize(normal);

  	tNormal = (normal + 1) / 2;
  	tView   = (view + 1) / 2;
  	tAlbedo = albedo;
  	tRoughness = rougness;

#	ifdef HAS_PICKER_TARGET
  		objectColorKey = uObjectColorKey PICKER_SWIZZLE;
#	endif // HAS_PICKER_TARGET
}



//#endif // DEFERED
