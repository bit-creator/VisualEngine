#version 460 core

out vec4 color;

in vec3 vTexCoords;
uniform samplerCube uSkyBox;

void main() {
	color = texture(uSkyBox, vTexCoords);
}
