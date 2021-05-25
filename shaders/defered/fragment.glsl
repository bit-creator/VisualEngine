//#ifdef DEFERED

TARGET(ALBEDO_TARGET_LOCATION)	  vec4  tAlbedo;
TARGET(NORMAL_TARGET_LOCATION)	  vec4  tNormal;
TARGET(VIEW_TARGET_LOCATION)	  vec4  tView;

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
	vec4 result_albedo = vec4(0.0);
	vec4 result_normal = vec4(0.0);
	vec4 result_view   = vec4(0.0);

	vec3 normal = g_in.gNormal;
	vec3 view   = normalize(g_in.gView);

	float roughness = 1.0;
	float materialID = 0.0;

	vec4 ambientColor = uAmbientColor;
	vec4 albedoColor = vec4(0.0);

#	ifdef GLOSSY
	albedoColor = uGlossyColor;
	materialID = 1.0;
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
  		roughness *= texture(uTexRougness, texCoord).r;
#	else
  		roughness *= uRoughness;
#	endif // HAS_ROUGNESS_MAP

  	normal = normalize(normal);
  	normal = (normal + 1) / 2;

  	view   = normalize(view);
  	view   = (view + 1) / 2;

//  	float zNear = 0.1;
//  	float zFar  = 100;

//  	float z = gl_FragCoord.z * 2.0 - 1.0;
//  	z = (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
//  	z /= zFar;
//  	z -= texture(uLocalThikness, gl_FragCoord.xy).r;

  	result_albedo.xyz = albedoColor.xyz;
//  	result_albedo.xyz = vec3(z);
  	result_albedo.a   = specularColor;

  	result_normal.xyz = normal;
  	result_normal.a   = roughness;

  	result_view.xyz   = view;
  	result_view.a   = materialID;

  	tNormal = result_normal;
  	tView   = result_view;
  	tAlbedo = result_albedo;

#	ifdef HAS_PICKER_TARGET
  		objectColorKey = uObjectColorKey PICKER_SWIZZLE;
#	endif // HAS_PICKER_TARGET
}



//#endif // DEFERED
