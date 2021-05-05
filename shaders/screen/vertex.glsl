ATTRIBUTE(POSITION_ATTRIBUTE_LOCATION) 	vec2 aCoord;
ATTRIBUTE(TEXTURE_ATTRIBUTE_LOCATION) 	vec2 aTexCoord;

out vec2 vTexCoord;

void main() {
    gl_Position = vec4(aCoord.x, aCoord.y, 0.0, 1.0); 
    vTexCoord = aTexCoord;
}  