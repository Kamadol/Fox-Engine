#include "Sprite.hpp"

#include <iostream>

Sprite::Sprite(Vector3 position, Vector2 size)
	:m_size(size)
{
	setPosition(position);
}
Sprite::Sprite()
{

}

Vector2 Sprite::getSize() const
{
	return m_size;
}
