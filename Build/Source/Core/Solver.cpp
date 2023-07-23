#include "mthpch.h"

#include "Utility/Utils.h"

#include "Core/Solver.h"

void MSolver::InitSolver(const MRef<MMathNode>& tree)
{
    mTree = tree;
}

MNumber MSolver::SolveTree()
{
    return RecursiveSolve(mTree);
}

MNumber MSolver::RecursiveSolve(const MRef<MMathNode>& node)
{

    switch(node->type)
    {
        case EMathNodeType::BinaryFunction:
            {
                // Since the idoneity of each node is checked in the parser,
                // it is safe to instantiate [0] and [1], from the children.
                MTH_ASSERT(node->children.size() == 2, "What kind of sorcery is this?!");
                MRef<MMathNode> leftChild  = node->children[0];
                MRef<MMathNode> rightChild = node->children[1];

                MNumber left = RecursiveSolve(leftChild);
                MNumber right = RecursiveSolve(rightChild);

                // Get the function assigned to the math node.
                try{
                FBinaryFunction function = std::any_cast<FBinaryFunction>(node->data);
                return function(left, right);
                } catch(...)
                {
                    MTH_ASSERT(false, "Crashed! bad_any_cast<FBinaryFunction> detected!");
                }
            }
            break;
        case EMathNodeType::Number:
            try
            {            
            return std::any_cast<MNumber>(node->data);
             } catch(...)
                {
                    MTH_ASSERT(false, "Crashed! bad_any_cast<FBinaryFunction> detected!");
                }
            break;
        default:
            MTH_ASSERT(false, "What kind of sorcery is this?!");
            break;
    }
}