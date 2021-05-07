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
		&& lhs._renderTargets        == rhs._renderTargets
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
	std::bitset<NUM_ATTRIBUTES> 		hash(_attribHash);
	std::bitset<NUM_RENDERING_TARGET> 	targetsHash(_renderTargets);

	std::string defines = Engine::window.getVersion();

	auto shaderTypeDefGenerator = [&defines, this](ShaderType type, std::string def) mutable -> void {
		if (_type == (int)type) defines += "#define " +  def + "\n";
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

	shaderTypeDefGenerator(ShaderType::SHADER_BUMP,   "BUMP");
	shaderTypeDefGenerator(ShaderType::SHADER_GLASS,  "GLASS");
	shaderTypeDefGenerator(ShaderType::SHADER_GLOSSY, "GLOSSY");
	shaderTypeDefGenerator(ShaderType::SHADER_PHONG,  "PHONG");
	shaderTypeDefGenerator(ShaderType::SHADER_SKYBOX, "SKYBOX");
	shaderTypeDefGenerator(ShaderType::SHADER_SCREEN, "SCREEN");

	atribDefGenerator(Attribute::ATTRIB_BITANGENT, "BITANGENT");
	atribDefGenerator(Attribute::ATTRIB_COLOR, 	   "COLOR");
	atribDefGenerator(Attribute::ATTRIB_NORMAL,    "NORMAL");
	atribDefGenerator(Attribute::ATTRIB_POSITION,  "POSITION");
	atribDefGenerator(Attribute::ATTRIB_TANGENT,   "TANGENT");
	atribDefGenerator(Attribute::ATTRIB_TEX,       "TEXTURE");

	targetDefGenerator(RenderingTarget::SCREEN, "SCREEN");
	targetDefGenerator(RenderingTarget::PICKER, "PICKER");

//	if (hash[(int)Attribute::ATTRIB_BITANGENT]) defines += atribDefGenerator("BITANGENT", Attribute::ATTRIB_BITANGENT);
//	if (hash[(int)Attribute::ATTRIB_COLOR])     defines += atribDefGenerator("COLOR",     Attribute::ATTRIB_COLOR);
//	if (hash[(int)Attribute::ATTRIB_NORMAL])    defines += atribDefGenerator("NORMAL",    Attribute::ATTRIB_NORMAL);
//	if (hash[(int)Attribute::ATTRIB_POSITION])  defines += atribDefGenerator("POSITION",  Attribute::ATTRIB_POSITION);
//	if (hash[(int)Attribute::ATTRIB_TANGENT])   defines += atribDefGenerator("TANGENT",   Attribute::ATTRIB_TANGENT);
//	if (hash[(int)Attribute::ATTRIB_TEX])       defines += atribDefGenerator("TEXTURE",   Attribute::ATTRIB_TEX);

//	if (targetsHash[(int)RenderingTarget::SCREEN]) defines += targetDefGenerator("SCREEN", RenderingTarget::SCREEN);
//	if (targetsHash[(int)RenderingTarget::PICKER]) defines += targetDefGenerator("PICKER", RenderingTarget::PICKER);

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

	defines += "#define NUM_OF_LIGHT " + std::to_string(_numOfLight) + "\n";

	return defines;

}
