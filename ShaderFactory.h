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
#include <unordered_map>

#include "GL/shaderprogram.h"

#include "Draw.h"
#include "MaterialTypes.hpp"

using shaderTree = std::unordered_map < Draw, PrgPtr >;

class ShaderFactory final {
private:
	shaderTree								 					_shaders;
	std::string 												_vertexShadersSources;
	std::string													_fragmentShadersSources;

public:
	ShaderFactory();
	ShaderProgram& getShader(const Draw& draw);

private:
	PrgPtr createShader(const Draw& draw);
};

#endif /* SHADERFACTORY_H_ */
