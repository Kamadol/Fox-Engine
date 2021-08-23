#include "CylinderMesh.hpp"

CylinderMesh::CylinderMesh(size_t sideQuads, float height, float radius)
{
	m_vertices.push_back(MeshVertex(Vector3(0.0f, -height * 0.5f, 0.0f), Vector2(), Vector3(0.0f, -1.0f, 0.0f)));

	float angleStep = 2.0f * 3.1415926535f / (float)sideQuads;
	float currentAngle = 0.0f;
	for (size_t i = 0; i < sideQuads; i++)
	{
		Vector3 position = Vector3(radius * cosf(currentAngle), -height * 0.5f, radius * sinf(currentAngle));
		m_vertices.push_back(MeshVertex(position, Vector2(0.0f, 0.0f), position.unit()));
		m_vertices.push_back(MeshVertex(Vector3(position.x, -position.y, position.z), Vector2(0.0f, 0.0f), Vector3(position.x, -position.y, position.z).unit()));

		currentAngle += angleStep;
	}

	m_vertices.push_back(MeshVertex(Vector3(0.0f, height * 0.5f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)));

	//m_indices.push_back(0);
	//m_indices.push_back(1);
	//m_indices.push_back(3);

	//m_indices.push_back(0);
	//m_indices.push_back(3);
	//m_indices.push_back(5);

	//bottom
	for (size_t i = 0; i < sideQuads - 1; i++)
	{
		m_indices.push_back(0);
		m_indices.push_back(i * 2 + 1);
		m_indices.push_back(i * 2 + 3);
	}
	m_indices.push_back(0);
	m_indices.push_back(sideQuads * 2 - 1);
	m_indices.push_back(1);

	//middle
	for (size_t i = 0; i < sideQuads - 1; i++)
	{
		m_indices.push_back(i * 2 + 1);
		m_indices.push_back(i * 2 + 4);
		m_indices.push_back(i * 2 + 3);

		m_indices.push_back(i * 2 + 1);
		m_indices.push_back(i * 2 + 2);
		m_indices.push_back(i * 2 + 4);
	}
	m_indices.push_back(1);
	m_indices.push_back(sideQuads * 2);
	m_indices.push_back(2);

	m_indices.push_back(1);
	m_indices.push_back(sideQuads * 2 - 1);
	m_indices.push_back(sideQuads * 2);

	//top 
	for (size_t i = 0; i < sideQuads - 1; i++)
	{
		m_indices.push_back(m_vertices.size() - 1);
		m_indices.push_back(i * 2 + 4);
		m_indices.push_back(i * 2 + 2);
	}
	m_indices.push_back(m_vertices.size() - 1);
	m_indices.push_back(2);
	m_indices.push_back(sideQuads * 2);
}
