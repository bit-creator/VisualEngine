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

//bool operator ==(const Draw& lhs, const Draw& rhs) noexcept {
//	return lhs._shaderType			 == rhs._shaderType
//		&& lhs._materialType         == rhs._materialType
//		&& lhs._attribHash           == rhs._attribHash
//		&& lhs._renderTargets        == rhs._renderTargets
//		&& lhs._numOfDirLight        == rhs._numOfDirLight
//		&& lhs._numOfPointLight      == rhs._numOfPointLight
//		&& lhs._numOfSpotLight       == rhs._numOfSpotLight
//		&& lhs._hasAmbientMap        == rhs._hasAmbientMap
//		&& lhs._hasDiffuseMap        == rhs._hasDiffuseMap
//		&& lhs._hasSpecularMap       == rhs._hasSpecularMap
//		&& lhs._hasRougnessMap       == rhs._hasRougnessMap
//		&& lhs._hasNormalMap         == rhs._hasNormalMap
//		&& lhs._hasHeightMap         == rhs._hasHeightMap
//		&& lhs._hasSkyBoxMap         == rhs._hasSkyBoxMap
//		&& lhs._hasPerspectiveCamera == rhs._hasPerspectiveCamera;
//}

std::string Draw::genDefines() const {
	std::bitset<NUM_ATTRIBUTES> 		hash(_attribHash);
	std::bitset<NUM_RENDERING_TARGET> 	targetsHash(_renderTargets);

	std::string defines = Engine::window.getVersion();

	auto shaderTypeDefGenerator = [&defines, this](MaterialType type, std::string def) mutable -> void {
		if (_materialType == (int)type) defines += "#define " +  def + "\n"
				+ "#define MATERIAL_ID " + std::to_string((int)type + 1) + "\n";
	};

	auto atribDefGenerator = [&defines, hash, this](Attribute attr, std::string def) -> void {
		if (hash[(int)attr]) defines += "#define HAS_" + def + "_ATTRUBUTE\n"
				+ "#define " + def + "_ATTRIBUTE_LOCATION "
				+ std::to_string((int)attr)
				+ "\n";
	};

	auto targetDefGenerator = [&defines, targetsHash, this](RenderingTarget target, std::string def) -> void {
		if(targetsHash[(int)target]) defines += "#define HAS_" + def + "_TARGET\n"
				+ "#define " + def + "_TARGET_LOCATION "
				+ std::to_string((int)target)
				+ "\n";
	};

	shaderTypeDefGenerator(MaterialType::MATERIAL_BUMP,   "BUMP");
	shaderTypeDefGenerator(MaterialType::MATERIAL_GLASS,  "GLASS");
	shaderTypeDefGenerator(MaterialType::MATERIAL_GLOSSY, "GLOSSY");
	shaderTypeDefGenerator(MaterialType::MATERIAL_PHONG,  "PHONG");

	atribDefGenerator(Attribute::ATTRIB_BITANGENT, "BITANGENT");
	atribDefGenerator(Attribute::ATTRIB_COLOR, 	   "COLOR");
	atribDefGenerator(Attribute::ATTRIB_NORMAL,    "NORMAL");
	atribDefGenerator(Attribute::ATTRIB_POSITION,  "POSITION");
	atribDefGenerator(Attribute::ATTRIB_TANGENT,   "TANGENT");
	atribDefGenerator(Attribute::ATTRIB_TEX,       "TEXTURE");

	targetDefGenerator(RenderingTarget::ALBEDO,    "ALBEDO");
	targetDefGenerator(RenderingTarget::NORMAL,    "NORMAL");
	targetDefGenerator(RenderingTarget::VIEW,      "VIEW");
	targetDefGenerator(RenderingTarget::PICKER,    "PICKER");
	targetDefGenerator(RenderingTarget::SCREEN,    "SCREEN");

	if (targetsHash[(int)RenderingTarget::PICKER]) {
		defines += "#define PICKER_COMPONENT " + std::to_string(sizeof(Object3D::ID_t)) + "\n";
		switch (sizeof(Object3D::ID_t)) {
		case 1:
			defines += "#define PICKER_INTERNAL_TYPE float\n";
			defines += "#define PICKER_SWIZZLE .r\n";
			break;
		case 2:
			defines += "#define PICKER_INTERNAL_TYPE vec2\n";
			defines += "#define PICKER_SWIZZLE .rg\n";
			break;
		case 3:
			defines += "#define PICKER_INTERNAL_TYPE vec3\n";
			defines += "#define PICKER_SWIZZLE .rgb\n";
			break;
		case 4:
			defines += "#define PICKER_INTERNAL_TYPE vec4\n";
			defines += "#define PICKER_SWIZZLE\n";
			break;
		}
	}

	if (_hasAmbientMap)		   defines += "#define HAS_AMBIENT_MAP\n";
	if (_hasDiffuseMap)		   defines += "#define HAS_DIFFUSE_MAP\n";
	if (_hasSpecularMap)	   defines += "#define HAS_SPECULAR_MAP\n";
	if (_hasRougnessMap)	   defines += "#define HAS_ROUGNESS_MAP\n";
	if (_hasNormalMap)	  	   defines += "#define HAS_NORMAL_MAP\n";
	if (_hasHeightMap)	   	   defines += "#define HAS_HEIGHT_MAP\n";
	if (_hasSkyBoxMap)	   	   defines += "#define HAS_SKYBOX_MAP\n";
	if (_hasPerspectiveCamera) defines += "#define USE_PERSPECTIVE_CAMERA\n";

	defines += "#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in\n";
	defines += "#define TARGET(LOCATION) layout(location = LOCATION) out\n";

	if(_numOfDirLight) {
		defines += "#define HAS_DIRECTIONAL_LIGHT\n";
		defines += "#define NUM_OF_DIRECTIONAL_LIGHT " + std::to_string(_numOfDirLight) + "\n";
	}

	if(_numOfPointLight) {
		defines += "#define HAS_POINT_LIGHT\n";
		defines += "#define NUM_OF_POINT_LIGHT " + std::to_string(_numOfPointLight) + "\n";
	}

	if(_numOfSpotLight) {
		defines += "#define HAS_SPOT_LIGHT\n";
		defines += "#define NUM_OF_SPOT_LIGHT " + std::to_string(_numOfSpotLight) + "\n";
	}

	return defines;

}
