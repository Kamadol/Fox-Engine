#ifndef COSINE_MASK_HPP
#define COSINE_MASK_HPP

#include <cmath>

#include "Mask.hpp"

namespace pg
{
	class CosineMask : public Mask
	{
	public:
		CosineMask(float posX, float posY, float period);
		CosineMask();

		void setXPosition(float positionX) { m_posX = positionX; }
		void setYPosition(float positionY) { m_posY = positionY; }
		void setPeriod(float p) { m_omega = (2.0f * 3.1415f) / p; }

		virtual float getValue(float x, float y) override;

	private:
		float m_posX;
		float m_posY;
		float m_omega;

	};
}

#endif
