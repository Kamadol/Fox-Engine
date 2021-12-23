#include "TextRenderer.hpp"

#include <iostream>

#include "GL/glew.h"
#include "Utility/Constants.hpp"

TextRenderer::TextParams::TextParams()
	:font(nullptr),
	fontSize(0),
	text(""),
	color(1.0f, 1.0f, 1.0f, 1.0f),
	VAO(0),
	VBO(0)
{

}
TextRenderer::TextParams::~TextParams()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
TextRenderer::TextParams::TextParams(TextParams&& other) noexcept
	:font(other.font),
	fontSize(other.fontSize),
	fontAtlas(std::move(other.fontAtlas)),
	characters(other.characters),
	text(other.text),
	color(other.color),
	VAO(other.VAO),
	VBO(other.VBO)
{
	other.VAO = 0;
	other.VBO = 0;
}

TextRenderer::TextRenderer()
{
	unsigned int* indices = new unsigned int[textIndicesCount];

	for (size_t i = 0; i < maxGlyphs; i++)
	{
		indices[i * 6	 ] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 0;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	}

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, textIndicesSize, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] indices;
}
TextRenderer::~TextRenderer()
{
	glDeleteBuffers(1, &m_IBO);
}

void TextRenderer::flush(const RenderText& text, const Shader& shader, const Mat4x4& camera)
{
	std::unordered_map<const RenderText*, TextParams>::iterator it = m_textParams.find(&text);

	if (it != m_textParams.end()) //if text in map
	{
		glBindVertexArray(it->second.VAO);

		bool needUpdate = false;

		if (text.m_text != it->second.text)
		{
			it->second.text = text.m_text;

			needUpdate = true;
		}
		if (text.m_font != it->second.font || text.m_fontSize != it->second.fontSize)
		{
			it->second.font = text.m_font;
			it->second.fontSize = text.m_fontSize;
			it->second.font->create(text.m_fontSize);
			it->second.characters = it->second.font->getCharactersCopy();
			it->second.fontAtlas.create(it->second.font->getTextureSize(text.m_fontSize), it->second.font->getRawData(), 1); //this is probably bad

			needUpdate = true;
		}

		if (needUpdate)
		{
			createVertices(it->second);
		}

		glBindBuffer(GL_ARRAY_BUFFER, it->second.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertex) * it->second.vertices.size(), &it->second.vertices[0], GL_DYNAMIC_DRAW);
	}
	else //if text not in map
	{
		m_textParams[&text];
		it = m_textParams.find(&text);

		it->second.fontSize = text.m_fontSize;
		it->second.text = text.m_text;
		it->second.color = text.m_color;

		glGenVertexArrays(1, &it->second.VAO);
		glBindVertexArray(it->second.VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		glGenBuffers(1, &it->second.VBO);
		glBindBuffer(1, it->second.VBO);
		
		it->second.font = text.m_font;
		it->second.font->create(text.m_fontSize);
		it->second.characters = it->second.font->getCharactersCopy();
		it->second.fontAtlas.create(it->second.font->getTextureSize(text.m_fontSize), it->second.font->getRawData(), 1);

		createVertices(it->second);

		glBindBuffer(GL_ARRAY_BUFFER, it->second.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertex) * it->second.vertices.size(), &it->second.vertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, texCoord));
	}

	shader.bind();
	shader.setUniformMat4("u_MVP", camera * text.getTransform());
	glActiveTexture(GL_TEXTURE0);
	it->second.fontAtlas.bind();
	shader.setUniform1i("texture0", 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, it->second.vertices.size() / 4 * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

void TextRenderer::createVertices(TextParams& params)
{
	std::vector<TextVertex>& vertices = params.vertices;
	std::string& text				  = params.text;
	Vector4 color					  = params.color;
	Font* font						  = params.font;

	vertices.clear();
	vertices.reserve(text.size() / 4);

	Vec2i textureSize = font->getTextureSize(params.fontSize);

	Vec2f offset(0.0f, 0.0f);
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n')
		{
			offset.y -= (float)textureSize.y / (float)glyphYCount;
			offset.x = 0.0f;

			continue;
		}

		Character c = font->getCharacter(text[i], params.characters);
		RectFloat txRect = font->getCharacterTextureRect(text[i], params.characters, params.fontSize);

		Vec2f pos(offset.x + (float)c.bearing.x, offset.y - ((float)c.size.y - (float)c.bearing.y));

		vertices.push_back(TextVertex(Vector3(pos.x + c.size.x, pos.y + c.size.y, 0.0f), color, Vector2(txRect.ur.x, txRect.ur.y)));
		vertices.push_back(TextVertex(Vector3(pos.x			  , pos.y + c.size.y, 0.0f), color, Vector2(txRect.dl.x, txRect.ur.y)));
		vertices.push_back(TextVertex(Vector3(pos.x			  , pos.y			, 0.0f), color, Vector2(txRect.dl.x, txRect.dl.y)));
		vertices.push_back(TextVertex(Vector3(pos.x + c.size.x, pos.y			, 0.0f), color, Vector2(txRect.ur.x, txRect.dl.y)));

		offset.x += (float)(c.advance >> 6);
	}	
}
