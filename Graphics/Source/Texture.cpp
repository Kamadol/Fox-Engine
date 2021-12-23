#include "Texture.hpp"

#include <iostream>

#include "GL/glew.h"

#include "../Vendor/stb_image.h"

Texture::Texture()
{
	glGenTextures(1, &m_id);
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}
Texture::Texture(Texture&& other) noexcept
	:m_id(other.m_id)
{
	other.m_id = 0;
}

bool Texture::create(const char* filename)
{
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &m_size.x, &m_size.y, &nrChannels, 4);

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture from: \"" << filename << "\"" << std::endl;
		return false;
	}

	stbi_image_free(data);

	return true;
}
bool Texture::create(Vec2i size, unsigned char* data, unsigned int channels)
{
	m_size = size;

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if(channels == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		else if(channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);

		return true;
	}
	else
	{
		return false;
	}
}
bool Texture::create(Vec2i size, unsigned char* data)
{
	m_size = size;

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		return true;
	}
	else
	{
		return false;
	}
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Vec2i Texture::getSize() const
{ 
	return m_size; 
}
