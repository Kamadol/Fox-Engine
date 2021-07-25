#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Transformable.hpp"

struct SpriteVertex
{
	SpriteVertex(Vector3 position, Vector4 color)
		:position(position), color(color)
	{

	}

	Vector3 position;
	Vector4 color;
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
