#ifndef RENDER_TEXT_HPP
#define RENDER_TEXT_HPP

#include <vector>

#include "Transformable.hpp"
#include "Vector2.hpp"
#include "Vector4.hpp"

#include "Font.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct TextVertex
{
	TextVertex(Vector3 position, Vector4 color, Vector2 texCoord)
		:position(position), color(color), texCoord(texCoord)
	{

	}

	Vector3 position;
	Vector4 color;
	Vector2 texCoord;
};
class TextRenderer;
class RenderText : public Transformable
{
private:
	friend TextRenderer;

public:
	RenderText();

	void setFont(Font* font);
	const Font* getFont() const;
	void setFontSize(size_t fontSize);
	size_t getFontSize() const;

	void setText(const std::string& text);
	void addNewLine(const std::string& text);

	void setColor(Vector4 color);
	Vector4 getColor() const;

	bool operator==(const RenderText& other) const;

private:
	Font* m_font;
	size_t m_fontSize;
	std::string m_text;
	Vector4 m_color;

};

#endif
