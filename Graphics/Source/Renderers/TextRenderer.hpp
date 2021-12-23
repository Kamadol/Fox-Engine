#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <unordered_map>
#include <vector>

#include "Shader.hpp"
#include "RenderText.hpp"

class TextRenderer
{
private:
	struct TextParams
	{
		TextParams();
		~TextParams();
		TextParams(TextParams&& other) noexcept;

		Font* font;
		size_t fontSize;
		Texture fontAtlas;
		std::vector<Character> characters;

		std::string text;
		Vector4 color;

		unsigned int VAO;
		unsigned int VBO;
		std::vector<TextVertex> vertices;
	};

public:
	TextRenderer();
	~TextRenderer();

	void flush(const RenderText& text, const Shader& shader, const Mat4x4& camera);

private:
	void createVertices(TextParams& params);

private:
	std::unordered_map<const RenderText*, TextParams> m_textParams;
	
	unsigned int m_IBO;

};

#endif
