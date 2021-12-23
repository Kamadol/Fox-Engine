#include "LineRenderer.hpp"

#include "GL/glew.h"

#include "Vertices/SpriteVertex.hpp"

#include <iostream>

LineRenderer::LineRenderer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex) * 4000, 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6000, 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, texCoord));

	glBindVertexArray(0);
}

void LineRenderer::draw(const Line& line, const Shader& shader, const Mat4x4& camera)
{
	//TODO: fill gaps between lines

	const std::vector<Vector3>& points = line.m_points;
	const Vector4& color = line.m_color;
	unsigned int verticesCount = (points.size() - 1) * 4;
	unsigned int indicesCount = (points.size() - 1) * 6;
	
	glBindVertexArray(m_VAO);

	std::vector<SpriteVertex> vertices;
	vertices.reserve(verticesCount);

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		Vector2 dist = Vector2(points[i + 1].x - points[i].x, points[i + 1].y - points[i].y);

		Vector2 p1 = Vector2(points[i].x, points[i].y) + Vector2(-dist.y,  dist.x).unit() * line.m_thickness;
		Vector2 p2 = Vector2(points[i].x, points[i].y) + Vector2( dist.y, -dist.x).unit() * line.m_thickness;
		Vector2 p3 = p1 + dist;
		Vector2 p4 = p2 + dist;

		vertices.push_back(SpriteVertex(Vector3(p1.x, p1.y, points[i].z), color, Vector2(0.0, 0.0)));
		vertices.push_back(SpriteVertex(Vector3(p2.x, p2.y, points[i].z), color, Vector2(0.0, 0.0)));
		vertices.push_back(SpriteVertex(Vector3(p3.x, p3.y, points[i].z), color, Vector2(0.0, 0.0)));
		vertices.push_back(SpriteVertex(Vector3(p4.x, p4.y, points[i].z), color, Vector2(0.0, 0.0)));
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SpriteVertex) * verticesCount, &vertices[0]);

	unsigned int* indices = new unsigned int[indicesCount];
	for (size_t i = 0; i < indicesCount / 6; i++)
	{
		indices[i * 6	 ] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 1;
		indices[i * 6 + 5] = i * 4 + 3;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indicesCount, indices);

	shader.bind();
	shader.setUniformMat4("u_MVP", camera * line.getTransform());
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
