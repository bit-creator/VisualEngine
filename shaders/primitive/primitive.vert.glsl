#version 460 core

layout(location = 0)

uniform mat3 scale;
uniform mat3 rotate;

in vec3 pos;

void main()
{
    gl_Position = vec4(rotate * pos, 1);
}
