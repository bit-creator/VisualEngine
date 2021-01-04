#version 460 core

layout(location = 0) in vec3 aCoord;

uniform mat4 uSkyBoxMVPMat;

void main() {
    gl_Position = uSkyBoxMVPMat * vec4(aCoord, 1.0);
};
