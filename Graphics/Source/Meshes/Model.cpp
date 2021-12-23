#include "Model.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Model::Model(const char* filename)
{

}

void Model::draw(const Shader& shader) const
{
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].draw(shader);
	}
}
