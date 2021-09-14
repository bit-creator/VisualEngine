/*
 * ShaderFactory.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include <fstream>
#include "ShaderFactory.h"
#include "Material/MaterialTypes.hpp"

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
            return source;

        } else {
        	ERROR("Shader source file is empty")
        }
    } else {
    	ERROR("Shader source file" << path << " not open")
    }

    return std::string("");
}

ShaderProgram& ShaderFactory::getShader(const Draw& draw) {
	if (_shaders[draw] == nullptr) {
	    auto shader = createShader(draw);
	    _shaders[draw] = std::move(shader);
	}
	return *_shaders[draw];
}

ShaderFactory::ShaderFactory() {
	_vertexShadersSources.insert({"vertex", std::move(loadShaderFromFile("shaders/vertex.glsl"))});
	_vertexShadersSources.insert({"skybox", std::move(loadShaderFromFile("shaders/skybox/vertex.glsl"))});
	_vertexShadersSources.insert({"screen", std::move(loadShaderFromFile("shaders/screen/vertex.glsl"))});
	_vertexShadersSources.insert({"defered", std::move(loadShaderFromFile("shaders/defered/vertex.glsl"))});
	_vertexShadersSources.insert({"texture", std::move(loadShaderFromFile("shaders/postProcesing/vertex.glsl"))});

	_fragmentShadersSources.insert({"phong",    std::move(loadShaderFromFile("shaders/phong.glsl"))});
	_fragmentShadersSources.insert({"paralax",  std::move(loadShaderFromFile("shaders/paralax.glsl"))});
	_fragmentShadersSources.insert({"fragment", std::move(loadShaderFromFile("shaders/fragment.glsl"))});
	_fragmentShadersSources.insert({"glossy",   std::move(loadShaderFromFile("shaders/glossy/fragment.glsl"))});
	_fragmentShadersSources.insert({"skybox",   std::move(loadShaderFromFile("shaders/skybox/fragment.glsl"))});
	_fragmentShadersSources.insert({"screen",   std::move(loadShaderFromFile("shaders/screen/fragment.glsl"))});
	_fragmentShadersSources.insert({"defered",   std::move(loadShaderFromFile("shaders/defered/fragment.glsl"))});
	_fragmentShadersSources.insert({"texture",   std::move(loadShaderFromFile("shaders/postProcesing/fragment.glsl"))});


//	_vertexShadersSources["vertex"] = loadShaderFromFile("shaders/vertex.glsl");
//	_vertexShadersSources["skybox"] = loadShaderFromFile("shaders/skybox/vertex.glsl");
//
//	_fragmentShadersSources["phong"]    = loadShaderFromFile("shaders/phong.glsl");
//	_fragmentShadersSources["paralax"]  = loadShaderFromFile("shaders/paralax.glsl");
//	_fragmentShadersSources["fragment"] = loadShaderFromFile("shaders/fragment.glsl");
//	_fragmentShadersSources["glossy"]   = loadShaderFromFile("shaders/glossy/fragment.glsl");
//	_fragmentShadersSources["skybox"]   = loadShaderFromFile("shaders/skybox/fragment.glsl");

	//	_fragmentShadersSources += loadShaderFromFile("shaders/glass/glass.frag.glsl");
}

PrgPtr ShaderFactory::createShader(const Draw& draw) {
	VertexShader vertex;
	FragmentShader frag;

	const auto&& defines = draw.genDefines();

	vertex.addSource(std::move(defines));
	if (draw._shaderType == (int)ShaderType::SHADER_SKYBOX) vertex.addSource(_vertexShadersSources["skybox"]);
	else if (draw._shaderType == (int)ShaderType::SHADER_SCREEN) vertex.addSource(_vertexShadersSources["screen"]);
	else if (draw._shaderType == (int)ShaderType::SHADER_GEOMETRY_PASS) vertex.addSource(_vertexShadersSources["defered"]);
	else if (draw._shaderType == (int)ShaderType::SHADER_TEXTURE_RENDER) vertex.addSource(_vertexShadersSources["texture"]);
	else vertex.addSource(_vertexShadersSources["vertex"]);

	frag.addSource(std::move(defines));
	if (draw._materialType == (int)ShaderType::SHADER_BUMP) frag.addSource(_fragmentShadersSources["paralax"]);

	if (draw._shaderType == (int)ShaderType::SHADER_SKYBOX) frag.addSource(_fragmentShadersSources["skybox"]);
	else if (draw._shaderType == (int)ShaderType::SHADER_SCREEN) {
		frag.addSource(_fragmentShadersSources["phong"]);
		frag.addSource(_fragmentShadersSources["screen"]);
	}
	else if (draw._shaderType == (int)ShaderType::SHADER_TEXTURE_RENDER) frag.addSource(_fragmentShadersSources["texture"]);
	else if (draw._shaderType == (int)ShaderType::SHADER_GEOMETRY_PASS) frag.addSource(_fragmentShadersSources["defered"]);
	else {
		frag.addSource(_fragmentShadersSources["phong"]);
		if(draw._shaderType == (int)ShaderType::SHADER_GLOSSY) frag.addSource(_fragmentShadersSources["glossy"]);
		else {
			if (draw._shaderType == (int)ShaderType::SHADER_BUMP) frag.addSource(_fragmentShadersSources["paralax"]);
			frag.addSource(_fragmentShadersSources["fragment"]);
		}
	}

	auto shaderPrg = ShaderProgram::create();

	shaderPrg -> attachShader(vertex);
	shaderPrg -> attachShader(frag);
	shaderPrg -> link();

	return shaderPrg;
}
