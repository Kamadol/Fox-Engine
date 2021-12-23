#include "Font.hpp"

#include <iostream>

#include "Utility/Constants.hpp"

RectFloat Character::getTextureRect() const
{

}

Font::Font(const char* filename)
    :m_rawData(nullptr), m_fontSize(0)
{
    if (FT_Init_FreeType(&m_ft))
    {
        std::cout << "Could not init FreeType library" << std::endl;
    }

    if (FT_New_Face(m_ft, filename, 0, &m_face))
    {
        std::cout << "Failed to load font" << std::endl;
    }
}
Font::~Font()
{
    delete[] m_rawData;
}

void Font::create(unsigned int fontSize)
{
    m_fontSize = fontSize;

    FT_Set_Pixel_Sizes(m_face, 0, fontSize);

    m_characters.clear();
    m_characters.reserve(asciiTo - asciiFrom);

    unsigned int currX = 0, currY = 0;

    size_t imageXSize = (size_t)glyphXCount * fontSize;
    size_t imageYSize = (size_t)glyphYCount * fontSize;

    delete[] m_rawData;
    m_rawData = new unsigned char[imageXSize * imageYSize];

    for (unsigned int i = asciiFrom; i < asciiTo; i++)
    {
        if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
        {
            std::cout << "Failed to load glyph: \'" << (unsigned char)i << "\'" << std::endl;
            continue;
        }

        unsigned int width = m_face->glyph->bitmap.width;
        unsigned int height = m_face->glyph->bitmap.rows;

        Character c;
        c.size = Vec2i(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
        c.bearing = Vec2i(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
        c.advance = m_face->glyph->advance.x;
        m_characters.push_back(c);

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                unsigned char grayScale = m_face->glyph->bitmap.buffer[(height - 1 - i) * width + j];

                unsigned int x = j + (size_t)currX * fontSize;
                unsigned int y = i + (size_t)currY * fontSize;

                m_rawData[imageXSize * y + x] = grayScale;
            }
        }

        currX++;
        if (currX == glyphXCount)
        {
            currX = 0;
            currY++;
            if (currY == glyphYCount)
                currY = 0;
        }
    }
}
unsigned char* Font::getRawData() const
{
    return m_rawData;
}
Vec2i Font::getTextureSize(unsigned int fontSize) const
{
    return Vec2i((size_t)glyphXCount * fontSize, (size_t)glyphYCount * fontSize);
}
Vec2i Font::getTextureSize() const
{
    return Vec2i((size_t)glyphXCount * m_fontSize, (size_t)glyphYCount * m_fontSize);
}
unsigned int Font::getFontSize() const
{
    return m_fontSize;
}

const std::vector<Character>& Font::getCharacters() const
{
    return m_characters;
}
std::vector<Character> Font::getCharactersCopy() const
{
    return m_characters;
}
const Character& Font::getCharacter(char c) const
{
    return m_characters[(unsigned int)c - 32];
}
const Character& Font::getCharacter(char c, const std::vector<Character>& characters) const
{
    return characters[(unsigned int)c - 32];
}
RectFloat Font::getCharacterTextureRect(char c, const std::vector<Character>& characters, unsigned int fontSize) const
{
    RectFloat ret;

    Vec2i size = getTextureSize(fontSize);
    Vec2f quadSize = Vec2f((float)fontSize / (float)size.x, (float)fontSize / (float)size.y);

    unsigned int id = (unsigned int)c - 32;
    unsigned int y = id / 10;
    unsigned int x = id - y * 10;

    Character ch = characters[(unsigned int)c - 32];

    ret.dl = Vec2f(quadSize.x * (float)x, quadSize.y * (float)y);
    ret.ur = Vec2f(quadSize.x * (float)x + (float)ch.size.x / (float)size.x, quadSize.y * (float)y + (float)ch.size.y / (float)size.y);

    return ret;
}
RectFloat Font::getCharacterTextureRect(char c) const
{
    RectFloat ret;

    Vec2i size = getTextureSize();
    Vec2f quadSize = Vec2f((float)m_fontSize / (float)size.x, (float)m_fontSize / (float)size.y);

    unsigned int id = (unsigned int)c - 32;
    unsigned int y = id / 10;
    unsigned int x = id - y * 10;

    Character ch = getCharacter(c);

    ret.dl = Vec2f(quadSize.x * (float)x                                   , quadSize.y * (float)y);
    ret.ur = Vec2f(quadSize.x * (float)x + (float)ch.size.x / (float)size.x, quadSize.y * (float)y + (float)ch.size.y / (float)size.y);

    return ret;
}
