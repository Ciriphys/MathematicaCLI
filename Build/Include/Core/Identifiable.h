#pragma once

#include "Utility/Types.h"

class MIdentifiable
{
public:
	MIdentifiable();
	MString GetUUID() const { return mId; }

protected:
	MString mId;

private:
	MString GenerateUUID();
};
