#version 460 core

#define MAX_LIGHT_COUNT 8

in vec3 vNormal;
in vec3 vView;
in vec3 vPos;
in vec2 vTexCoords;
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

uniform uint uLightCount;
uniform float uRoughness;


vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness);

vec2 paralax(vec3 viewVec, vec2 tex);

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

void main() {
  vec3 normal = normalize(vNormal);
  vec3 view = normalize(vView);

  vec4 _color;

  vec4 ambientColor = uAmbientColor;
  vec4 diffuseColor = uDiffuseColor;
  vec4 specularColor = uSpecularColor;
  vec3 norm = vNormal;
  float depth;
  mat3 TBNMat = cotangent_frame(vNormal, vPos, vTexCoords);
  vec2 texCoord = vTexCoords;

  if (uHasHeightMap) texCoord = paralax(view * TBNMat, vTexCoords);

  if (uHasNormalMap) norm = TBNMat * (texture(uTexNormal, texCoord).xyz * 2 - 1);

  norm = normalize(norm);

  if (uHasAmbientMap) ambientColor *= texture(uTexAmbient, texCoord);
  if (uHasDiffuseMap) diffuseColor *= texture(uTexDiffuse, texCoord);
  if (uHasSpecularMap) specularColor *= texture(uTexSpecular, texCoord);

  for (uint i = 0; i < 2; ++i)
		  _color += PhongLighting(ambientColor, diffuseColor, specularColor,
			  normalize(uLights[i].lightDir), norm, view, uRoughness) * uLights[i].lightColor;

//  float BrusterAngle = sqrt(1 - (1/(1.52 * 1.52)));
//  vec3 I = normalize(vPos - uCameraPos);
//  vec3 R = refract(I, normal, 1 / 1.52);
//  vec3 R_1 = reflect(I, normal);

//  color = mix(texture(uSkyBox, R), texture(uSkyBox, R_1), dot(normal, I) > BrusterAngle ? 1 : 0);
  color = vec4(1.0);
//  color = vec4(vec3(dot(norm, -(uLights[0].lightDir))), 1.0);
//  	 color.xyz = vNormal;


  vec3 _half = -normalize(uLights[0].lightDir + view);
  float spec = pow(max(dot(_half, normal), 0.0), uRoughness);

//  color.xyz = vec3(-dot(view, -(uLights[0].lightDir)) * 0.5);
//  color.xyz = vec3(spec);
  color = _color;
}

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float rougness) {
  vec3 _half = -normalize(lightDir + viewDir);

  float diffFactor = dot(normal, -lightDir);
  
  float specFactor = pow(max(dot(_half, normal), 0.0), uRoughness);
  
  if (diffFactor < 0) specFactor = 0;

  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  return ambientColor + diffuseColor * diffFactor + specularColor * specFactor * 0;
}

vec2 paralax(vec3 viewVec, vec2 tex){
	float height_scale = 0.2;
	float height = texture(uTexHeight, tex).x * height_scale;
//
//	vec2 offset = height * viewVec.xy / viewVec.z;

    const float numLayers = 50;
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewVec.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;

	vec2  currentTexCoords     = tex;
	float currentDepthMapValue = texture(uTexHeight, currentTexCoords).r;

	while(currentLayerDepth < currentDepthMapValue)
	{
	    currentTexCoords -= deltaTexCoords;
	    currentDepthMapValue = 1 - texture(uTexHeight, currentTexCoords).r;
	    currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(uTexHeight, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}
