#pragma once

#include "Core/Utility/Types.h"

namespace Mathematica
{
	// TODO : Add more conversions.
	namespace Convert
	{
		String Uint32ToHexString(UInt32 number, UInt32 length);
		String Uint32ToOctString(UInt32 number, UInt32 length);

		String Uint32ToBaseString(UInt32 number, UInt32 base, UInt32 length);

		Int32 StringToInt32(String string);

		String Int32ToString(Int32 number);

		Float32 StringToFloat32(String string);
		Float64 StringToFloat64(String string);

		String Float32ToString(Float32 number);
		String Float64ToString(Float64 number);
	}
}