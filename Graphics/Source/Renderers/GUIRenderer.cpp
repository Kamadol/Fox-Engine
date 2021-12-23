#include "GUIRenderer.hpp"

#include "GL/glew.h"

#include "Vertices/SpriteVertex.hpp"

#include <iostream>

GUIRenderer::GUIRenderer()
	:m_bodyTex(nullptr), m_cornerTex(nullptr), m_edgeTex(nullptr)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex) * 16, 0, GL_DYNAMIC_DRAW);

	unsigned int* indices = new unsigned int[6 * 4];
	for (size_t i = 0; i < 4; i++)
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6 * 4, indices, GL_STATIC_DRAW);
	delete[] indices;	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, texCoord));

	glBindVertexArray(0);
}

void GUIRenderer::setTextures(Texture* bodyTexture, Texture* cornerTexture, Texture* edgeTexture)
{
	m_bodyTex = bodyTexture;
	m_cornerTex = cornerTexture;
	m_edgeTex = edgeTexture;
}

void GUIRenderer::createBody(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr)
{
	Vec2f quadCount = Vec2f((float)(size.x / margin.x), (float)(size.y / margin.y));

	ptr[0] = SpriteVertex(Vector3(pos.x + size.x,	pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, quadCount.y));
	ptr[1] = SpriteVertex(Vector3(pos.x + margin.x,	pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, quadCount.y));
	ptr[2] = SpriteVertex(Vector3(pos.x + margin.x,	pos.y - size.y,   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[3] = SpriteVertex(Vector3(pos.x + size.x,	pos.y - size.y,   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, 0.0f));
}
void GUIRenderer::createCorners(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr)
{
	ptr[0 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y,			   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	ptr[1 ] = SpriteVertex(Vector3(pos.x,			 pos.y,			   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	ptr[2 ] = SpriteVertex(Vector3(pos.x,			 pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[3 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));

	ptr[4 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - size.y,			0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[5 ] = SpriteVertex(Vector3(pos.x,			 pos.y - size.y,			0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	ptr[6 ] = SpriteVertex(Vector3(pos.x,			 pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	ptr[7 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));

	ptr[8 ] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y - size.y,			 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[9 ] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y - size.y,			 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[10] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
	ptr[11] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));

	ptr[12] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y,			0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
	ptr[13] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y,			0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[14] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[15] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
}
void GUIRenderer::createEdges(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr)
{
	Vec2f quadCount = Vec2f((float)(size.x / margin.x), (float)(size.y / margin.y));

	ptr[0 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y,			  0.0f),  Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[1 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[2 ] = SpriteVertex(Vector3(pos.x + size.x,	 pos.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, 0.0f));
	ptr[3 ] = SpriteVertex(Vector3(pos.x + size.x,   pos.y,			  0.0f),  Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, 1.0f));
		  
	ptr[4 ] = SpriteVertex(Vector3(pos.x,		     pos.y - margin.y, 0.0f),	 Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.y, 1.0f));
	ptr[5 ] = SpriteVertex(Vector3(pos.x,			 pos.y - size.y,	  0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[6 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - size.y,	  0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[7 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - margin.y, 0.0f),	 Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.y, 0.0f));

	ptr[8 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - size.y,		    0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, 0.0f));
	ptr[9 ] = SpriteVertex(Vector3(pos.x + margin.x, pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.x, 1.0f));
	ptr[10] = SpriteVertex(Vector3(pos.x + size.x,   pos.y - size.y - margin.y, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[11] = SpriteVertex(Vector3(pos.x + size.x,   pos.y - size.y,		    0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));

	ptr[12] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y - margin.y,	0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
	ptr[13] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y - margin.y,	0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
	ptr[14] = SpriteVertex(Vector3(pos.x + size.x,			  pos.y - size.y,   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.y, 0.0f));
	ptr[15] = SpriteVertex(Vector3(pos.x + size.x + margin.x, pos.y - size.y,   0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector2(quadCount.y, 1.0f));
}

void GUIRenderer::draw(const GUIRectangle& rectangle, const Shader& shader, const OrthographicCamera& camera)
{
	Vec2i pos = rectangle.getWorldPosition();
	pos = Vec2i(pos.x, -pos.y + camera.getTop());
	Vec2i margin = rectangle.getMargin();
	Vec2i size = rectangle.getSize() - margin;

	shader.bind();
	shader.setUniformMat4("u_MVP", camera.getMatrix());

	glBindVertexArray(m_VAO);

	SpriteVertex data[16];
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glActiveTexture(GL_TEXTURE0);
	shader.setUniform1i("texture0", 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_bodyTex->bind();
	createBody(pos - Vec2i(1, -1), size + Vec2i(2, 2), margin, data); //Artificial fitting
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SpriteVertex) * 4, data);
	glDrawElements(GL_TRIANGLES, 1 * 6, GL_UNSIGNED_INT, 0);

	m_cornerTex->bind();
	createCorners(pos, size, margin, data);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SpriteVertex) * 16, data);
	glDrawElements(GL_TRIANGLES, 4 * 6, GL_UNSIGNED_INT, 0);

	m_edgeTex->bind();
	createEdges(pos, size, margin, data);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SpriteVertex) * 16, data);
	glDrawElements(GL_TRIANGLES, 4 * 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glDisable(GL_BLEND);
}
