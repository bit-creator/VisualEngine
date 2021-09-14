/*
 * Deleters.h
 *
 *  Created on: 14 вер. 2021 р.
 *      Author: IAbernikhin
 */

#ifndef GL_DELETERS_H_
#define GL_DELETERS_H_

#include <inttypes.h>

namespace GL::Deleters {
	void shaderPrg		(uint32_t* obj);
	void renderBuff		(uint32_t* obj);
	void frameBuff		(uint32_t* obj);
	void buffer			(uint32_t* obj);
	void texture		(uint32_t* obj);
	void vertexArray	(uint32_t* obj);
	void shader			(uint32_t* obj);
} /* namespace Deleters */

#endif /* GL_DELETERS_H_ */
