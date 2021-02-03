/**
 * @file buffer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "globject.hpp"

class Buffer : public GLObject {
private:
	const GLuint                           _type;

public:
	Buffer(GLuint type) noexcept;
    ~Buffer() noexcept;

    void bind() noexcept;
    void unbind() noexcept;
    
    template < typename Tp >
		void loadData(Tp data, GLenum usage) {
    		loadRawData(std::data(data), std::size(data) * sizeof(typename Tp::value_type), usage);
    	}

	template <class T, unsigned int size>
    	void loadData(T (&data)[size], GLenum usage) {
			loadRawData(data, sizeof(data), usage);
		}

private:
	void loadRawData(GLvoid* data, size_t size, GLenum usage) noexcept;
    GLuint genBuff();
}; // Buffer

#endif // BUFFER_H
