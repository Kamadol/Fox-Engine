#include "IndexBuffer.hpp"

#include "GL/glew.h"

IndexBuffer::IndexBuffer(const void* data, size_t count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
