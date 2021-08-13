#include "SimpleMeshRenderer.hpp"

#include "GL/glew.h"

SimpleMeshRenderer::SimpleMeshRenderer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * 128, 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * 128, 0, GL_DYNAMIC_DRAW);

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
	for (size_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		textures[i]->bind();
		shader.setUniform1i(("texture" + std::to_string(i)).c_str(), i);
	}

	glBindVertexArray(m_VAO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(MeshVertex) * mesh.getVertices().size(), &mesh.getVertices()[0]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(size_t) * mesh.getIndices().size(), &mesh.getIndices()[0]);
	glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
