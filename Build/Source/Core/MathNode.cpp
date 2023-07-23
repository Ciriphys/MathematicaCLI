#include "mthpch.h"

#include "Core/MathNode.h"

MMathNode::MMathNode(
    PointerType __parent,
    ChildrenType __children,
    MAny __data,
    EMathNodeType __type
) :
parent(__parent),
children(__children),
data(__data),
type(__type)
{

}
