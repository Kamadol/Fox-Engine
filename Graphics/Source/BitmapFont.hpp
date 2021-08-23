#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include <unordered_map>

#include "Texture.hpp"

class BitmapFont : public Texture
{
public:
	BitmapFont(Vector2 glyphSize);

	TextureRect getGlyphCoord(char a) const;
	Vector2 getGlyphSize() const;

private:
	Vector2 m_glyphSize;
	std::unordered_map<char, TextureRect> m_glyphsCoords;

};

#endif
