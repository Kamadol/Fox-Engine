#include "Mesh.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Mesh::Mesh()
{

}

void Mesh::load(const char* filename)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];
    m_vertices.reserve(mesh->mNumVertices);

    std::cout << mesh->mNumVertices << " vertices" << std::endl;

    Vector3 firstVertexPos;
    firstVertexPos.x = mesh->mVertices[0].x;
    firstVertexPos.y = mesh->mVertices[0].y;
    firstVertexPos.z = mesh->mVertices[0].z;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        MeshVertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;
        vertex.position -= firstVertexPos;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0])
        {
            vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
        }

        m_vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            m_indices.push_back(face.mIndices[j]);
    }
}

void Mesh::addTexture(Texture* texture)
{
	m_textures.push_back(texture);
}
