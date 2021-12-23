#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Vector2.hpp"

#include "Utility/Vec2.hpp"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(Texture&& other) noexcept;

	bool create(const char* filename);
	bool create(Vec2i size, unsigned char* data, unsigned int channels);
	bool create(Vec2i size, unsigned char* data);

	void bind() const;
	void unbind() const;

	Vec2i getSize() const;

protected:
	unsigned int m_id;
	Vec2i m_size;

};

#endif
