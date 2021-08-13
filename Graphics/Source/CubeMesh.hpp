#ifndef CUBE_MESH_HPP
#define CUBE_MESH_HPP

#include "Mesh.hpp"

enum class CUBE_FACE
{
	FRONT = 0,
	RIGHT = 1,
	BACK = 2,
	LEFT = 3,
	TOP = 4, 
	BOTTOM = 5
};
class CubeMesh : public Mesh
{
public:
	CubeMesh(Vector3 size);

	void setTextureCoord(CUBE_FACE face, Vector2 dl, Vector2 size);

private:
	Vector3 m_size;

};

#endif
