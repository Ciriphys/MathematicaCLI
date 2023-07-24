#include "mthpch.h"

#include "Utility/Utils.h"

#include "Core/Solver.h"

void MSolver::InitSolver(const MRef<MMathNode>& tree)
{
    mTree = tree;
}

void MSolver::InitSolver(const MRef<MMathNode>& tree, const MMap<uint32, MVector<MRef<MMathNode>>>& executionFlow)
{
    mTree = tree;
    mExecutionFlow = executionFlow;
}

MNumber MSolver::SolveTree()
{
    return mExecutionFlow.size() == 0 ? RecursiveSolve(mTree) : ExecutionSolve();
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
                FBinaryFunction function = std::any_cast<FBinaryFunction>(node->data);
                return function(left, right);
            }
            break;
        case EMathNodeType::Number:      
            return std::any_cast<MNumber>(node->data);
            break;
        default:
            MTH_ASSERT(false, "What kind of sorcery is this?!");
            break;
    }
}

MNumber MSolver::ExecutionSolve()
{
    for (auto [order, operations] : mExecutionFlow)
    {
        for (auto operation : operations)
        {
            // Since the execution flow is generated in the parser,
            // it's safe to any_cast the children's data to MNumber.
            // Also, this function creates a new result node with
            // number type, that overwrites the current node. 
            // This allows every following operation to have 
            // both children of number type.

			MTH_ASSERT(operation->children.size() == 2, "What kind of sorcery is this?!");
			MRef<MMathNode> leftChild = operation->children[0];
			MRef<MMathNode> rightChild = operation->children[1];

			MTH_ASSERT(leftChild->type  == EMathNodeType::Number, "What kind of sorcery is this?!");
			MTH_ASSERT(rightChild->type == EMathNodeType::Number, "What kind of sorcery is this?!");
            MNumber left  = std::any_cast<MNumber>( leftChild->data);
            MNumber right = std::any_cast<MNumber>(rightChild->data);

            FBinaryFunction function = std::any_cast<FBinaryFunction>(operation->data);
            MNumber operationResult = function(left, right);

            MRef<MMathNode> newNode = Mathematica::MakeRef<MMathNode>();
            newNode->type = EMathNodeType::Number;
            newNode->parent = operation->parent;
            newNode->data = operationResult;

            // This is used to end the solve task.
            if (!newNode->parent) return operationResult;

            if (operation->parent->children[0] == operation)
            {
                operation->parent->children[0] = newNode;
            }
            else
            {
                operation->parent->children[1] = newNode;
            }
        }
    }

    MTH_ASSERT(false, "What kind of sorcery is this?!");
    return {};
}
