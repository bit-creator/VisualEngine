#version 460 core

layout(location = 0) in vec3 pos;

uniform mat3 mat;
uniform vec3 offset;

void main()
{
    gl_Position = vec4(mat * pos + offset, 1);
}
