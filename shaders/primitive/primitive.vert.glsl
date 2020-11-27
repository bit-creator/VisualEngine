#version 460 core

#define ATTRIB_COORD_LOC 0
#define ATTRIB_NORMAL_LOC 1
#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in

ATTRIBUTE(ATTRIB_COORD_LOC) vec3 aCoord;
ATTRIBUTE(ATTRIB_NORMAL_LOC) vec3 aNormal;

uniform mat3 uModelMat;
uniform mat3 uNormalMat;
uniform vec3 uPosition;

out vec3 vNormal;

void main()
{
    gl_Position = vec4(uModelMat * aCoord + uPosition, 1);

    vNormal = uNormalMat * aNormal;
}
