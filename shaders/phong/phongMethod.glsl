#ifdef PHONG

vec4 PhongLighting(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor,
		vec3 lightDir, vec3 normal, vec3 viewDir, float roughness) {
	float diffFactor = dot(normal, -lightDir);

	vec3 _half = -normalize(lightDir + viewDir);
	float specFactor = pow(max(dot(_half, normal), 0.0), roughness);

	if (diffFactor < 0) specFactor = 0;

	diffFactor = clamp(diffFactor, 0.0, 1.0);
	specFactor = clamp(specFactor, 0.0, 1.0);

	return ambientColor + diffuseColor * diffFactor + specularColor * specFactor;
}

#endif // PHONG
