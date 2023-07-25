#include "mthpch.h"

#include "Core/MathNode.h"

MathNode::MathNode(
    PointerType __parent,
    ChildrenType __children,
    Any __data,
    EMathNodeType __type
) :
parent(__parent),
children(__children),
data(__data),
type(__type)
{

}
