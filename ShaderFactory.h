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

namespace fs = std::filesystem;

enum ShaderType {
  SHADER_PHONG,
  SHADER_SKYBOX
};

using shaderTree = std::map < ShaderType, PrgPtr >;

class ShaderFactory final {
private:
	ShaderFactory();
	~ShaderFactory();
	ShaderFactory(const ShaderFactory &other) = delete;
	ShaderFactory(ShaderFactory &&other) = delete;
	ShaderFactory& operator=(const ShaderFactory &other) = delete;
	ShaderFactory& operator=(ShaderFactory &&other) = delete;

	shaderTree								 					_shaders;
	bool														_loaded;
	bool														_compiled;

public:
	static ShaderFactory& getInstance() noexcept;

//	void loadShaders(std::string path);

	ShaderProgram& getShader(ShaderType type);

private:
	PrgPtr
	createShader(ShaderType type);
//
//	  std::string fragmentSource;
//	  std::string vertexSource;
//
//	  if (type == SHADER_PHONG) {
//	    fragmentSource = readFile("Shaders/frag.glsl");
//	    vertexSource = readFile("Shaders/vert.glsl");
//	  } else if (type == SHADER_SKYBOX) {
//	    fragmentSource = readFile("Shaders/skybox.frag.glsl");
//	    vertexSource = readFile("Shaders/skybox.vert.glsl");
//	  }

//	Program& ShaderFactory::getShader(ShaderType type) {
//	  if (_shaders[type] == nullptr) {
//	    auto shader = createShader(type);
//	    _shaders[type] = std::move(shader);
//	  }
//
//	  return *_shaders[type];
//	}

//	Да, отнаследуй от шейдера вертекс шейдер и фрагмент шейдер, в аттач шейдер программы сделай перегрузку по типу
//	В более общем случае нужно сделать
//	Program& getShader(ShaderType type, CameraType, LightsCount);
};

#endif /* SHADERFACTORY_H_ */
