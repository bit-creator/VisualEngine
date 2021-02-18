/*
 * ShaderFactory.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include "ShaderFactory.h"

inline std::string loadShaderFromFile(const std::string& path) noexcept {
    std::ifstream in(path, std::ios::in);

    if (in.is_open()) {
        if (in.peek() != EOF) {
            std::string source = "", sourceline = "\n";
            while (getline(in, sourceline, '\n')) {
            	if(!sourceline.empty()) {
            		source.append(sourceline);
                }
                source.push_back('\n');
            }
            return source.c_str();

        } else std::cout << "| EROR | Shader source file is empty" << std::endl;

    } else  std::cout << "| EROR | Shader source file " << path <<" not open" << std::endl;

    return std::string("").c_str();
}

ShaderProgram& ShaderFactory::getShader(ShaderType type) {
	if (_shaders[type] == nullptr) {
	    auto shader = createShader(type);
	    _shaders[type] = std::move(shader);
	}
	return *_shaders[type];
}


void ShaderFactory::addVertexShaderSourceFile(ShaderType type,
		std::string vertPath) {
	if (_vertexShadersSources[type] == nullptr) {
		_vertexShadersSources[type] = std::make_shared<VertexShader>();
	}
	_vertexShadersSources[type]->addSource(std::forward<std::string>(loadShaderFromFile(vertPath)));
}

void ShaderFactory::addFragmentShaderSourceFile(ShaderType type,
		std::string fragPath) {
	if (_fragmentShadersSources[type] == nullptr) {
		_fragmentShadersSources[type] = std::make_shared<FragmentShader>();
	}
	_fragmentShadersSources[type]->addSource(std::forward<std::string>(loadShaderFromFile(fragPath)));
}

ShaderFactory::ShaderFactory() {
	addVertexShaderSourceFile(SHADER_BUMP, "shaders/bumpMapping/bump.vert.glsl");
	addVertexShaderSourceFile(SHADER_PHONG, "shaders/phong/phong.vert.glsl");
	addVertexShaderSourceFile(SHADER_GLASS, "shaders/glass/glass.vert.glsl");
	addVertexShaderSourceFile(SHADER_GLOSSY, "shaders/glossy/glossy.vert.glsl");
	addVertexShaderSourceFile(SHADER_SKYBOX, "shaders/skybox/skybox.vert.glsl");

	addFragmentShaderSourceFile(SHADER_BUMP, "shaders/bumpMapping/bump.frag.glsl");
	addFragmentShaderSourceFile(SHADER_PHONG, "shaders/phong/phongMethod.glsl");
	addFragmentShaderSourceFile(SHADER_PHONG, "shaders/phong/phong.frag.glsl");
	addFragmentShaderSourceFile(SHADER_GLASS, "shaders/glass/glass.frag.glsl");
	addFragmentShaderSourceFile(SHADER_GLOSSY, "shaders/glossy/glossy.frag.glsl");
	addFragmentShaderSourceFile(SHADER_SKYBOX, "shaders/skybox/skybox.frag.glsl");
}

PrgPtr ShaderFactory::createShader(ShaderType type) {
//	VertexShader vert;
//	FragmentShader frag;
//
//	switch(type) {
//	case SHADER_BUMP: {
//		vert.addSource(loadShaderFromFile("shaders/bumpMapping/bump.vert.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/bumpMapping/bump.frag.glsl"));
//		break;
//	}
//
//	case SHADER_PHONG: {
//		vert.addSource(loadShaderFromFile("shaders/phong/phong.vert.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/phong/phongMethod.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/phong/phong.frag.glsl"));
//		break;
//	}
//
//	case SHADER_SKYBOX: {
//		vert.addSource(loadShaderFromFile("shaders/skybox/skybox.vert.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/skybox/skybox.frag.glsl"));
//		break;
//	}
//
//	case SHADER_GLASS: {
//		vert.addSource(loadShaderFromFile("shaders/glass/glass.vert.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/glass/glass.frag.glsl"));
//		break;
//	}
//
//	case SHADER_GLOSSY: {
//		vert.addSource(loadShaderFromFile("shaders/glossy/glossy.vert.glsl"));
//		frag.addSource(loadShaderFromFile("shaders/glossy/glossy.frag.glsl"));
//	}
//	}

	auto shaderPrg = std::make_unique<ShaderProgram>();

	shaderPrg -> attachShader(*_vertexShadersSources[type]);
	shaderPrg -> attachShader(*_fragmentShadersSources[type]);
	shaderPrg -> link();

	return shaderPrg;
}
