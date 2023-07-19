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
    using PointerType = MRef<MMathNode>;
    using ChildrenType = MVector<PointerType>;

    PointerType parent;
    ChildrenType children;

    MAny tokenData;
    EMathTokenType type;

    MMathNode(PointerType __parent = nullptr, ChildrenType __children = {}, MAny __data = {}, EMathTokenType __type = EMathTokenType::Unknown);
};
