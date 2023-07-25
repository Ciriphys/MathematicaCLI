#pragma once

#include "Utility/Types.h"

namespace Mathematica
{
	// TODO : Add more conversions.
	namespace Convert
	{
		String IntToHexString(uint32 number, uint32 length);
		String IntToOctString(uint32 number, uint32 length);

		String IntToBaseString(uint32 number, uint32 base, uint32 length);

		// TODO : Write String to Float and Float to string
	}
}