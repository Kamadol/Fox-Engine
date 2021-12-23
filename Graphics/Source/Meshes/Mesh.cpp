#include "Mesh.hpp"

#include "GL/glew.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Mesh::Mesh(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures)
    :m_vertices(vertices), m_indices(indices), m_textures(textures)
{
    setup();
}
Mesh::Mesh()
    :m_VAO(0), m_VBO(0), m_IBO(0)
{
    
}
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

void Mesh::setup()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, texCoord));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (const void*)offsetof(MeshVertex, normal));

    glBindVertexArray(0);
}

void Mesh::load(const char* filename)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Assimp error:" << import.GetErrorString() << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];
    m_vertices.reserve(mesh->mNumVertices);

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

void Mesh::draw(const Shader& shader) const
{
    shader.bind();
    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        m_textures[i]->bind();
        shader.setUniform1i(("texture" + std::to_string(i)).c_str(), i);
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
