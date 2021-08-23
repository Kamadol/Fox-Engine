#include "BitmapFont.hpp"

BitmapFont::BitmapFont(Vector2 glyphSize)
	:m_glyphSize(glyphSize)
{
	m_glyphsCoords['0'] = TextureRect(Vector2( 0.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['1'] = TextureRect(Vector2( 1.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['2'] = TextureRect(Vector2( 2.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['3'] = TextureRect(Vector2( 3.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['4'] = TextureRect(Vector2( 4.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['5'] = TextureRect(Vector2( 5.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['6'] = TextureRect(Vector2( 6.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['7'] = TextureRect(Vector2( 7.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['8'] = TextureRect(Vector2( 8.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
	m_glyphsCoords['9'] = TextureRect(Vector2( 9.0f * m_glyphSize.x, 0.0f * m_glyphSize.y), m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
}

TextureRect BitmapFont::getGlyphCoord(char a) const
{
	Vector2 quad;

	if (a == ' ')
		quad = Vector2(11.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '0')
		quad = Vector2( 0.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '1')
		quad = Vector2( 1.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '2')
		quad = Vector2( 2.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '3')
		quad = Vector2( 3.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '4')
		quad = Vector2( 4.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '5')
		quad = Vector2( 5.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '6')
		quad = Vector2( 6.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '7')
		quad = Vector2( 7.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '8')
		quad = Vector2( 8.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '9')
		quad = Vector2( 9.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == '.')
		quad = Vector2(10.0f * m_glyphSize.x, 0.0f * m_glyphSize.y);
	else if (a == 'm')
		quad = Vector2( 0.0f * m_glyphSize.x, 1.0f * m_glyphSize.y);
	else if (a == 's')
		quad = Vector2( 1.0f * m_glyphSize.x, 1.0f * m_glyphSize.y);
	else if (a == 'F')
		quad = Vector2( 2.0f * m_glyphSize.x, 1.0f * m_glyphSize.y);
	else if (a == 'P')
		quad = Vector2( 3.0f * m_glyphSize.x, 1.0f * m_glyphSize.y);
	else if (a == 'S')
		quad = Vector2( 4.0f * m_glyphSize.x, 1.0f * m_glyphSize.y);

	return TextureRect(quad, m_glyphSize, Vector2((float)m_xSize, (float)m_ySize));
}
Vector2 BitmapFont::getGlyphSize() const
{
	return m_glyphSize;
}