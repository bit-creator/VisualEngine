#ifdef PHONG

struct Light
{
	vec3 lightDir;
	vec4 lightColor;
};

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;

in vec2 vTexCoords;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;

#ifdef HAS_AMBIENT_MAP 
	uniform sampler2D uTexAmbient;
#endif // HAS_AMBIENT_MAP
#ifdef HAS_DIFFUSE_MAP 
	uniform sampler2D uTexDiffuse;
#endif // HAS_DIFFUSE_MAP
#ifdef HAS_SPECULAR_MAP 
	uniform sampler2D uTexSpecular;
#endif // HAS_SPECULAR_MAP
#ifdef HAS_ROUGNESS_MAP 
	uniform sampler2D uTexRougness;
#else
	uniform float uRoughness;
#endif // HAS_ROUGNESS_MAP	

uniform Light uLights[NUM_OF_LIGHT];

out vec4 color;

void main() {
	vec3 normal = normalize(vNormal);
	vec3 view = normalize(vView);

	vec4 _color;

	vec4 ambientColor = uAmbientColor;
	vec4 diffuseColor = uDiffuseColor;
	vec4 specularColor = uSpecularColor;
	
	float rougness = 0.05;

#	ifdef HAS_AMBIENT_MAP 
  		ambientColor *= texture(uTexAmbient, vTexCoords);
#	endif // HAS_AMBIENT_MAP
#	ifdef HAS_DIFFUSE_MAP 
  		diffuseColor *= texture(uTexDiffuse, vTexCoords);
#	endif // HAS_DIFFUSE_MAP	
#	ifdef HAS_SPECULAR_MAP 
  		specularColor *= texture(uTexSpecular, vTexCoords);
#	endif // HAS_SPECULAR_MAP
#	ifdef HAS_ROUGNESS_MAP 
  		rougness = texture(uTexRougness, vTexCoords);
#	else
  		rougness = uRoughness;
#	endif // HAS_SPECULAR_MAP

  	for (uint i = 0; i < NUM_OF_LIGHT; ++i) {
  		_color += PhongLighting(ambientColor, diffuseColor, specularColor,
  			(uLights[i].lightDir), normal, view, rougness) * uLights[i].lightColor;
  	}
  	
  	color = _color;
}

#endif // PHONG