#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2.hpp"

class Sprite
{
public:
	Sprite(Vector2 position, Vector2 size);
	Sprite();

private:
	Vector2 m_position;
	Vector2 m_size;

};

#endif
