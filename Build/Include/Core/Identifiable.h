#pragma once

#include "Core/Utility/Types.h"

class Identifiable
{
public:
	Identifiable();
	String GetUUID() const { return mId; }
	String GetShortUUID() const { return String(mId.begin(), mId.begin() + 7); }

	bool operator==(Identifiable other);
	bool operator!=(Identifiable other);

protected:
	String mId;

private:
	String GenerateUUID();
};
