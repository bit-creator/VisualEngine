/*
 * Texture2D.h
 *
 *  Created on: Dec 10, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE_TEXTURE2D_H_
#define GL_TEXTURE_TEXTURE2D_H_

#include "Texture.h"

class Texture2D : public Texture {
public:
	Texture2D();
	~Texture2D();
	Texture2D(const Texture2D &other) = delete;
	Texture2D(Texture2D &&other) = delete;
	Texture2D& operator=(const Texture2D &other) = delete;
	Texture2D& operator=(Texture2D &&other) = delete;
};

#endif /* GL_TEXTURE_TEXTURE2D_H_ */
