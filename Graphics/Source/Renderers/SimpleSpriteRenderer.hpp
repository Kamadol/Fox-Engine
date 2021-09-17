#ifndef SIMPLE_SPRITE_RENDERER_HPP
#define SIMPLE_SPRITE_RENDERER_HPP

#include "Sprite.hpp"
#include "Shader.hpp"

class SimpleSpriteRenderer
{
public:
	SimpleSpriteRenderer();
	~SimpleSpriteRenderer();

	void submit(const Sprite& sprite, Shader& shader, const Mat4x4& camera);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_indices[6];

};

#endif
