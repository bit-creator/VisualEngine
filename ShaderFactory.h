/*
 * ShaderFactory.h
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#ifndef SHADERFACTORY_H_
#define SHADERFACTORY_H_

#include <filesystem>
#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "GL/shaderprogram.h"

enum ShaderType {
  SHADER_BUMP,
  SHADER_PHONG,
  SHADER_SKYBOX,
  SHADER_GLASS,
  SHADER_GLOSSY
};

using shaderTree = std::map < ShaderType, PrgPtr >;

class ShaderFactory final {
private:
	shaderTree								 					_shaders;
	std::string 												_vertexShadersSources;
	std::string													_fragmentShadersSources;

public:
	ShaderFactory();
	ShaderProgram& getShader(ShaderType type);

private:
	PrgPtr createShader(ShaderType type);
};

#endif /* SHADERFACTORY_H_ */
