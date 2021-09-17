#ifndef SIMPLE_TEXT_RENDERER
#define SIMPLE_TEXT_RENDERER

#include "Shader.hpp"
#include "Text.hpp"

class SimpleTextRenderer
{
public:
	SimpleTextRenderer();
	~SimpleTextRenderer();

	void submit(const Text& text, Shader& shader, const Mat4x4& camera);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

};

#endif
