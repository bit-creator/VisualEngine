ATTRIBUTE(POSITION_ATTRIBUTE_LOCATION) 	vec2 aCoord;

out vec2 vTexCoord;

void main() {
    gl_Position = vec4(aCoord, 0.0, 1.0);
    vTexCoord = (aCoord + 1) / 2;
}  
