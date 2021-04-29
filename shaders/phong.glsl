/**
 * impliment PHONG lighting
 */

//#if defined(PHONG) || defined(BUMP) || defined(GLOSSY)

vec4 calculateLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor, vec4 scatterColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float roughness, float scatterWidth, float wrap) {
	float scatterFactor = 0.0;

	float diffFactor = (dot(normal, -lightDir) + wrap) / (1 + wrap);
	
#	ifdef WRAP	 
		scatterFactor = smoothstep(0.0, scatterWidth, diffFactor) *
			smoothstep(scatterWidth * 3.0, scatterWidth, diffFactor);
#	endif // WRAP

	vec3 _half = -normalize(lightDir + viewDir);
	float specFactor = pow(max(dot(_half, normal), 0.0), roughness);

	if (diffFactor < 0) specFactor = 0;

	diffFactor = clamp(diffFactor, 0.0, 1.0);
	specFactor = clamp(specFactor, 0.0, 1.0);

	return ambientColor + diffuseColor * diffFactor + specularColor * specFactor + scatterFactor * scatterColor;
}

//#endif // PHONG || BUMP
