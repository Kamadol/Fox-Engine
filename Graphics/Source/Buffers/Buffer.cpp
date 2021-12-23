#include "Buffer.hpp"

#include "GL/glew.h"

Buffer::Buffer(size_t elementSize, size_t count, const void* data, bool staticDraw)
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(1, m_VBO);
	glBufferData(GL_VERTEX_ARRAY, elementSize * count, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_VBO);
}
Buffer::Buffer(Buffer&& other) noexcept
	:m_VBO(other.m_VBO)
{
	other.m_VBO = 0;
}

void Buffer::putData(size_t offset, size_t size, const void* data)
{
	glBufferSubData(GL_VERTEX_ARRAY, offset, size, data);
}

void Buffer::bind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, m_VBO);
}
void Buffer::unbind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}
