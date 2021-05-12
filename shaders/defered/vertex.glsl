//#ifdef DEFERED

ATTRIBUTE(POSITION_ATTRIBUTE_LOCATION) 	vec3 aCoord;
ATTRIBUTE(NORMAL_ATTRIBUTE_LOCATION) 	vec3 aNormal;

#ifdef BUMP
	ATTRIBUTE(TANGENT_ATTRIBUTE_LOCATION) 	vec3 aTangent;
	ATTRIBUTE(BITANGENT_ATTRIBUTE_LOCATION) vec3 aBiTangent;
#endif // BUMP

ATTRIBUTE(TEXTURE_ATTRIBUTE_LOCATION) 	vec2 aTexCoord;

// matrices
uniform mat4 uModelMat;
uniform mat4 uMVPMat;

uniform mat3 uNormalMat;

uniform vec3 uCamPos;

out GEOMETRY_PASS {
	#ifdef BUMP
		mat3 gTBNMat;
	#endif // BUMP

	vec3 gNormal;
	vec3 gView;

	vec2 gTexCoords;
} g_out;

void main() {
    gl_Position = uMVPMat * vec4(aCoord, 1.0);

    g_out.gTexCoords = aTexCoord;
    g_out.gNormal = normalize(uNormalMat * aNormal);
//    vPos = (uModelMat * vec4(aCoord, 1.0)).xyz;

#	ifdef BUMP
    	vec3 tangent = normalize((uModelMat * vec4(aTangent, 0.0)).xyz);
    	vec3 biTangent = normalize((uModelMat * vec4(aBiTangent, 0.0)).xyz);

    	g_out.gTBNMat = mat3(-tangent, -biTangent, g_out.gNormal);
#	endif // BUMP

#	ifdef USE_PERSPECTIVE_CAMERA
    	g_out.gView = (uModelMat * vec4(aCoord, 1.0)).xyz - uCamPos;
#	else
    	g_out.gView = vec3(0.0, 0.0, 1.0);
#	endif
}

//#endif // DEFERED
