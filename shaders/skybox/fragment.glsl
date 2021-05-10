#ifdef SKYBOX
TARGET(SCREEN_TARGET_LOCATION) vec4 color;
TARGET(PICKER_TARGET_LOCATION) float objectColor;

in vec3 vTexCoords;
uniform samplerCube uSkyBox;

void main() {
#	ifdef HAS_SCREEN_TARGET
  		color = texture(uSkyBox, vTexCoords);
#	endif // HAS_SCREEN_TARGET
#	ifdef HAS_PICKER_TARGET
  		objectColor = 0.0f;
#	endif // HAS_PICKER_TARGET
}
#endif // SKYBOX
