/*
 * ShaderFactory.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: bit_creator
 */

#include "ShaderFactory.h"
#include "engine.h"

//std::string version ="#version 460 core\n";

std::string layoutDef = "\
#define ATTRIB_COORD_LOC 0\n\
#define ATTRIB_NORMAL_LOC 1\n\
#define ATTRIB_TANGENT_LOC 2\n\
#define ATTRIB_BITANGENT_LOC 3\n\
#define ATTRIB_COLOR_LOC 4\n\
#define ATTRIB_TEXCOORD_LOC 5\n\
#define ATTRIBUTE(LOCATION) layout(location = LOCATION) in\n";

inline std::string typeToDef(const ShaderType type) {
	if (type == ShaderType::SHADER_BUMP)   return "#define BUMP\n";
	if (type == ShaderType::SHADER_GLASS)  return "#define GLASS\n";
	if (type == ShaderType::SHADER_GLOSSY) return "#define GLOSSY\n";
	if (type == ShaderType::SHADER_PHONG)  return "#define PHONG\n";
	if (type == ShaderType::SHADER_SKYBOX) return "#define SKYBOX\n";
}

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

ShaderProgram& ShaderFactory::getShader(ShaderType type) {
	if (_shaders[type] == nullptr) {
	    auto shader = createShader(type);
	    _shaders[type] = std::move(shader);
	}
	return *_shaders[type];
}

ShaderFactory::ShaderFactory() {
	_vertexShadersSources += loadShaderFromFile("shaders/bumpMapping/bump.vert.glsl");
	_vertexShadersSources += loadShaderFromFile("shaders/phong/phong.vert.glsl");
	_vertexShadersSources += loadShaderFromFile("shaders/glass/glass.vert.glsl");
	_vertexShadersSources += loadShaderFromFile("shaders/glossy/glossy.vert.glsl");
	_vertexShadersSources += loadShaderFromFile("shaders/skybox/skybox.vert.glsl");

	_fragmentShadersSources += loadShaderFromFile("shaders/bumpMapping/bump.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/phong/phongMethod.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/phong/phong.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/glass/glass.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/glossy/glossy.frag.glsl");
	_fragmentShadersSources += loadShaderFromFile("shaders/skybox/skybox.frag.glsl");
}

PrgPtr ShaderFactory::createShader(ShaderType type) {
	VertexShader vertex;
	FragmentShader frag;

	vertex.addSource(Engine::window.getVersion());
	vertex.addSource(layoutDef);
	vertex.addSource(typeToDef(type));
	vertex.addSource(_vertexShadersSources);

	frag.addSource(Engine::window.getVersion());
	frag.addSource(typeToDef(type));
	frag.addSource(_fragmentShadersSources);

	auto shaderPrg = std::make_unique<ShaderProgram>();

	shaderPrg -> attachShader(vertex);
	shaderPrg -> attachShader(frag);
	shaderPrg -> link();

	return shaderPrg;
}
