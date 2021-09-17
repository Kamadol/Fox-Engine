#ifndef GRADIENT_MASK_HPP
#define GRADIENT_MASK_HPP

#include <cmath>

#include "Mask.hpp"

namespace pg
{
	class GradientMask : public Mask
	{
	public:
		GradientMask(float x0, float y0, float x1, float y1, bool vertical);

		virtual float getValue(float x, float y) override;

	private:
		float m_x0, m_y0, m_x1, m_y1;
		bool m_vertical;

	};
}

#endif
