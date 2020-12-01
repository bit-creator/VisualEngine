#version 460 core

in vec3 vNormal;
out vec4 color;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;
uniform vec3 uLightDir;
uniform float uRoughness;

void main()
{
  float diffFactor = -dot(normalize(vNormal), uLightDir);

  vec3 r = normalize(reflect(-uLightDir, normalize(vNormal)));
  
  float specFactor = pow(max(dot(r, vec3(0.0, 0.0, 1.0)), 0.0), uRoughness);

  float ambiFactor = 0.1; 
  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  color = uAmbientColor * ambiFactor + uDiffuseColor * diffFactor;
}
