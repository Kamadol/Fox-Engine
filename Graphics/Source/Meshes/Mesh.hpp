#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Transformable.hpp"
#include "Texture.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

struct MeshVertex
{
	MeshVertex(Vector3 position, Vector2 texCoord, Vector3 normal)
		:position(position), texCoord(texCoord), normal(normal)
	{

	}

	Vector3 position;
	Vector2 texCoord;
	Vector3 normal;
};
class Mesh : public Transformable
{
public:
	Mesh();

	void addTexture(Texture* texture);

	size_t getVertexCount() { return m_vertices.size(); }

	const std::vector<MeshVertex>& getVertices() const { return m_vertices; }
	const std::vector<size_t>& getIndices() const { return m_indices; }
	const std::vector<Texture*>& getTextures() const { return m_textures; }

protected:
	std::vector<MeshVertex> m_vertices;
	std::vector<size_t>     m_indices;
	std::vector<Texture*>   m_textures;

};

#endif
