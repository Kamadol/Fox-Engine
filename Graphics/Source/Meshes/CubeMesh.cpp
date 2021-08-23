#include "CubeMesh.hpp"

CubeMesh::CubeMesh(Vector3 size)
	:m_size(size)
{
	size *= 0.5f;

	//front
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y,  size.z), Vector2(1.0f, 1.0f), Vector3( 0.0f,  0.0f,  1.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y,  size.z), Vector2(0.0f, 1.0f), Vector3( 0.0f,  0.0f,  1.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y,  size.z), Vector2(0.0f, 0.0f), Vector3( 0.0f,  0.0f,  1.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y,  size.z), Vector2(1.0f, 0.0f), Vector3( 0.0f,  0.0f,  1.0f)));

	//right																							 	 	   
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y, -size.z), Vector2(1.0f, 1.0f), Vector3( 1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y,  size.z), Vector2(0.0f, 1.0f), Vector3( 1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y,  size.z), Vector2(0.0f, 0.0f), Vector3( 1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y, -size.z), Vector2(1.0f, 0.0f), Vector3( 1.0f,  0.0f,  0.0f)));

	//back																							 	 
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y, -size.z), Vector2(1.0f, 1.0f), Vector3( 0.0f,  0.0f, -1.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y, -size.z), Vector2(0.0f, 1.0f), Vector3( 0.0f,  0.0f, -1.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y, -size.z), Vector2(0.0f, 0.0f), Vector3( 0.0f,  0.0f, -1.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y, -size.z), Vector2(1.0f, 0.0f), Vector3( 0.0f,  0.0f, -1.0f)));

	//left																							 	 
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y,  size.z), Vector2(1.0f, 1.0f), Vector3(-1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y, -size.z), Vector2(0.0f, 1.0f), Vector3(-1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y, -size.z), Vector2(0.0f, 0.0f), Vector3(-1.0f,  0.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y,  size.z), Vector2(1.0f, 0.0f), Vector3(-1.0f,  0.0f,  0.0f)));

	//top																							 	 	   
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y, -size.z), Vector2(1.0f, 1.0f), Vector3( 0.0f,  1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y, -size.z), Vector2(0.0f, 1.0f), Vector3( 0.0f,  1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x,  size.y,  size.z), Vector2(0.0f, 0.0f), Vector3( 0.0f,  1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x,  size.y,  size.z), Vector2(1.0f, 0.0f), Vector3( 0.0f,  1.0f,  0.0f)));

	//bottom																						 	 	   
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y,  size.z), Vector2(1.0f, 1.0f), Vector3( 0.0f, -1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y,  size.z), Vector2(0.0f, 1.0f), Vector3( 0.0f, -1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( -size.x, -size.y, -size.z), Vector2(0.0f, 0.0f), Vector3( 0.0f, -1.0f,  0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(  size.x, -size.y, -size.z), Vector2(1.0f, 0.0f), Vector3( 0.0f, -1.0f,  0.0f)));

	for (size_t i = 0; i < 6; i++)
	{
		m_indices.push_back(0 + i * 4);
		m_indices.push_back(1 + i * 4);
		m_indices.push_back(2 + i * 4);
		m_indices.push_back(0 + i * 4);
		m_indices.push_back(2 + i * 4);
		m_indices.push_back(3 + i * 4);
	}
}

void CubeMesh::setTextureCoord(CUBE_FACE face, Vector2 dl, Vector2 size)
{
	Vector2 dr = Vector2(dl.x + size.x, dl.y);
	Vector2 ur = Vector2(dl.x + size.x, dl.y + size.y);
	Vector2 ul = Vector2(dl.x         , dl.y + size.y);

	if (face == CUBE_FACE::FRONT)
	{
		m_vertices[0].texCoord = dl;
		m_vertices[1].texCoord = dr;
		m_vertices[2].texCoord = ur;
		m_vertices[3].texCoord = ul;
	}
	else if (face == CUBE_FACE::RIGHT)
	{
		m_vertices[4].texCoord = dl;
		m_vertices[5].texCoord = dr;
		m_vertices[6].texCoord = ur;
		m_vertices[7].texCoord = ul;
	}
	else if (face == CUBE_FACE::BACK)
	{
		m_vertices[8].texCoord = dl;
		m_vertices[9].texCoord = dr;
		m_vertices[10].texCoord = ur;
		m_vertices[11].texCoord = ul;
	}
	else if (face == CUBE_FACE::LEFT)
	{
		m_vertices[12].texCoord = dl;
		m_vertices[13].texCoord = dr;
		m_vertices[14].texCoord = ur;
		m_vertices[15].texCoord = ul;
	}
	else if (face == CUBE_FACE::TOP)
	{
		m_vertices[16].texCoord = dl;
		m_vertices[17].texCoord = dr;
		m_vertices[18].texCoord = ur;
		m_vertices[19].texCoord = ul;
	}
	else if (face == CUBE_FACE::BOTTOM)
	{
		m_vertices[20].texCoord = dl;
		m_vertices[21].texCoord = dr;
		m_vertices[22].texCoord = ur;
		m_vertices[23].texCoord = ul;
	}
}
