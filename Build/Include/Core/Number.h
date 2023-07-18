#pragma once

#include "Utility/Utils.h"
#include "Core/Identifiable.h"

// TODO : Add suport for real numbers. Currently this definition is valid for rationals.
struct MNumber : public IIdentifiable
{
    int32 numerator;
    int32 denominator;

    MNumber(int32 num = 0, int32 den = 1);

    MNumber LowestTerms();
};