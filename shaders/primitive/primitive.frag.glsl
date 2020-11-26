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
  float factor = -dot(normalize(vNormal), uLightDir);
  vec3 r = normalize(reflect(-uLightDir, normalize(vNormal)));;
  float factorWhite = pow(max(dot(r, vec3(0.0, 0.0, 1.0)), 0.0), 1 / uRoughness);
  color = 0.8 * factorWhite * vec4(1.0, 1.0, 1.0, 1.0) + factor * uAmbientColor;
}
