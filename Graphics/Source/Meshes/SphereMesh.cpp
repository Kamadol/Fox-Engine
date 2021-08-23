#include "SphereMesh.hpp"

#include <iostream>

SphereMesh::SphereMesh(size_t xRings, size_t yRings, float radius)
	:m_radius(radius)
{
	//vertices
	m_vertices.push_back(MeshVertex(Vector3(0.0f, -radius, 0.0f), Vector2(0.5f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)));

	float yAngleStep = 2.0f * 3.1415926535f / (float)(yRings * 2 - 2);
	float xAngleStep = 2.0f * 3.1415926535f / (float)(xRings);

	float yCurrentAngle = yAngleStep;
	float xCurrentAngle = 0.0f;

	for (size_t i = 0; i < yRings - 2; i++)
	{
		float height = -radius * cosf(yCurrentAngle);
		float xTmpRadius = radius * sinf(yCurrentAngle);
		yCurrentAngle += yAngleStep;

		for (size_t j = 0; j < xRings; j++)
		{
			float xPos = xTmpRadius * cosf(xCurrentAngle);
			float zPos = xTmpRadius * sinf(xCurrentAngle);
			xCurrentAngle += xAngleStep;

			Vector3 vertexPosition(xPos, height, zPos);
			Vector3 normal = vertexPosition.unit();
			Vector2 textureCoord(asinf(normal.x) / 3.1415986535f + 0.5f, asinf(normal.y) / 3.1415986535f + 0.5f);

			m_vertices.push_back(MeshVertex(vertexPosition, textureCoord, normal));
		}

		xCurrentAngle = 0.0f;
	}

	m_vertices.push_back(MeshVertex(Vector3(0.0f, radius, 0.0f), Vector2(0.5f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)));

	//indices
	//bottom
	for (size_t i = 0; i < xRings; i++)
	{
		m_indices.push_back(0);
		m_indices.push_back(i + 1);
		m_indices.push_back((i + 1) % xRings + 1);
	}

	//middle
	for (size_t i = 0; i < yRings - 3; i++)
	{
		size_t yStartIndex = i * xRings;

		for (size_t j = 0; j < xRings - 1; j++)
		{
			m_indices.push_back(yStartIndex + (j + 2));
			m_indices.push_back(yStartIndex + (j + 1));
			m_indices.push_back(yStartIndex + (j + 2) + xRings);
													
			m_indices.push_back(yStartIndex + (j + 2) + xRings);
			m_indices.push_back(yStartIndex + (j + 1));
			m_indices.push_back(yStartIndex + (j + 1) + xRings);
		}

		m_indices.push_back(yStartIndex + xRings + 1);
		m_indices.push_back(yStartIndex + 1);
		m_indices.push_back(yStartIndex + 2 * xRings);

		m_indices.push_back(yStartIndex + 1);
		m_indices.push_back(yStartIndex + xRings);
		m_indices.push_back(yStartIndex + 2 * xRings);
	}

	//top
	size_t lastVertexIndex = getVertexCount() - 1;
	for (size_t i = 0; i < xRings - 1; i++)
	{
		m_indices.push_back(lastVertexIndex);
		m_indices.push_back(lastVertexIndex - i - 1);
		m_indices.push_back((lastVertexIndex - i - 2));
	}
	m_indices.push_back(lastVertexIndex - 1);
	m_indices.push_back(lastVertexIndex);
	m_indices.push_back((lastVertexIndex - xRings));
}
