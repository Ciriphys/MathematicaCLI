#pragma once

#include "Core/Identifiable.h"

#include "Utility/Types.h"

enum class EMathNodeType : int32
{
    Number, 
    BinaryFunction,

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
    EMathNodeType type;

    MMathNode(PointerType __parent = nullptr, ChildrenType __children = {}, MAny __data = {}, EMathNodeType __type = EMathNodeType::Unknown);
};
