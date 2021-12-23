#include "Sprite.hpp"

Sprite::Sprite(Vector3 position, Vector2 size, Vector4 color)
	:m_size(size), m_color(color)
{
	m_texCoords[0] = Vector2(1.0f, 1.0f);
	m_texCoords[1] = Vector2(0.0f, 1.0f);
	m_texCoords[2] = Vector2(0.0f, 0.0f);
	m_texCoords[3] = Vector2(1.0f, 0.0f);

	setPosition(position);
}
Sprite::Sprite()
	:m_size(Vector2::zero()), m_color(Vector4(1.0f, 1.0f, 1.0f, 1.0f))
{
	m_texCoords[0] = Vector2(1.0f, 1.0f);
	m_texCoords[1] = Vector2(0.0f, 1.0f);
	m_texCoords[2] = Vector2(0.0f, 0.0f);
	m_texCoords[3] = Vector2(1.0f, 0.0f);

	setPosition(Vector3::zero());
}
void Sprite::setSize(Vector2 size)
{
	m_size = size;
}
Vector2 Sprite::getSize() const
{
	return m_size;
}
void Sprite::setColor(Vector4 color)
{
	m_color = color;
}
Vector4 Sprite::getColor() const
{
	return m_color;
}
void Sprite::setTextureCoords(RectFloat rect)
{
	m_texCoords[0] = Vector2(rect.ur.x, rect.ur.y);
	m_texCoords[1] = Vector2(rect.dl.x, rect.ur.y);
	m_texCoords[2] = Vector2(rect.dl.x, rect.dl.y);
	m_texCoords[3] = Vector2(rect.ur.x, rect.dl.y);
}
const Vector2* Sprite::getTextureCoords() const
{
	return m_texCoords;
}
