#ifndef LINE_RENDERER_HPP
#define LINE_RENDERER_HPP

#include "Renderables/Line.hpp"

#include "Shader.hpp"
#include "Mat4x4.hpp"

class LineRenderer
{
public:
	LineRenderer();

	void draw(const Line& line, const Shader& shader, const Mat4x4& camera);

private:
	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_VBO;

};

#endif
