#version 460 core

layout(location = 0) in vec3 aCoord;

out vec3 vTexCoords;

uniform mat4 uSkyBoxMVPMat;

void main() {
	vTexCoords = aCoord;
    gl_Position = uSkyBoxMVPMat * vec4(aCoord * 50, 1.0);
}
