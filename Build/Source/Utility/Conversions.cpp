#include "mthpch.h"

#include "Utility/Conversions.h"
#include "Utility/Utils.h"

namespace Mathematica
{
	namespace Convert
	{
		String Uint32ToHexString(uint32 number, uint32 length)
		{
			return Uint32ToBaseString(number, 16, length);
		}

		String Uint32ToOctString(uint32 number, uint32 length)
		{
			return Uint32ToBaseString(number, 8, length);
		}

		String Uint32ToBaseString(uint32 number, uint32 base, uint32 length)
		{
			MTH_ASSERT(base < 36, "ConversionError: Base is too large!");

			String result(length, '0');

			int32 counter = length - 1;
			while (number != 0)
			{
				MTH_ASSERT(counter >= 0, "ConversionError: String is too narrow to contain information, please increase the length.");

				int32 remainder = number % base;
				result[counter--] = remainder < 10 ? (char)(48 + remainder) : (char)(87 + remainder);
				number /= base;
			}

			return result;
		}

		int32 StringToInt32(String string)
		{
			return std::atoi(string.c_str());
		}

		String Int32ToString(int32 number)
		{
			return std::to_string(number);
		}

		float32 StringToFloat32(String string)
		{
			return std::atof(string.c_str());
		}

		float64 StringToFloat64(String string)
		{
			return std::atof(string.c_str());
		}

		String Float32ToString(float32 number)
		{
			return std::to_string(number);
		}
		String Float64ToString(float64 number)
		{
			return std::to_string(number);
		}
	}
}
