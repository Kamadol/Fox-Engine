#include "HeightMap.hpp"

#include <iostream>

#include "Utility\Image.hpp"

namespace pg
{
	HeightMap HeightMap::BWHeightMap = HeightMap({ HeightStep(0.0f, 1.0f, Color(255, 255, 255), Color(0, 0, 0)) });
	HeightMap HeightMap::NaturalHeightMap = HeightMap({ HeightStep(0.0f, 0.5f, Color(0, 0, 50), Color(0, 0, 200)),
														HeightStep(0.5f, 1.0f, Color(0, 200, 0), Color(0, 50, 0)) });
	HeightMap HeightMap::NaturalFlatHeightMap = HeightMap({ HeightStep(0.0f, 0.5f, Color(0, 0, 100), Color(0, 0, 100)),
														HeightStep(0.5f, 1.0f, Color(0, 150, 0), Color(0, 150, 0)) });

	HeightMap::HeightMap(std::vector<HeightStep> steps)
		:m_steps(steps)
	{

	}
	HeightMap::HeightMap()
	{

	}

	void HeightMap::saveToFile(float xPosition, float yPosition, size_t xSize, size_t ySize, float xZoom, float yZoom, Mask* mask, const char* filename) const
	{
		Image image;
		image.create(xSize, ySize, Color::White);

		size_t pixelCount = xSize * ySize;
		size_t saveOffset = pixelCount / 5;
		size_t currentPixelCount = 0;

		for (size_t y = 0; y < ySize; y++)
		{
			for (size_t x = 0; x < xSize; x++)
			{
				Color color = Color::White;
				float value = (*mask)((float)x, (float)y);

				for (size_t s = 0; s < m_steps.size(); s++)
				{
					if (value >= m_steps[s].from && value <= m_steps[s].to)
					{
						color = m_steps[s].colorFrom.lerpColor(m_steps[s].colorTo, (value - m_steps[s].from) / (m_steps[s].to - m_steps[s].from));
						break;
					}
				}

				size_t xPixelPos = (size_t)(((float)x + xPosition) / xZoom);
				size_t yPixelPos = (size_t)(((float)y + yPosition) / yZoom);
				image.setPixel(xPixelPos, yPixelPos, Color(color.r, color.g, color.b, color.a));

				if (++currentPixelCount % saveOffset == 0)
					std::cout << filename << " done in " << (float)currentPixelCount / (float)pixelCount * 100.0f << "%" << std::endl;
			}
		}

		image.saveToFile(filename);

		std::cout << filename << " saved" << std::endl;
	}
	void HeightMap::saveToFile(size_t xPosition, size_t yPosition, size_t xSize, size_t ySize, float* values, const char* filename) const
	{
		Image image;
		image.create(xSize, ySize, Color::White);

		size_t pixelCount = xSize * ySize;
		size_t saveOffset = pixelCount / 5;
		size_t currentPixelCount = 0;

		for (size_t y = 0; y < ySize; y++)
		{
			for (size_t x = 0; x < xSize; x++)
			{
				Color color = Color::White;
				float value = values[y * xSize + x];

				for (size_t s = 0; s < m_steps.size(); s++)
				{
					if (value >= m_steps[s].from && value <= m_steps[s].to)
					{
						if (m_steps[s].interpolation == Interpolation::LERP)
							color = m_steps[s].colorFrom.lerpColor(m_steps[s].colorTo, (value - m_steps[s].from) / (m_steps[s].to - m_steps[s].from));
						else if(m_steps[s].interpolation == Interpolation::INT3)
							color = m_steps[s].colorFrom.interpolate3Color(m_steps[s].colorTo, (value - m_steps[s].from) / (m_steps[s].to - m_steps[s].from));
						else if (m_steps[s].interpolation == Interpolation::INT5)
							color = m_steps[s].colorFrom.interpolate5Color(m_steps[s].colorTo, (value - m_steps[s].from) / (m_steps[s].to - m_steps[s].from));
						break;
					}
				}

				size_t xPixelPos = (size_t)((float)x + xPosition);
				size_t yPixelPos = (size_t)((float)y + yPosition);
				image.setPixel(xPixelPos, yPixelPos, Color(color.r, color.g, color.b, color.a));

				if (++currentPixelCount % saveOffset == 0)
					std::cout << filename << " done in " << (float)currentPixelCount / (float)pixelCount * 100.0f << "%" << std::endl;
			}
		}

		image.saveToFile(filename);

		std::cout << filename << " saved" << std::endl;
	}
}
