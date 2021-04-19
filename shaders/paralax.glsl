#ifdef BUMP

vec2 paralax(sampler2D texHeight, vec3 viewVec, vec2 currentTex, float scale) {
	const float height_scale = scale;
    const float numLayers = 20;

    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;

	vec2 currentTexCoords = currentTex;
    vec2 P = viewVec.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;

	float currentDepthMapValue = 1 - texture(texHeight, currentTexCoords).r;

	while(currentLayerDepth < currentDepthMapValue) {
	    currentTexCoords -= deltaTexCoords;
	    currentDepthMapValue = 1 - texture(texHeight, currentTexCoords).r;
	    currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = 1 - texture(texHeight, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}

#endif // BUMP