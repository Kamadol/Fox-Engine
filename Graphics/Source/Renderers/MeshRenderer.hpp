#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "Shader.hpp"
#include "Meshes/Mesh.hpp"

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void submit(const Mesh& mesh, Vector3* offsets, unsigned int count);
	void flush(const Shader& shader, const Mat4x4& camera);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_offsetVBO;
	unsigned int m_IBO;

	unsigned int m_indexCount;
	unsigned int m_count;
};

#endif
