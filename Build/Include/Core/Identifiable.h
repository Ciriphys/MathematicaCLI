#pragma once

#include "Utility/Types.h"

class IIdentifiable
{
public:
	IIdentifiable();
	MString GetUUID() const { return mId; }

	bool operator==(IIdentifiable other);
	bool operator!=(IIdentifiable other);

protected:
	MString mId;

private:
	MString GenerateUUID();
};
