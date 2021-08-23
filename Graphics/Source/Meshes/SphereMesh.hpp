#ifndef SPHERE_MESH
#define SPHERE_MESH

#include "Mesh.hpp"

class SphereMesh : public Mesh
{
public:
	SphereMesh(size_t xRings, size_t yRings, float radius);

private:
	float m_radius;

};

#endif
