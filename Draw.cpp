/*
 * Draw.cpp
 *
 *  Created on: 19 ���. 2021 �.
 *      Author: IAbernikhin
 */

#include "Draw.h"
#include "Material/MaterialTypes.hpp"
#include "engine.h"

#include "GL/vertexarray.h"

bool operator ==(const Draw& lhs, const Draw& rhs) noexcept {
	return lhs._type                 == rhs._type
		&& lhs._attribHash           == rhs._attribHash
		&& lhs._numOfLight           == rhs._numOfLight
		&& lhs._hasAmbientMap        == rhs._hasAmbientMap
		&& lhs._hasDiffuseMap        == rhs._hasDiffuseMap
		&& lhs._hasSpecularMap       == rhs._hasSpecularMap
		&& lhs._hasRougnessMap       == rhs._hasRougnessMap
		&& lhs._hasNormalMap         == rhs._hasNormalMap
		&& lhs._hasHeightMap         == rhs._hasHeightMap
		&& lhs._hasSkyBoxMap         == rhs._hasSkyBoxMap
		&& lhs._hasPerspectiveCamera == rhs._hasPerspectiveCamera;
}

std::string Draw::genDefines() const {
	std::bitset<NUM_ATTRIBUTES> 	hash(_attribHash);
	std::string defines = Engine::window.getVersion();

	auto atribDefGenerator = [](std::string Attr, int loc) -> std::string {
		return "#define HAS_" + Attr + "_ATTRUBUTE\n"
				+ "#define " + Attr + "_ATTRIBUTE_LOCATION "
				+ std::to_string(loc)
				+ "\n";
	};

	if (_type == (int)ShaderType::SHADER_BUMP)   defines += "#define BUMP\n";
	if (_type == (int)ShaderType::SHADER_GLASS)  defines += "#define GLASS\n";
	if (_type == (int)ShaderType::SHADER_GLOSSY) defines += "#define GLOSSY\n";
	if (_type == (int)ShaderType::SHADER_PHONG)  defines += "#define PHONG\n";
	if (_type == (int)ShaderType::SHADER_SKYBOX) defines += "#define SKYBOX\n";
	if (_type == (int)ShaderType::SHADER_SCREEN) defines += "#define SCREEN\n";

	if (hash[(int)Attribute::ATTRIB_BITANGENT]) defines += atribDefGenerator("BITANGENT", (int)Attribute::ATTRIB_BITANGENT);
	if (hash[(int)Attribute::ATTRIB_COLOR])     defines += atribDefGenerator("COLOR",     (int)Attribute::ATTRIB_COLOR);
	if (hash[(int)Attribute::ATTRIB_NORMAL])    defines += atribDefGenerator("NORMAL",    (int)Attribute::ATTRIB_NORMAL);
	if (hash[(int)Attribute::ATTRIB_POSITION])  defines += atribDefGenerator("POSITION",  (int)Attribute::ATTRIB_POSITION);
	if (hash[(int)Attribute::ATTRIB_TANGENT])   defines += atribDefGenerator("TANGENT",   (int)Attribute::ATTRIB_TANGENT);
	if (hash[(int)Attribute::ATTRIB_TEX])       defines += atribDefGenerator("TEXTURE",   (int)Attribute::ATTRIB_TEX);

	if (_hasAmbientMap)		   defines += "#define HAS_AMBIENT_MAP\n";
	if (_hasDiffuseMap)		   defines += "#define HAS_DIFFUSE_MAP\n";
	if (_hasSpecularMap)	   defines += "#define HAS_SPECULAR_MAP\n";
	if (_hasRougnessMap)	   defines += "#define HAS_ROUGNESS_MAP\n";
	if (_hasNormalMap)	  	   defines += "#define HAS_NORMAL_MAP\n";
	if (_hasHeightMap)	   	   defines += "#define HAS_HEIGHT_MAP\n";
	if (_hasSkyBoxMap)	   	   defines += "#define HAS_SKYBOX_MAP\n";
	if (_hasPerspectiveCamera) defines += "#define USE_PERSPECTIVE_CAMERA\n";

	defines += "#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in\n";
	defines += "#define NUM_OF_LIGHT " + std::to_string(_numOfLight) + "\n";

	return defines;

}



