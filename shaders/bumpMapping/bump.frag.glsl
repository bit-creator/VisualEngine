#version 460 core

#define MAX_LIGHT_COUNT 8

in vec2 vTexCoords;

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;

in mat3 vTBNMat;

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
uniform sampler2D uTexNormal;
uniform sampler2D uTexHeight;

//uniform samplerCube uSkyBox;

//uniform bool uHasSkyBox;
uniform bool uHasAmbientMap;
uniform bool uHasDiffuseMap;
uniform bool uHasSpecularMap;
uniform bool uHasNormalMap;
uniform bool uHasHeightMap;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;

uniform float uScale;

uniform uint uLightCount;

uniform float uRoughness;

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

vec2 paralax(vec3 viewVec);

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv );

void main() {
  vec4 ambientColor  = uAmbientColor;
  vec4 diffuseColor  = uDiffuseColor;
  vec4 specularColor = uSpecularColor;
  vec4 fragmentColor = vec4(0.0);

  vec3 normal = vNormal;
  vec3 view   = normalize(vView);

  vec2 texCoord = vTexCoords;

  if (uHasHeightMap) 	texCoord = paralax(view * vTBNMat);
  if (uHasNormalMap){
	  normal = (texture(uTexNormal, texCoord).xyz * 2 - 1);
	  normal.xy *= uScale;
	  normal = vTBNMat * normal;
  }
  if (uHasAmbientMap) 	ambientColor *= texture(uTexAmbient, texCoord);
  if (uHasDiffuseMap) 	diffuseColor *= texture(uTexDiffuse, texCoord);
  if (uHasSpecularMap) 	specularColor *= texture(uTexSpecular, texCoord);

  normal = normalize(normal);

  for (uint i = 0; i < 2; ++i)
	  fragmentColor += PhongLighting(ambientColor, diffuseColor, specularColor,
			  (uLights[i].lightDir), normal, view, uRoughness) * uLights[i].lightColor;

  color = fragmentColor;
}

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

vec2 paralax(vec3 viewVec) {
	const float height_scale = uScale;
    const float numLayers = 20;

    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;

	vec2 currentTexCoords = vTexCoords;
    vec2 P = viewVec.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;

	float currentDepthMapValue = 1 - texture(uTexHeight, currentTexCoords).r;

	while(currentLayerDepth < currentDepthMapValue) {
	    currentTexCoords -= deltaTexCoords;
	    currentDepthMapValue = 1 - texture(uTexHeight, currentTexCoords).r;
	    currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = 1 - texture(uTexHeight, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

