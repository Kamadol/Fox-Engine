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
	size_t m_VAO;
	size_t m_VBO;
	size_t m_IBO;
	size_t m_indices[6];

};

#endif
