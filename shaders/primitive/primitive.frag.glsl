#version 460 core

in vec3 vNormal;
in vec3 vView;
out vec4 color;

uniform vec4 uAmbientColor;
uniform vec4 uDiffuseColor;
uniform vec4 uSpecularColor;
uniform vec3 uLightDir;
uniform float uRoughness;

void main()
{
  vec3 normal = normalize(vNormal);
  vec3 lightDir = -uLightDir;
  
  vec3 _half = normalize(lightDir + vView); 

  float diffFactor = dot(normal, lightDir);
  
  float specFactor = pow(max(-dot(_half, normal), 0.0), uRoughness);

  float ambiFactor = 0.1; 
  diffFactor = clamp(diffFactor, 0.0, 1.0);
  specFactor = clamp(specFactor, 0.0, 1.0);

  color = uAmbientColor * ambiFactor + uDiffuseColor * diffFactor + uSpecularColor * specFactor;
}
