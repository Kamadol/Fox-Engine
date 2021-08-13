#include "SimpleSpriteRenderer.hpp"

#include "GL/glew.h"

SimpleSpriteRenderer::SimpleSpriteRenderer()
{
	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 0;
	m_indices[4] = 2;
	m_indices[5] = 3;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex) * 4, 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * 6, m_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, texCoord));

	glBindVertexArray(0);
}
SimpleSpriteRenderer::~SimpleSpriteRenderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void SimpleSpriteRenderer::submit(const Sprite& sprite, Shader& shader, const Mat4x4& camera)
{
	shader.bind();
	shader.setUniformMat4("u_MVP", camera * sprite.getTransform());

	Vector3 position = sprite.getPosition();
	Vector2 size = sprite.getSize() * 0.5f;

	SpriteVertex quad[4] =
	{
		SpriteVertex(Vector3( size.x,  size.y, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
		SpriteVertex(Vector3(-size.x,  size.y, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)),
		SpriteVertex(Vector3(-size.x, -size.y, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f)),
		SpriteVertex(Vector3( size.x, -size.y, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f))
	};

	glBindVertexArray(m_VAO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SpriteVertex) * 4, quad);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
