out vec4 color;
  
in vec2 vTexCoord;

uniform sampler2D uScreen;

void main() {
	color = texture(uScreen, vTexCoord);
}