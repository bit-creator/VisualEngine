#ifdef HAS_SCREEN_TARGET
	TARGET(SCREEN_TARGET_LOCATION) vec4 color;
#else
	out vec4 color;
#endif // SCREEN_TARGET_LOCATION

in vec3 vTexCoords;
uniform samplerCube uSkyBox;

void main() {
	color = texture(uSkyBox, vTexCoords);
//	color = vec4(1.0);
}
//#endif // SKYBOX
