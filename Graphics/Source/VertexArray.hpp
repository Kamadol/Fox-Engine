#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexLayout.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();	

	void bind() const;
	void unbind() const;
	void useLayout(const VertexLayout &layout);

private:
	size_t m_id;

};

#endif
