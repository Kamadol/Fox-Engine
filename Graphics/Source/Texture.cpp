#include "Texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "..\Vendor\stb_image.h"
#include "GL/glew.h"

Texture::Texture()
	:m_xSize(0), m_ySize(0)
{
	glGenTextures(1, &m_id);
}
bool Texture::load(const char* filename)
{
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &m_xSize, &m_ySize, &nrChannels, 4);

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_xSize, m_ySize, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
