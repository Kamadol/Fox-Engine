#include "SpriteRenderer.hpp"

#include "GL/glew.h"

#include "Utility/Constants.hpp"

SpriteRenderer::SpriteRenderer()
	:m_bufferPtr(nullptr), m_idCount(0)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, spritesSize, 0, GL_DYNAMIC_DRAW);

	unsigned int* indices = new unsigned int[spriteIndicesCount];
	for (size_t i = 0; i < maxSprites; i++)
	{
		indices[i * 6	 ] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 0;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	}
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, spriteIndicesSize, indices, GL_STATIC_DRAW);
	delete[] indices;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, texCoord));

	glBindVertexArray(0);
}
SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void SpriteRenderer::start()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_bufferPtr = (SpriteVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	m_idCount = 0;
}
void SpriteRenderer::submit(const Sprite& sprite)
{
	Vector2 size = sprite.getSize();
	Vector4 color = sprite.getColor();
	const Vector2* texCoords = sprite.getTextureCoords();
	Mat4x4 transform = sprite.getTransform();

	m_bufferPtr->position = transform * Vector3(size.x, size.y, 0.0f);
	m_bufferPtr->color = color;
	m_bufferPtr->texCoord = texCoords[0];
	m_bufferPtr++;

	m_bufferPtr->position = transform * Vector3(0.0f, size.y, 0.0f);
	m_bufferPtr->color = color;
	m_bufferPtr->texCoord = texCoords[1];
	m_bufferPtr++;

	m_bufferPtr->position = transform * Vector3(0.0f, 0.0f, 0.0f);
	m_bufferPtr->color = color;
	m_bufferPtr->texCoord = texCoords[2];
	m_bufferPtr++;

	m_bufferPtr->position = transform * Vector3(size.x, 0.0f, 0.0f);
	m_bufferPtr->color = color;
	m_bufferPtr->texCoord = texCoords[3];
	m_bufferPtr++;

	m_idCount += 6;
}
void SpriteRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void SpriteRenderer::flush()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_idCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
