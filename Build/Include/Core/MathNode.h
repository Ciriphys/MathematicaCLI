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
struct MMathNode : public IIdentifiable
{
    MRef<MMathNode> parent;
    MVector<MMathNode> children;

    MAny tokenData;
    EMathTokenType type;
};