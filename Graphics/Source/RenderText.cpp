#include "RenderText.hpp"

#include <iostream>

#include "GL/glew.h"
#include "Utility/Constants.hpp"

RenderText::RenderText()
	:m_font(nullptr), m_fontSize(0), m_text(""), m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

void RenderText::setFont(Font* font)
{
	m_font = font;
}
const Font* RenderText::getFont() const
{
	return m_font;
}
void RenderText::setFontSize(size_t fontSize)
{
	m_fontSize = fontSize;
}
size_t RenderText::getFontSize() const
{
	return m_fontSize;
}

void RenderText::setText(const std::string& text)
{
	m_text = text;
}
void RenderText::addNewLine(const std::string& text)
{
	m_text += "\n" + text;
}

void RenderText::setColor(Vector4 color)
{
	m_color = color;
}
Vector4 RenderText::getColor() const
{
	return m_color;
}

bool RenderText::operator==(const RenderText& other) const
{
	return m_text == other.m_text;
}
