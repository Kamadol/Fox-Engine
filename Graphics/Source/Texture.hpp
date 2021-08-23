#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Vector2.hpp"

struct TextureRect
{
	TextureRect()
	{

	}
	TextureRect(Vector2 position, Vector2 size)
	{
		dl = position;
		dr = Vector2(position.x + size.x, position.y);
		ur = Vector2(position.x + size.x, position.y + size.y);
		ul = Vector2(position.x,          position.y + size.y);
	}
	TextureRect(Vector2 pixelPosition, Vector2 quadPixelSize, Vector2 texturePixelSize)
	{
		Vector2 size(quadPixelSize.x / texturePixelSize.x, quadPixelSize.y / texturePixelSize.y);
		Vector2 position(pixelPosition.x / texturePixelSize.x, pixelPosition.y / texturePixelSize.y);

		dl = position;
		dr = Vector2(position.x + size.x, position.y);
		ur = Vector2(position.x + size.x, position.y + size.y);
		ul = Vector2(position.x,          position.y + size.y);
	}

	Vector2 dl;
	Vector2 dr;
	Vector2 ur;
	Vector2 ul;
};
class Texture
{
public:
	Texture();
	bool load(const char* filename);

	void bind() const;
	void unbind() const;

	Vector2 getSize() const { return Vector2((float)m_xSize, (float)m_ySize); }

protected:
	size_t m_id;
	int m_xSize, m_ySize;

};

#endif
