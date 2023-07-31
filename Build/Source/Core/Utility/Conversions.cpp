#include "mthpch.h"

#include "Core/Utility/Conversions.h"
#include "Core/Utility/Profiler.h"
#include "Core/Utility/Utils.h"

namespace Mathematica
{
	namespace Convert
	{
		String Uint32ToHexString(UInt32 number, UInt32 length)
		{
			return Uint32ToBaseString(number, 16, length);
		}

		String Uint32ToOctString(UInt32 number, UInt32 length)
		{
			return Uint32ToBaseString(number, 8, length);
		}

		String Uint32ToBaseString(UInt32 number, UInt32 base, UInt32 length)
		{
			MTH_ASSERT(base < 36, "ConversionError: Base is too large!");

			String result(length, '0');

			Int32 counter = length - 1;
			while (number != 0)
			{
				MTH_ASSERT(counter >= 0, "ConversionError: String is too narrow to contain information, please increase the length.");

				Int32 remainder = number % base;
				result[counter--] = remainder < 10 ? (char)(48 + remainder) : (char)(87 + remainder);
				number /= base;
			}

			return result;
		}

		Int32 StringToInt32(String string)
		{
			return std::atoi(string.c_str());
		}

		String Int32ToString(Int32 number)
		{
			return std::to_string(number);
		}

		Float32 StringToFloat32(String string)
		{
			return Mathematica::Cast<Float32>(std::atof(string.c_str()));
		}

		Float64 StringToFloat64(String string)
		{
			return std::atof(string.c_str());
		}

		String Float32ToString(Float32 number)
		{
			return std::to_string(number);
		}
		String Float64ToString(Float64 number)
		{
			return std::to_string(number);
		}
	}
}
