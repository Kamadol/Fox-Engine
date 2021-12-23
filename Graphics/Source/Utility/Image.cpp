#include "Image.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../Vendor/stb_image.h"

#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../Vendor/stb_image_write.h"

Image::Image()
		:m_xSize(0), m_ySize(0), m_data(nullptr)
	{
		
	}
Image::~Image()
{
	delete[] m_data;
}

void Image::create(size_t x, size_t y, Color color)
	{
		m_xSize = x;
		m_ySize = y;

		delete[] m_data;
		m_data = new unsigned char[x * y * 4];
		int index = 0;
		for (size_t i = 0; i < x * y; i++)
		{
			m_data[i * 4    ] = color.r;
			m_data[i * 4 + 1] = color.g;
			m_data[i * 4 + 2] = color.b;
			m_data[i * 4 + 3] = color.a;
		}
	}
void Image::create(size_t x, size_t y, unsigned char* data)
{
	m_xSize = x;
	m_ySize = y;

	m_data = data;
}
void Image::setPixel(size_t x, size_t y, Color color)
{
	size_t index = (y * m_xSize + x) * 4;

	m_data[index    ] = color.r;
	m_data[index + 1] = color.g;
	m_data[index + 2] = color.b;
	m_data[index + 3] = color.a;
}
Color Image::getPixel(size_t x, size_t y) const
{
	size_t index = (y * m_xSize + x) * 4;

	unsigned char r = m_data[index    ];
	unsigned char g = m_data[index + 1];
	unsigned char b = m_data[index + 2];
	unsigned char a = m_data[index + 3];

	return Color(r, g, b, a);
}

void Image::flip(bool vertical, bool horizontal)
{
	if (vertical)
	{
		for (size_t i = 0; i < m_ySize / 2; i++)
		{
			for (size_t j = 0; j < m_xSize; j++)
			{
				Color down = getPixel(j, m_ySize - i - 1);
				Color up = getPixel(j, i);

				setPixel(j, i, down);
				setPixel(j, m_ySize - i - 1, up);
			}
		}
	}
	if (horizontal)
	{
		for (size_t i = 0; i < m_ySize; i++)
		{
			for (size_t j = 0; j < m_xSize / 2; j++)
			{
				Color right = getPixel(m_xSize - j - 1, i);
				Color left = getPixel(j, i);

				setPixel(j, i, right);
				setPixel(m_xSize - j - 1, i, left);
			}
		}
	}
}
void Image::drawGrid(size_t xOffset, size_t yOffset, Color color)
{
	size_t xStrips = m_xSize / xOffset;
	size_t yStrips = m_ySize / yOffset;

	for (size_t i = 0; i < m_xSize; i += xOffset)
	{
		for (size_t k = 0; k < m_ySize; k++)
		{
			setPixel(i, k, color);
		}
	}

	for (size_t i = 0; i < m_ySize; i += yOffset)
	{
		for (size_t k = 0; k < m_xSize; k++)
		{
			setPixel(k, i, color);
		}
	}
}

bool Image::loadFromFile(const char* filename)
	{
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename, &m_xSize, &m_ySize, &nrChannels, 4);

		if (!data)
		{
			std::cout << "failed to load image from: \"" << filename << "\"" << std::endl;
			return false;
		}

		stbi_image_free(data);

		return true;
	}
bool Image::saveToFile(const char* filename) const
{
	if (!stbi_write_png(filename, m_xSize, m_ySize, 4, m_data, m_xSize * 4))
	{
		std::cout << "failed to save image to: \"" << filename << "\"" << std::endl;
		return false;
	}

	return true;
}

unsigned char* Image::getRawData() const
{
	return m_data;
}
