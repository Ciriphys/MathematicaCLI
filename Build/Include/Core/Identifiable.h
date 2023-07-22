#pragma once

#include "Utility/Types.h"

class IIdentifiable
{
public:
	IIdentifiable();
	MString GetUUID() const { return mId; }
	MString GetShortUUID() const { return MString(mId.begin(), mId.begin() + 7); }

	bool operator==(IIdentifiable other);
	bool operator!=(IIdentifiable other);

protected:
	MString mId;

private:
	MString GenerateUUID();
};
