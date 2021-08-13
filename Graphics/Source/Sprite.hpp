#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Transformable.hpp"

struct SpriteVertex
{
	SpriteVertex(Vector3 position, Vector4 color, Vector2 texCoord)
		:position(position), color(color), texCoord(texCoord)
	{

	}

	Vector3 position;
	Vector4 color;
	Vector2 texCoord;
};
class Sprite : public Transformable
{
public:
	Sprite(Vector3 position, Vector2 size);
	Sprite();

	Vector2 getSize() const;

private:
	Vector2 m_size;

};

#endif
