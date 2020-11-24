#version 460 core

layout(location = 0) in vec3 aCoord;

uniform mat3 uModelMat;
uniform vec3 uPosition;

void main()
{
    gl_Position = vec4(uModelMat * aCoord + uPosition, 1);
}
