/*
 * Texture2D.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: bit_creator
 */

#include "Texture2D.h"

Texture2D::Texture2D() {
}

Texture2D::~Texture2D() {
}

GLuint Texture2D::gentex()
{
    GLuint ID;
    glGenTextures(1, &ID);
    return ID;
}
