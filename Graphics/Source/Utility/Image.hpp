#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Color.hpp"

class Image
{
public:
	Image();
	~Image();

	void create(size_t x, size_t y, Color color);
	void create(size_t x, size_t y, unsigned char* data);
	void setPixel(size_t x, size_t y, Color color);
	Color getPixel(size_t x, size_t y) const;

	void flip(bool vertical, bool horizontal);
	void drawGrid(size_t xOffset, size_t yOffset, Color color);

	bool loadFromFile(const char* filename);
	bool saveToFile(const char* filename) const;

	unsigned char* getRawData() const;

private:
	int m_xSize, m_ySize;
	unsigned char* m_data;

};

#endif
