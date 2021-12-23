#ifndef SPRITE_VERTEX_HPP
#define SPRITE_VERTEX_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

struct SpriteVertex
{
	SpriteVertex(Vector3 position, Vector4 color, Vector2 texCoord);
	SpriteVertex();

	Vector3 position;
	Vector4 color;
	Vector2 texCoord;
};

#endif
