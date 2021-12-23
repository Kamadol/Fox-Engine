#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <memory>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Utility/Vec2.hpp"
#include "Utility/Rect.hpp"
#include "Utility/Image.hpp"

struct Character
{
	RectFloat getTextureRect() const;

	Vec2i size;
	Vec2i bearing;
	unsigned int advance = 0;
};
class Font
{
public:
	Font(const char* filename);
	~Font();

	void create(unsigned int fontSize);
	unsigned char* getRawData() const;
	Vec2i getTextureSize(unsigned int fontSize) const;
	Vec2i getTextureSize() const;
	unsigned int getFontSize() const;

	const std::vector<Character>& getCharacters() const;
	std::vector<Character> getCharactersCopy() const;
	const Character& getCharacter(char c) const;
	const Character& getCharacter(char c, const std::vector<Character>& characters) const;
	RectFloat getCharacterTextureRect(char c, const std::vector<Character>& characters, unsigned int fontSize) const;
	RectFloat getCharacterTextureRect(char c) const;

private:
	FT_Library m_ft;
	FT_Face m_face;

	unsigned char* m_rawData;
	unsigned int m_fontSize;
	std::vector<Character> m_characters;

};

#endif
