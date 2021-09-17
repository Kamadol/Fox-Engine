#ifndef COHERENT_NOISE_MASK
#define COHERENT_NOISE_MASK

#include <memory>

#include "Mask.hpp"

namespace pg
{
	class CoherentNoise;
	class CoherentNoiseMask : public Mask
	{
	public:
		CoherentNoiseMask();

		virtual float getValue(float x, float y) override;

		void setNoise(CoherentNoise* noise);
		void setSeed(int seed);

		void setXPosition(float positionX);
		void setYPosition(float positionY);
		void setStartZoom(float startZoom);
		void setOctaveCount(size_t octaves);

	private:
		std::unique_ptr<CoherentNoise> m_noise;

		float m_posX;
		float m_posY;
		float m_startZoom;
		size_t m_octaves;

	};
}

#endif
