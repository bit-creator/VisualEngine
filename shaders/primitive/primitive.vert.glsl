#version 460 core

#define ATTRIB_COORD_LOC 0
#define ATTRIB_NORMAL_LOC 1
#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in

ATTRIBUTE(ATTRIB_COORD_LOC) vec3 aCoord;
ATTRIBUTE(ATTRIB_NORMAL_LOC) vec3 aNormal;

uniform mat4 uModelMat;
uniform mat4 uProjMat;
uniform mat3 uNormalMat;

out vec3 vNormal;

void main()
{
    vec4 position = uModelMat * vec4(aCoord, 1.0);

    float n = 0.01;
    float f = 10;

    mat4 matProj = mat4(
        1., 0., 0., 0.,
        0., 1., 0., 0.,
        0., 0., (f + n) / (f - n), ( - 2 * f * n) / (f - n),
        0., 0., 1., 0.
    );

    gl_Position = uProjMat * position;
    // gl_Position = position;

    vNormal = uNormalMat * aNormal;
}
