/*
 * FRAGMENT shader for roug material, optional supported BUMP maping
 */

//#if defined(BUMP) || defined(PHONG)

struct Light {
	vec3 lightDir;
	vec4 lightColor;
};

#ifdef BUMP
	in mat3 vTBNMat;
#endif // BUMP

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;

in vec2 vTexCoords;

uniform Light uLights[NUM_OF_LIGHT];

#ifdef HAS_AMBIENT_MAP 
	uniform sampler2D uTexAmbient;
#endif // HAS_AMBIENT_MAP
#ifdef HAS_DIFFUSE_MAP 
	uniform sampler2D uTexDiffuse;
#endif // HAS_DIFFUSE_MAP
#ifdef HAS_SPECULAR_MAP 
	uniform sampler2D uTexSpecular;
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
uniform vec4 uSpecularColor;

#ifdef BUMP
	uniform float uScale;
#endif // BUMP

#ifdef WRAP
	uniform float uWrap;
	uniform float uScatterWeight;
	uniform vec4  uColor;
#endif // WRAP

out vec4 color;

void main() {
	vec4 ambientColor  = uAmbientColor;
	vec4 diffuseColor  = uDiffuseColor;
	vec4 specularColor = uSpecularColor;
	vec4 fragmentColor = vec4(0.0);

	vec3 normal = vNormal;
	vec3 view   = normalize(vView);

	vec2 texCoord = vTexCoords;

	float rougness = 1.0;

#	ifdef HAS_HEIGHT_MAP
		texCoord = paralax(uTexHeight, view * vTBNMat, texCoord, uScale);
#	endif // HAS_HEIGHT_MAP
#	ifdef HAS_NORMAL_MAP
		normal = (texture(uTexNormal, texCoord).xyz * 2 - 1);
		normal.xy *= uScale;
		normal = vTBNMat * normal;
#	endif // HAS_NORMAL_MAP  
#	ifdef HAS_AMBIENT_MAP 
  		ambientColor *= texture(uTexAmbient, texCoord);
#	endif // HAS_AMBIENT_MAP
#	ifdef HAS_DIFFUSE_MAP 
  		diffuseColor *= texture(uTexDiffuse, texCoord);
#	endif // HAS_DIFFUSE_MAP	
#	ifdef HAS_SPECULAR_MAP 
  		specularColor *= texture(uTexSpecular, texCoord);
#	endif // HAS_SPECULAR_MAP
#	ifdef HAS_ROUGNESS_MAP 
  		rougness *= texture(uTexRougness, texCoord);
#	else
  		rougness *= uRoughness;
#	endif // HAS_ROUGNESS_MAP
  		
  	float wrap = 0.0;
  	float scatterWeight = 0.0;
  	vec4 scatterColor = vec4(0.0, 0.0, 0.0, 0.0);

  	
#	ifdef WRAP
		wrap = uWrap;
		scatterWeight = uScatterWeight;
		scatterColor = uColor;
#	endif // WRAP

  	normal = normalize(normal);

  	for (uint i = 0; i < NUM_OF_LIGHT; ++i) {
  		fragmentColor += calculateLighting(ambientColor, diffuseColor, specularColor, scatterColor,
  			(uLights[i].lightDir), normal, view, rougness, scatterWeight, wrap) * uLights[i].lightColor;
  	}
  
  	color = fragmentColor;
}

//#endif // BUMP || PHONG

