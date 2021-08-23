#include "Text.hpp"

#include <iostream>

Text::Text()
	:m_text(""), m_font(nullptr)
{

}

void Text::setText(const std::string& text)
{
	m_text = text;

	m_vertices.clear();
	
	Vector2 currentPosition = Vector2::zero();
	Vector2 glyphSize = m_font->getGlyphSize();

	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n')
		{
			currentPosition.x = 0.0f;
			currentPosition.y += glyphSize.y;
			continue;
		}

		TextureRect rect = m_font->getGlyphCoord(text[i]);		

		m_vertices.push_back(TextVertex(Vector3(0.0f        + currentPosition.x, 0.0f        + currentPosition.y, 0.0f), rect.dl));
		m_vertices.push_back(TextVertex(Vector3(glyphSize.x + currentPosition.x, 0.0f        + currentPosition.y, 0.0f), rect.dr));
		m_vertices.push_back(TextVertex(Vector3(glyphSize.x + currentPosition.x, glyphSize.y + currentPosition.y, 0.0f), rect.ur));
		m_vertices.push_back(TextVertex(Vector3(0.0f        + currentPosition.x, glyphSize.y + currentPosition.y, 0.0f), rect.ul));

		currentPosition.x += glyphSize.x;
	}
}
void Text::addNewLine(const std::string& text)
{
	m_text = m_text + "\n" + text;
	setText(m_text);
}

void Text::setFont(BitmapFont* font)
{
	m_font = font;
}
