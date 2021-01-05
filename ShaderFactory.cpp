/*
 * ShaderFactory.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include "ShaderFactory.h"

ShaderProgram& ShaderFactory::getShader(ShaderType type) {
	if (_shaders[type] == nullptr) {
	    auto shader = createShader(type);
	    _shaders[type] = std::move(shader);
	}
	return *_shaders[type];
}

PrgPtr ShaderFactory::createShader(ShaderType type) {
	VertexShader vert;
	FragmentShader frag;

	if (type == SHADER_PHONG) {
		vert.addSource(loadShaderFromFile("shaders/primitive/primitive.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/primitive/primitive.frag.glsl"));
	}
	else if (type == SHADER_SKYBOX) {
		vert.addSource(loadShaderFromFile("shaders/skybox/skybox.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/skybox/skybox.frag.glsl"));
	}

	auto shaderPrg = std::make_unique<ShaderProgram>();

	shaderPrg -> attachShader(vert);
	shaderPrg -> attachShader(frag);
	shaderPrg -> link();

	return shaderPrg;
}
