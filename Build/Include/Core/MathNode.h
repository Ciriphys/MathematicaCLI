#pragma once

#include "Core/Identifiable.h"

#include "Utility/Types.h"

enum class EMathNodeType : int32
{
    Number, 
    BinaryFunction,

    WrapStart,
    WrapEnd,

    Wrapper,

    None
};

// This struct behaves like a node of a tree.
struct MathNode : public Identifiable
{
    using PointerType = Ref<MathNode>;
    using ChildrenType = Vector<PointerType>;

    PointerType parent;
    ChildrenType children;

    Any data;
    EMathNodeType type;

    MathNode(PointerType __parent = nullptr, ChildrenType __children = {}, Any __data = {}, EMathNodeType __type = EMathNodeType::None);
};
