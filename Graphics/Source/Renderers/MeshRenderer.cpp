#include "MeshRenderer.hpp"

#include <iostream>

#include "GL/glew.h"

#define MAX_VERTEX_COUNT 500000

MeshRenderer::MeshRenderer()
	:m_indexCount(0), m_count(0)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * MAX_VERTEX_COUNT, 0, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_VERTEX_COUNT, 0, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, texCoord));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, normal));


	glGenBuffers(1, &m_offsetVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_offsetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * MAX_VERTEX_COUNT, 0, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (const void*)0);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}
MeshRenderer::~MeshRenderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteBuffers(1, &m_offsetVBO);
}

void MeshRenderer::submit(const Mesh& mesh, Vector3* offsets, unsigned int count)
{
	m_indexCount = mesh.getIndices().size();
	m_count = count;

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(MeshVertex) * mesh.getVertices().size(), &mesh.getVertices()[0]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * m_indexCount, &mesh.getIndices()[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_offsetVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector3) * count, offsets);

	glBindVertexArray(0);
}
void MeshRenderer::flush(const Shader& shader, const Mat4x4& camera)
{
	shader.bind();
	shader.setUniformMat4("u_camera", camera);
	
	glBindVertexArray(m_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0, m_count);
	glBindVertexArray(0);
}
