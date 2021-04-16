#ifdef PHONG
ATTRIBUTE(ATTRIB_COORD_LOC) vec3 aCoord;
ATTRIBUTE(ATTRIB_NORMAL_LOC) vec3 aNormal;
ATTRIBUTE(ATTRIB_TEXCOORD_LOC) vec2 aTexCoord;

uniform mat4 uModelViewMat;
uniform mat4 uModelMat;
uniform mat4 uMVPMat;

uniform mat3 uNormalMat;

uniform bool uPerspectiveCamera;

//uniform sampler2D uDisplacementMap;
//uniform bool uHasDisplacementMap;

out vec3 vNormal;
out vec3 vView;
out vec2 vTexCoords;

out vec3 vPos;

void main() {
    gl_Position = uMVPMat * vec4(aCoord, 1.0);
   
    vNormal = uNormalMat * aNormal;
    vTexCoords = aTexCoord;
    vPos = (uModelMat * vec4(aCoord, 1.0)).xyz;
    
    if(uPerspectiveCamera) vView = (uModelViewMat * vec4(aCoord, 1.0)).xyz;
    else                   vView = vec3(0.0, 0.0, 1.0);
}

#endif // PHONG
