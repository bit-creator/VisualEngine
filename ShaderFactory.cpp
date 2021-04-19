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

        } else {
        	ERROR("Shader source file is empty")
        }
    } else {
    	ERROR("Shader source file" << path << " not open")
    }

    return std::string("").c_str();
}

ShaderProgram& ShaderFactory::getShader(const Draw& draw) {
	if (_shaders[draw] == nullptr) {
	    auto shader = createShader(draw);
	    _shaders[draw] = std::move(shader);
	}
	return *_shaders[draw];
}

ShaderFactory::ShaderFactory() {
	_vertexShadersSources += loadShaderFromFile("shaders/vertex.glsl");
	_vertexShadersSources += loadShaderFromFile("shaders/skybox/skybox.vert.glsl");

	_fragmentShadersSources += loadShaderFromFile("shaders/phong.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/paralax.glsl");;
	_fragmentShadersSources += loadShaderFromFile("shaders/fragment.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/glass/glass.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/glossy/glossy.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/skybox/skybox.frag.glsl");
}

PrgPtr ShaderFactory::createShader(const Draw& draw) {
	VertexShader vertex;
	FragmentShader frag;

	auto defines = draw.genDefines();

	vertex.addSource(defines);
	vertex.addSource(_vertexShadersSources);

	frag.addSource(defines);
	frag.addSource(_fragmentShadersSources);

	auto shaderPrg = std::make_unique<ShaderProgram>();

	shaderPrg -> attachShader(vertex);
	shaderPrg -> attachShader(frag);
	shaderPrg -> link();

	return shaderPrg;
}
