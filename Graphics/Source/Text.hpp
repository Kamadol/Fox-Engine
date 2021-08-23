#ifndef TEXT_HPP
#define TEXT_HPP

#include <vector>

#include "Transformable.hpp"
#include "BitmapFont.hpp"


struct TextVertex
{
	TextVertex(Vector3 position, Vector2 texCoord)
		:position(position), texCoord(texCoord)
	{

	}

	Vector3 position;
	Vector2 texCoord;
};
class Text : public Transformable
{
public:
	Text();

	void setText(const std::string& text);
	void addNewLine(const std::string& text);
	void setFont(BitmapFont* font);

	const BitmapFont* getFont() const { return m_font; }
	const std::vector<TextVertex>& getVertices() const { return m_vertices; }

private:
	std::string m_text;
	BitmapFont* m_font;
	std::vector<TextVertex> m_vertices;

};

#endif
