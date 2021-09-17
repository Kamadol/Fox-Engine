#ifndef MASK_HPP
#define MASK_HPP

#include "MaskOperations/MaskOperation.hpp"
#include "PostEffects/PostEffect.hpp"

namespace pg
{
	class Mask
	{
	public:
		Mask();

		void setNext(Mask* next);
		void setOperation(MaskOperation* operation);
		void setPostEffect(PostEffect* postEffect);

		float operator()(float x, float y);

	private:
		Mask* m_next;
		MaskOperation* m_operation;
		PostEffect* m_postEffect;

	protected:
		virtual float getValue(float x, float y) = 0;

	};
}

#endif
