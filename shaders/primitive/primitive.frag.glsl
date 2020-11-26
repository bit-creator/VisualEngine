#version 460 core

in vec3 normal;
out vec4 color;

uniform vec4 uColor;
uniform vec3 uLightDir;

void main()
{
  float factor = dot(normalize(normal), uLightDir);
  color = vec4(normal, 1.0);
}
