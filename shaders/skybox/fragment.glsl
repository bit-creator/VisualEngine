//#ifdef SKYBOX
TARGET(SCREEN_TARGET_LOCATION) vec4  color;

in vec3 vTexCoords;
uniform samplerCube uSkyBox;

void main() {
	color = texture(uSkyBox, vTexCoords);
}
//#endif // SKYBOX
