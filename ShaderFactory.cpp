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

	switch(type) {
	case SHADER_BUMP: {
		vert.addSource(loadShaderFromFile("shaders/bumpMapping/bump.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/bumpMapping/bump.frag.glsl"));
		break;
	}

	case SHADER_PHONG: {
		vert.addSource(loadShaderFromFile("shaders/phong/phong.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/phong/phong.frag.glsl"));
		break;
	}

	case SHADER_SKYBOX: {
		vert.addSource(loadShaderFromFile("shaders/skybox/skybox.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/skybox/skybox.frag.glsl"));
		break;
	}

	case SHADER_GLASS: {
		vert.addSource(loadShaderFromFile("shaders/glass/glass.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/glass/glass.frag.glsl"));
		break;
	}

	case SHADER_GLOSSY: {
		vert.addSource(loadShaderFromFile("shaders/glossy/glossy.vert.glsl"));
		frag.addSource(loadShaderFromFile("shaders/glossy/glossy.frag.glsl"));
	}
	}

	auto shaderPrg = std::make_unique<ShaderProgram>();

	shaderPrg -> attachShader(vert);
	shaderPrg -> attachShader(frag);
	shaderPrg -> link();

	return shaderPrg;
}
