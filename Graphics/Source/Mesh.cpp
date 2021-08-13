#include "Mesh.hpp"

Mesh::Mesh()
{

}

void Mesh::addTexture(Texture* texture)
{
	m_textures.push_back(texture);
}
