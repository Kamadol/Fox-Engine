#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Utility/Rect.hpp"

#include "Transformable.hpp"

class Sprite : public Transformable
{
public:
	Sprite(Vector3 position, Vector2 size, Vector4 color);
	Sprite();

	void setSize(Vector2 size);
	Vector2 getSize() const;
	void setColor(Vector4 color);
	Vector4 getColor() const;
	void setTextureCoords(RectFloat rect);
	const Vector2* getTextureCoords() const;

private:
	Vector2 m_size;
	Vector4 m_color;
	Vector2 m_texCoords[4];

};

#endif
