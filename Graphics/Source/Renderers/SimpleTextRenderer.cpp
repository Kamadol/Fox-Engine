#include "SimpleTextRenderer.hpp"

#include "GL/glew.h"

#define MAX_GLYPHS 256

SimpleTextRenderer::SimpleTextRenderer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertex) * 4 * MAX_GLYPHS, 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	size_t indices[6 * MAX_GLYPHS];
	for (size_t i = 0; i < MAX_GLYPHS; i++)
	{
		indices[0 + i * 6] = 0 + i * 4;
		indices[1 + i * 6] = 1 + i * 4;
		indices[2 + i * 6] = 2 + i * 4;
		indices[3 + i * 6] = 0 + i * 4;
		indices[4 + i * 6] = 2 + i * 4;
		indices[5 + i * 6] = 3 + i * 4;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * 6 * MAX_GLYPHS, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, texCoord));

	glBindVertexArray(0);
}
SimpleTextRenderer::~SimpleTextRenderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void SimpleTextRenderer::submit(const Text& text, Shader& shader, const Mat4x4& camera)
{
	shader.bind();
	shader.setUniformMat4("u_MVP", camera * text.getTransform());

	glActiveTexture(GL_TEXTURE0);
	text.getFont()->bind();
	shader.setUniform1i("texture0", 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindVertexArray(m_VAO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(TextVertex) * text.getVertices().size() * 4, &text.getVertices()[0]);
	glDrawElements(GL_TRIANGLES, text.getVertices().size() / 4 * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
