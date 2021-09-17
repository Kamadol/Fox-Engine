#ifndef TRUNC_ADD_MIN_MASK_OPERATION_HPP
#define TRUNC_ADD_MIN_OPERATION_HPP

#include "MaskOperation.hpp"

namespace pg
{
	class TruncLessMaskOperation : public MaskOperation
	{
	public:
		virtual float getValue(float v0, float next) const
		{
			if (next > v0)
				return v0;
			else
				return 0.0f;
		}

	};
}

#endif
