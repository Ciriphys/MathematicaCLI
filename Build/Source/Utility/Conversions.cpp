#include "mthpch.h"

#include "Utility/Conversions.h"
#include "Utility/Utils.h"

namespace Mathematica
{
	namespace Convert
	{
		MString IntToHexString(uint32 number, uint32 length)
		{
			return IntToBaseString(number, 16, length);
		}

		MString IntToOctString(uint32 number, uint32 length)
		{
			return IntToBaseString(number, 8, length);
		}

		MString IntToBaseString(uint32 number, uint32 base, uint32 length)
		{
			MTH_ASSERT(base < 36, "ConversionError: Base is too large!");

			MString result(length, '0');

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
	}
}
