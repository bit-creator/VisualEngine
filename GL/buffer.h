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

#include "RowGraphicObject.h"

class Buffer: public RowGraphicObject <
	Creators::buffer,
	Deleters::buffer
> {
private:
	const uint32_t                           _type;

protected:
	Buffer(uint32_t type) noexcept;

public:
	~Buffer() noexcept;

    void bind() noexcept;
    void unbind() noexcept;
    
    template < typename Tp >
		void loadData(Tp data, uint32_t usage) {
    		loadRawData(std::data(data), std::size(data) * sizeof(typename Tp::value_type), usage);
    	}

	template <class T, unsigned int size>
    	void loadData(T (&data)[size], GLenum usage) {
			loadRawData(data, sizeof(data), usage);
		}

private:
	void loadRawData(void* data, size_t size, uint32_t usage) noexcept;
}; // Buffer

struct VertexBuffer: public Buffer {
	VertexBuffer();
};

struct IndexBuffer: public Buffer {
	IndexBuffer();
};

#endif // BUFFER_H
