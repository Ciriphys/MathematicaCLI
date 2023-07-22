#pragma once

#include "Utility/Types.h"

namespace Mathematica
{
	// TODO : Add more conversions.
	namespace Convert
	{
		MString IntToHexString(uint32 number, uint32 length);
		MString IntToOctString(uint32 number, uint32 length);

		MString IntToBaseString(uint32 number, uint32 base, uint32 length);
	}
}