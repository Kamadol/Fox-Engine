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
	size_t m_VAO;
	size_t m_VBO;
	size_t m_IBO;

};

#endif
