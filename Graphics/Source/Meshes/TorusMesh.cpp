#include "TorusMesh.hpp"

TorusMesh::TorusMesh(size_t rings, size_t vPerRing, float radius, float ringRadius)
{
	float betweenRingsAngle = 2.0f * 3.1415926535f / (float)rings;
	float ringStepAngle = 2.0f * 3.1415926535f / (float)vPerRing;

	float currentBetweenRingsAngle = 0.0f;

	for (size_t i = 0; i < rings; i++)
	{
		Vector3 ringCenterPosition;
		ringCenterPosition.x =  radius * cosf(currentBetweenRingsAngle);
		ringCenterPosition.y =  0.0f;
		ringCenterPosition.z = -radius * sinf(currentBetweenRingsAngle);

		float currentRingAngle = 0.0f;
		for (size_t j = 0; j < vPerRing; j++)
		{
			Vector3 vertexPosition;
			vertexPosition.x =  ringRadius * cosf(currentRingAngle) * cosf(currentBetweenRingsAngle) + radius * cosf(currentBetweenRingsAngle);
			vertexPosition.y =  ringRadius * sinf(currentRingAngle);
			vertexPosition.z = -ringRadius * cosf(currentRingAngle) * sinf(currentBetweenRingsAngle) - radius * sinf(currentBetweenRingsAngle);

			m_vertices.push_back(MeshVertex(vertexPosition, Vector2(0.0f, 0.0f), (vertexPosition - ringCenterPosition).unit()));

			currentRingAngle += ringStepAngle;
		}

		currentBetweenRingsAngle += betweenRingsAngle;
	}

	for (unsigned int i = 0; i < rings; i++)
	{
		unsigned int currentStartIndex = i * vPerRing;

		for (size_t j = 0; j < vPerRing; j++)
		{
			m_indices.push_back((currentStartIndex +  j                                                ));
			m_indices.push_back((currentStartIndex +  j                 + vPerRing) % (rings * vPerRing));
			m_indices.push_back((currentStartIndex + (j + 1) % vPerRing                                ));
																				  
			m_indices.push_back((currentStartIndex + (j + 1) % vPerRing                                ));
			m_indices.push_back((currentStartIndex +  j                 + vPerRing) % (rings * vPerRing));
			m_indices.push_back((currentStartIndex + (j + 1) % vPerRing + vPerRing) % (rings * vPerRing));
		}
	}
}
