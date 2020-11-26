#version 460 core

layout(location = 0) in vec3 aCoord;
layout(location = 1) in vec3 aNormal;

uniform mat3 uModelMat;
uniform mat3 uNormalMat;
uniform vec3 uPosition;


out vec3 vNormal;

void main()
{
    gl_Position = vec4(uModelMat * aCoord + uPosition, 1);

    vNormal = uNormalMat * aNormal;
}
