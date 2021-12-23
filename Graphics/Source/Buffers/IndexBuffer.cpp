#include "IndexBuffer.hpp"

#include "GL/glew.h"

IndexBuffer::IndexBuffer(size_t count, const void* data, bool staticDraw)
	:m_count(count)
{
	glGenBuffers(1, &m_IBO);
	glBindBuffer(1, m_IBO);
	glBufferData(GL_VERTEX_ARRAY, sizeof(unsigned int) * count, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_IBO);
}
IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	:m_IBO(other.m_IBO), m_count(other.m_count)
{
	other.m_IBO = 0;
	other.m_count = 0;
}

unsigned int IndexBuffer::getCount() const
{
	return m_count;
}
void IndexBuffer::putData(size_t offset, size_t count, const void* data)
{
	glBufferSubData(GL_VERTEX_ARRAY, offset, sizeof(unsigned int) * count, data);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, m_IBO);
}
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}
