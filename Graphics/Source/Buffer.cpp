#include "Buffer.hpp"

#include "GL/glew.h"

Buffer::Buffer(const void* data, size_t size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
void Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
