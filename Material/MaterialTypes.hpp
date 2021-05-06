/*
 * MaterialTypes.hpp
 *
 *  Created on: 19 ���. 2021 �.
 *      Author: IAbernikhin
 */

#ifndef MATERIALTYPES_HPP_
#define MATERIALTYPES_HPP_

enum class MaterialType {
	MATERIAL_BUMP =0,
	MATERIAL_PHONG,
	MATERIAL_GLASS,
	MATERIAL_GLOSSY
};

enum class ShaderType {
  SHADER_BUMP   = (int)MaterialType::MATERIAL_BUMP,
  SHADER_PHONG  = (int)MaterialType::MATERIAL_PHONG,
  SHADER_GLASS  = (int)MaterialType::MATERIAL_GLASS,
  SHADER_GLOSSY = (int)MaterialType::MATERIAL_GLOSSY,
  SHADER_SKYBOX,
  SHADER_SCREEN
};

#endif /* MATERIALTYPES_HPP_ */
