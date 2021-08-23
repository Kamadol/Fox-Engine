#include "PlaneMesh.hpp"

PlaneMesh::PlaneMesh()
{
	m_vertices.push_back(MeshVertex(Vector3( 0.5f, 0.0f,  0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(-0.5f, 0.0f,  0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)));
	m_vertices.push_back(MeshVertex(Vector3(-0.5f, 0.0f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)));
	m_vertices.push_back(MeshVertex(Vector3( 0.5f, 0.0f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)));

	m_indices.push_back(1);
	m_indices.push_back(0);
	m_indices.push_back(2);

	m_indices.push_back(3);
	m_indices.push_back(2);
	m_indices.push_back(0);
}
