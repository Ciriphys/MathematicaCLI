#pragma once

#include "Utility/Types.h"
#include "Core/Identifiable.h"

enum class EMathTokenType : int32
{
    Number, 
    BinaryOperation,

    Wrapper,

    Unknown
};

// This struct behaves like a node of a tree.
struct MMathToken : public IIdentifiable
{
    MRef<MMathToken> parent;
    MVector<MMathToken> children;

    MAny tokenData;
    EMathTokenType type;
};