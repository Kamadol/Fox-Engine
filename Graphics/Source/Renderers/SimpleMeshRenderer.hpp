#ifndef SIMPLE_MESH_RENDERER_HPP
#define SIMPLE_MESH_RENDERER_HPP

#include "Shader.hpp"
#include "Meshes/Mesh.hpp"

class SimpleMeshRenderer
{
public:
	SimpleMeshRenderer();
	~SimpleMeshRenderer();

	void submit(const Mesh& mesh, Shader& shader, const Mat4x4& camera);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

};

#endif
