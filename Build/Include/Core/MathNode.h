#pragma once

#include "Core/Identifiable.h"

#include "Core/Utility/Types.h"

enum class EMathNodeType : Int32
{
    Number, 
    BinaryFunction,
    NamedFunction,

    WrapStart,
    WrapEnd,

    Wrapper,

    Macro,

    None
};

// This struct behaves like a node of a tree.
struct MathNode : public Identifiable
{
    using PointerType = Ref<MathNode>;
    using ChildrenType = Vector<PointerType>;

    Int32 scope;

    PointerType parent;
    ChildrenType children;

    Any data;
    EMathNodeType type;

    MathNode(
        PointerType __parent = nullptr,
        ChildrenType __children = {},
        Any __data = {},
        EMathNodeType __type = EMathNodeType::None,
        Int32 __scope = -1
    );
};
