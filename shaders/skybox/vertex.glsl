#ifdef SKYBOX
ATTRIBUTE(POSITION_ATTRIBUTE_LOCATION) 	vec3 aCoord;

uniform mat4 uSkyBoxMVPMat;

out vec3 vTexCoords;

void main() {
	vTexCoords = aCoord;
    gl_Position = uSkyBoxMVPMat * vec4(aCoord * 50, 1.0);
}
#endif //SKYBOX
