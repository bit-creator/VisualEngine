#ifdef PHONG

void main() {
  vec3 normal = normalize(vNormal);
  vec3 view = normalize(vView);

  vec4 _color;

  vec4 ambientColor = uAmbientColor;
  vec4 diffuseColor = uDiffuseColor;
  vec4 specularColor = uSpecularColor;

  if (uHasAmbientMap) ambientColor *= texture(uTexAmbient, vTexCoords);
  if (uHasDiffuseMap) diffuseColor *= texture(uTexDiffuse, vTexCoords);
  if (uHasSpecularMap) specularColor *= texture(uTexSpecular, vTexCoords);

  for (uint i = 0; i < 2; ++i)
	  _color += PhongLighting(ambientColor, diffuseColor, specularColor,
			(uLights[i].lightDir), normal, view, uRoughness) * uLights[i].lightColor;

  color = _color;
}

#endif // PHONG