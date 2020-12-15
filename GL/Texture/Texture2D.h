/*
 * Texture2D.h
 *
 *  Created on: Dec 10, 2020
 *      Author: bit_creator
 */

#ifndef GL_TEXTURE2D_H_
#define GL_TEXTURE2D_H_

#include "globject.hpp"

class Texture2D : public GLObject {
public:
	Texture2D();
	~Texture2D();
	Texture2D(const Texture2D &other) = delete;
	Texture2D(Texture2D &&other) = delete;
	Texture2D& operator=(const Texture2D &other) = delete;
	Texture2D& operator=(Texture2D &&other) = delete;

	void bind(int unit);
	loadImage(const char* name);

private:
	GLuint gentex() noexcept;
};

#endif /* GL_TEXTURE2D_H_ */
