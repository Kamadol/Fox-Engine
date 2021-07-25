#include "VertexArray.hpp"

#include "GL/glew.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
}
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
void VertexArray::useLayout(const VertexLayout& layout)
{
	size_t offset = 0;
	std::vector<VertexLayoutElement> el = layout.getElements();
	for (size_t i = 0; i < el.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, el[i].count, el[i].type, GL_FALSE, layout.getStride(), (const void*)offset);
		offset += el[i].getSize();
	}
}
