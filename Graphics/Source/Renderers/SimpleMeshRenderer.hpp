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
	size_t m_VAO;
	size_t m_VBO;
	size_t m_IBO;

};

#endif
