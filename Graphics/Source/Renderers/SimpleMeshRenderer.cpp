#include "SimpleMeshRenderer.hpp"

#include "GL/glew.h"

#define MAX_VERTEX_COUNT 250000

SimpleMeshRenderer::SimpleMeshRenderer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * MAX_VERTEX_COUNT, 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_VERTEX_COUNT, 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, texCoord));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, normal));

	glBindVertexArray(0);
}
SimpleMeshRenderer::~SimpleMeshRenderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void SimpleMeshRenderer::submit(const Mesh& mesh, Shader& shader, const Mat4x4& camera)
{
	shader.bind();
	shader.setUniformMat4("u_MVP", camera * mesh.getTransform());
	shader.setUniformMat4("u_model", mesh.getTransform());

	const std::vector<Texture*>& textures = mesh.getTextures();
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		textures[i]->bind();
		shader.setUniform1i(("texture" + std::to_string(i)).c_str(), i);
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(MeshVertex) * mesh.getVertices().size(), &mesh.getVertices()[0]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * mesh.getIndices().size(), &mesh.getIndices()[0]);
	glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
