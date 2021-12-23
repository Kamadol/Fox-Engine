#include "SpriteVertex.hpp"

SpriteVertex::SpriteVertex(Vector3 position, Vector4 color, Vector2 texCoord)
	:position(position), color(color), texCoord(texCoord)
{

}
SpriteVertex::SpriteVertex()
	:position(Vector3::zero()), color(Vector4(0.0f, 0.0f, 0.0f, 1.0f)), texCoord(Vector2::zero())
{

}