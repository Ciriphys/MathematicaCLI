#pragma once

#include "Core/Utility/Types.h"

namespace Mathematica
{
	// TODO : Add more conversions.
	namespace Convert
	{
		String Uint32ToHexString(uint32 number, uint32 length);
		String Uint32ToOctString(uint32 number, uint32 length);

		String Uint32ToBaseString(uint32 number, uint32 base, uint32 length);

		int32 StringToInt32(String string);

		String Int32ToString(int32 number);

		float32 StringToFloat32(String string);
		float64 StringToFloat64(String string);

		String Float32ToString(float32 number);
		String Float64ToString(float64 number);
	}
}