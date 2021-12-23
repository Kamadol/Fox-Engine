#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "Sprite.hpp"
#include "Vertices/SpriteVertex.hpp"

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void start();
	void submit(const Sprite& sprite);
	void end();
	void flush();

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	SpriteVertex* m_bufferPtr;
	unsigned int m_idCount;

};

#endif
