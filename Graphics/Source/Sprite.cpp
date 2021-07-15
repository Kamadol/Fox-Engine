#include "Sprite.hpp"

#include <iostream>

Sprite::Sprite()
{
	std::cout << Vector2::up() * Vector2::right() << std::endl;
}
