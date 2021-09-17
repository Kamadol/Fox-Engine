#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Color.hpp"

namespace pg
{
	class Image
	{
	public:
		Image();
		~Image();

		void create(size_t x, size_t y, Color color);
		void setPixel(size_t x, size_t y, Color color);
		Color getPixel(size_t x, size_t y) const;

		bool loadFromFile(const char* filename);
		bool saveToFile(const char* filename) const;

	private:
		int m_xSize, m_ySize;
		unsigned char* m_data;

	};
}

#endif
