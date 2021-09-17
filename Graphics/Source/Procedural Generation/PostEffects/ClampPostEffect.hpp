#ifndef CLAMP_POST_EFFECT_HPP
#define CLAMP_POST_EFFECT_HPP

#include "PostEffect.hpp"

class ClampPostEffect : public PostEffect
{
public:
	ClampPostEffect(float minClamp, float maxClamp)
		:m_minClamp(minClamp), m_maxClamp(maxClamp)
	{

	}

	virtual float getValue(float v) const
	{
		return v * (m_maxClamp - m_minClamp) + m_minClamp;
	}

private:
	float m_minClamp;
	float m_maxClamp;

};

#endif
