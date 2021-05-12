out vec4 color;
  
in vec2 vTexCoord;

uniform sampler2D uScreen;
uniform mat3	  uKernel;
uniform float 	  uOffset;

void main() {
	float offset = uOffset;
	float zero	 = 0.0f;
	float minusOffset  = - uOffset;

	vec4 samples[9] = {
		//top
		texture(uScreen, vTexCoord + vec2(minusOffset, offset)), // left
		texture(uScreen, vTexCoord + vec2(zero,    	   offset)), // center
 		texture(uScreen, vTexCoord + vec2(offset,      offset)), // right

		// middle
		texture(uScreen, vTexCoord + vec2(minusOffset,  zero)), // left
		texture(uScreen, vTexCoord + vec2(zero,         zero)), // center
		texture(uScreen, vTexCoord + vec2(offset,       zero)), // right

		// bottom
		texture(uScreen, vTexCoord + vec2(minusOffset,  minusOffset)), // left
		texture(uScreen, vTexCoord + vec2(zero,         minusOffset)), // center
		texture(uScreen, vTexCoord + vec2(offset,       minusOffset))  // right
	};

    vec4 fragmentColor = vec4(0.0);
    for(int i = 0; i < 3; i++)
    	for(int j = 0; j < 3; j++)
    		fragmentColor += samples[ i * j ] * uKernel[i][j];

	color = fragmentColor;
}
