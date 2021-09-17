#ifndef AVG_MASK_OPERATION_HPP
#define AVG_MASK_OPERATION_HPP

#include "MaskOperation.hpp"

namespace pg
{
	class AvgMaskOperation : public MaskOperation
	{
	public:
		virtual float getValue(float v0, float next) const
		{
			return (v0 + next) * 0.5f;
		}

	};
}

#endif
