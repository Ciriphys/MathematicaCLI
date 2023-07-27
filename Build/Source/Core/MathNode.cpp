#include "mthpch.h"

#include "Core/MathNode.h"

MathNode::MathNode(
    PointerType __parent,
    ChildrenType __children,
    Any __data,
    EMathNodeType __type,
    int32 __scope
) :
parent(__parent),
children(__children),
data(__data),
type(__type),
scope(__scope)
{

}
