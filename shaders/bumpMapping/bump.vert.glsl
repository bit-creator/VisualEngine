#version 460 core

#define ATTRIB_COORD_LOC 0
#define ATTRIB_NORMAL_LOC 1
#define ATTRIB_TANGENT_LOC 2
#define ATTRIB_BITANGENT_LOC 3
#define ATTRIB_COLOR_LOC 4
#define ATTRIB_TEXCOORD_LOC 5

#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in

ATTRIBUTE(ATTRIB_COORD_LOC) 	vec3 aCoord;
ATTRIBUTE(ATTRIB_NORMAL_LOC) 	vec3 aNormal;
ATTRIBUTE(ATTRIB_TANGENT_LOC) 	vec3 aTangent;
ATTRIBUTE(ATTRIB_BITANGENT_LOC) vec3 aBiTangent;
ATTRIBUTE(ATTRIB_TEXCOORD_LOC) 	vec2 aTexCoord;

uniform mat4 uModelMat;
uniform mat4 uMVPMat;

uniform mat3 uNormalMat;

uniform vec3 uCamPos;

uniform bool uPerspectiveCamera;

out mat3 vTBNMat;
out vec3 vNormal;
out vec3 vView;
out vec2 vTexCoords;

out vec3 vPos;

/**
 *  v * n = 0
 *
 *  v' * n' = 0
 *
 *  v' = mm * v;
 *
 *  n' = mn * n;
 *
 *  mm * tr(mn) * v * n = 0;
 *
 *  mm * tr(mn) = I;
 *
 *  mm = inv(tr(mn));
 */


void main() {
    gl_Position = uMVPMat * vec4(aCoord, 1.0);
   
    vNormal = normalize(uNormalMat * aNormal);
    vec3 tangent = normalize((uModelMat * vec4(aTangent, 0.0)).xyz);
    vec3 biTangent = normalize((uModelMat * vec4(aBiTangent, 0.0)).xyz);

    vTexCoords = aTexCoord;
    vPos = (uModelMat * vec4(aCoord, 1.0)).xyz;

    vTBNMat = mat3(-tangent, -biTangent, vNormal);

    if(uPerspectiveCamera) vView = (uModelMat * vec4(aCoord, 1.0)).xyz - uCamPos;
    else                   vView = vec3(0.0, 0.0, 1.0);
}
