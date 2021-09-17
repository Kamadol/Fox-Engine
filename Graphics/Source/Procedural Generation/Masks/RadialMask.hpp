#ifndef RADIAL_MASK_HPP
#define RADIAL_MASK_HPP

#include <cmath>

#include "Mask.hpp"

namespace pg
{
	class RadialMask : public Mask
	{
	public:
		RadialMask(float xCenter, float yCenter, float r, float R);

		virtual float getValue(float x, float y) override;

	private:
		float m_xCenter;
		float m_yCenter;
		float m_r;
		float m_R;

	};
}

#endif
