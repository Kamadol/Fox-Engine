#include "Mask.hpp"

pg::Mask::Mask()
	:m_next(nullptr), m_operation(nullptr), m_postEffect(nullptr)
{

}

void pg::Mask::setNext(Mask* next)
{
	m_next = next;
}
void pg::Mask::setOperation(MaskOperation* operation)
{
	m_operation = operation;
}
void pg::Mask::setPostEffect(PostEffect* postEffect)
{
	m_postEffect = postEffect;
}

float pg::Mask::operator()(float x, float y)
{
	float value = 0.0f;

	if (m_next != nullptr)
	{
		if (m_operation != nullptr)
			value = m_operation->getValue(getValue(x, y), (*m_next)(x, y));
	}
	else
		value = getValue(x, y);

	if (m_postEffect != nullptr)
		value = m_postEffect->getValue(value);

	return value;
}
