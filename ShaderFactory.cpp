/*
 * ShaderFactory.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include "ShaderFactory.h"

ShaderFactory::ShaderFactory()
//	: _shaders({})
	: _loaded(false)
	, _compiled(false)
{  }

ShaderFactory::~ShaderFactory() {
}

ShaderFactory& ShaderFactory::getInstance() noexcept {
	static ShaderFactory factory; return factory;
}

//void ShaderFactory::loadShaders(std::string path) {
//    std::cout << "|    INFO    | start shader compilation process\n";
//
//    for (const auto& filePath : fs::recursive_directory_iterator(path))
//    {
//        if(filePath.is_directory()) continue;
//        auto name = filePath.path();
//
//        std::cout << "\n\n" << name << "\n\n";
//
////        const auto [iterator, insert] = _fragmentShaderTree.emplace(std::make_pair
////              (name.string(), std::move(Shader(GL_FRAGMENT_SHADER))));
//
//        std::cout << "\t\t| SUCCSESSFUL | "<< name << " fragment shader insert\n";
//    }
//}

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
