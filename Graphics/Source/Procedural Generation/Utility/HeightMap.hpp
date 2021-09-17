#ifndef HEIGHT_MAP_HPP
#define HEIGHT_MAP_HPP

#include <vector>

#include "Masks/Mask.hpp"

#include "Utility/Color.hpp"

namespace pg
{
	enum class Interpolation
	{
		LERP,
		INT3,
		INT5
	};
	struct HeightStep
	{
		HeightStep(float from, float to, Color colorFrom, Color colorTo, Interpolation interpolation = Interpolation::LERP)
			:m_from(from), m_to(to), m_colorFrom(colorFrom), m_colorTo(colorTo)
		{

		}
		float m_from = 0.0f;
		float m_to = 1.0f;
		Color m_colorFrom = Color::White;
		Color m_colorTo = Color::Black;
		Interpolation m_interpolation = Interpolation::LERP;
	};
	class HeightMap
	{
	public:
		HeightMap(std::vector<HeightStep> steps);
		HeightMap();

		void addHeightStep(HeightStep step) { m_steps.push_back(step); }
		void clearSteps() { m_steps.clear(); }

		void saveToFile(float xPosition, float yPosition, size_t xSize, size_t ySize, float xZoom, float yZoom, Mask* mask, const char* filename) const;
		void saveToFile(size_t xPosition, size_t yPosition, size_t xSize, size_t ySize, float* values, const char* filename) const;

	private:
		std::vector<HeightStep> m_steps;

	public:
		static HeightMap BWHeightMap;
		static HeightMap NaturalHeightMap;
		static HeightMap NaturalFlatHeightMap;

	};
}

#endif
