#ifndef PROCEDURAL_GENERATION_HPP
#define PROCEDURAL_GENERATION_HPP

#include "Utility/Color.hpp"
#include "Utility/HeightMap.hpp"

#include "Noises/PerlinNoise.hpp"
#include "Noises/SimpleNoise.hpp"

#include "Masks/CoherentNoiseMask.hpp"
#include "Masks/CosineMask.hpp"
#include "Masks/GradientMask.hpp"
#include "Masks/RadialMask.hpp"

#include "MaskOperations/AddMaskOperation.hpp"
#include "MaskOperations/SubMaskOperation.hpp"
#include "MaskOperations/AvgMaskOperation.hpp"
#include "MaskOperations/MinMaskOperation.hpp"
#include "MaskOperations/MaxMaskOperation.hpp"
#include "MaskOperations/TruncLessMaskOperation.hpp"

#include "PostEffects/ClampPostEffect.hpp"

#include "RandomGenerators/BasicRandomFloatGen2D.hpp"
#include "RandomGenerators/ModRandomFloatGen2D.hpp"

#include "Utility/Image.hpp"

#endif
