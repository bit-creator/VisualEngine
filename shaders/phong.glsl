/**
 * impliment PHONG lighting
 */

//#if defined(PHONG) || defined(BUMP) || defined(GLOSSY)

vec4 calculateDirLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float roughness) {
	float diffFactor = dot(normal, -lightDir);

	vec3 _half = -normalize(lightDir + viewDir);
	float specFactor = pow(max(dot(_half, normal), 0.0), roughness);

	if (diffFactor < 0) specFactor = 0;

	diffFactor = clamp(diffFactor, 0.0, 1.0);
	specFactor = clamp(specFactor, 0.0, 1.0);

	return ambientColor + diffuseColor * diffFactor + specularColor * specFactor;
}

vec4 calculatePointLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightPos, vec3 normal, vec3 camPos, vec3 viewDir, float viewLen, float roughness) {
	vec3 lightDir = normalize(viewDir) * viewLen - (lightPos - camPos);
	float distance    = length(lightDir);
	float attenuation = 1.0 / (1.0 + 0.09* distance +
	    		    0.032 * (distance * distance));


	float diffFactor = dot(normal, -lightDir);

	vec3 _half = -normalize(lightDir + viewDir);
	float specFactor = pow(max(dot(_half, normal), 0.0), roughness);

	if (diffFactor < 0) specFactor = 0;

	diffFactor = clamp(diffFactor, 0.0, 1.0);
	specFactor = clamp(specFactor, 0.0, 1.0);

	return attenuation * (ambientColor + diffuseColor * diffFactor + specularColor * specFactor);
	return vec4(1.0);
}

vec4 calculateSpotLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float roughness) {
	return vec4(0.0);
}

//#endif // PHONG || BUMP
