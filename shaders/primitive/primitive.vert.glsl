#version 460 core

#define ATTRIB_COORD_LOC 0
#define ATTRIB_NORMAL_LOC 1
#define ATTRIB_COLOR_LOC 2
#define ATTRIB_TEXCOORD_LOC 3

#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in

ATTRIBUTE(ATTRIB_COORD_LOC) vec3 aCoord;
ATTRIBUTE(ATTRIB_NORMAL_LOC) vec3 aNormal;
ATTRIBUTE(ATTRIB_TEXCOORD_LOC) vec2 aTexCoord;

uniform mat4 uModelViewMat;
uniform mat4 uMVPMat;
uniform mat3 uNormalMat;
uniform bool uPerspectiveCamera;

out vec3 vNormal;
out vec3 vView;
out vec2 vTexCoord;

void main()
{
    gl_Position = uMVPMat * vec4(aCoord, 1.0);
   
    vNormal = uNormalMat * aNormal;
    vTexCoord = aTexCoord;
    
    if(uPerspectiveCamera) vView = (uModelViewMat * vec4(aCoord, 1.0)).xyz;
    else                   vView = vec3(0.0, 0.0, 1.0);
}
