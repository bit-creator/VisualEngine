#ifdef BUMP

ATTRIBUTE(POSITION_ATTRIBUTE_LOCATION) 	vec3 aCoord;
ATTRIBUTE(NORMAL_ATTRIBUTE_LOCATION) 	vec3 aNormal;
ATTRIBUTE(TANGENT_ATTRIBUTE_LOCATION) 	vec3 aTangent;
ATTRIBUTE(BITANGENT_ATTRIBUTE_LOCATION) vec3 aBiTangent;

ATTRIBUTE(TEXTURE_ATTRIBUTE_LOCATION) 	vec2 aTexCoord;

// matrices
uniform mat4 uModelMat;
uniform mat4 uMVPMat;

uniform mat3 uNormalMat;

// camera position
uniform vec3 uCamPos;

// output data
out mat3 vTBNMat;
out vec3 vNormal;
out vec3 vView;
out vec3 vPos;

out vec2 vTexCoords;

void main() {
    gl_Position = uMVPMat * vec4(aCoord, 1.0);

    vTexCoords = aTexCoord;
    vNormal = normalize(uNormalMat * aNormal);
    vPos = (uModelMat * vec4(aCoord, 1.0)).xyz;

    vec3 tangent = normalize((uModelMat * vec4(aTangent, 0.0)).xyz);
    vec3 biTangent = normalize((uModelMat * vec4(aBiTangent, 0.0)).xyz);

    vTBNMat = mat3(-tangent, -biTangent, vNormal);

#	ifdef USE_PERSPECTIVE_CAMERA
    	vView = (uModelMat * vec4(aCoord, 1.0)).xyz - uCamPos;
#	else 
    	vView = vec3(0.0, 0.0, 1.0);
#	endif
}
#endif // BUMP
