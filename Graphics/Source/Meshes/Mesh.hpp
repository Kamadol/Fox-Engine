#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Transformable.hpp"
#include "Texture.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Shader.hpp"

struct MeshVertex
{
	MeshVertex(Vector3 position, Vector2 texCoord, Vector3 normal)
		:position(position), texCoord(texCoord), normal(normal)
	{

	}
	MeshVertex()
		:position(Vector3::zero()), texCoord(Vector2::zero()), normal(Vector3::zero())
	{

	}

	Vector3 position;
	Vector2 texCoord;
	Vector3 normal;
};
class Mesh : public Transformable
{
public:
	Mesh(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures);
	Mesh();
	~Mesh();

	void setup();

	void load(const char* filename);
	void draw(const Shader& shader) const;

	void addTexture(Texture* texture);
	size_t getVertexCount() { return m_vertices.size(); }

	const std::vector<MeshVertex>&   getVertices() const { return m_vertices; }
	const std::vector<unsigned int>& getIndices()  const { return m_indices; }
	const std::vector<Texture*>&	 getTextures() const { return m_textures; }

protected:
	std::vector<MeshVertex>   m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture*>     m_textures;

protected:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

};

#endif
