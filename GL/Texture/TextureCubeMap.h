/*
 * TextureCubeMap.h
 *
 *  Created on: Dec 15, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE_TEXTURECUBEMAP_H_
#define GL_TEXTURE_TEXTURECUBEMAP_H_

#include "Texture.h"

class TextureCubeMap: public Texture {
public:
	TextureCubeMap();
	~TextureCubeMap();
	TextureCubeMap(const TextureCubeMap &other) = delete;
	TextureCubeMap(TextureCubeMap &&other) = delete;
	TextureCubeMap& operator=(const TextureCubeMap &other) = delete;
	TextureCubeMap& operator=(TextureCubeMap &&other) = delete;
};

#endif /* GL_TEXTURE_TEXTURECUBEMAP_H_ */
