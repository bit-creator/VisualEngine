#version 460 core

in vec3 vNormal;
out vec4 color;

uniform vec4 uColor;
uniform vec3 uLightDir;

void main()
{
  float factor = -dot(normalize(vNormal), uLightDir);
  float koef = 1.;
  vec3 view = -normalize(vec3(0.0, 0.0, 1.0) - vNormal);
  vec3 reflectDir = reflect(-uLightDir, normalize(vNormal));
  float factorWhite = pow(-dot(view, reflectDir), 25);
  color = koef * factorWhite * vec4(1.0, 1.0, 1.0, 1.0) + factor * uColor;
}
