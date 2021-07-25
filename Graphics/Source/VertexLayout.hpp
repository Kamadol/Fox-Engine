#ifndef VERTEX_LAYOUT_HPP
#define VERTEX_LAYOUT_HPP

#include <vector>

#include "GL/glew.h"

struct VertexLayoutElement
{
	VertexLayoutElement(size_t type, size_t count)
		:type(type), count(count)
	{

	}

	inline size_t getSize()
	{
		return getSizeOfType(type) * count;
	}

	static size_t getSizeOfType(size_t type)
	{
		if (type == GL_FLOAT)
			return sizeof(GLfloat);
		else if (type == GL_UNSIGNED_INT)
			return sizeof(GLuint);
	}

	size_t count;
	size_t type;
	
};

class VertexLayout
{
public:
	inline size_t getStride() const { return m_stride; }
	inline const std::vector<VertexLayoutElement>& getElements() const { return m_elements; }

	template<typename T>
	void push(size_t count);

	template<>
	void push<float>(size_t count)
	{
		m_elements.push_back(VertexLayoutElement(GL_FLOAT, count));
		m_stride += sizeof(GLfloat) * count;
	}

	template<>
	void push<size_t>(size_t count)
	{
		m_elements.push_back(VertexLayoutElement(GL_UNSIGNED_INT, count));
		m_stride += sizeof(GLuint) * count;
	}

private:
	std::vector<VertexLayoutElement> m_elements;
	size_t m_stride;

};

#endif
