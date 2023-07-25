#include "mthpch.h"

#include "Utility/Utils.h"

#include "Core/Solver.h"

void Solver::InitSolver(const Ref<MathNode>& tree)
{
    mTree = tree;
}

void Solver::InitSolver(const Ref<MathNode>& tree, const Map<uint32, Vector<Ref<MathNode>>>& executionFlow)
{
    mTree = tree;
    mExecutionFlow = executionFlow;
}

Number Solver::SolveTree()
{
    return mExecutionFlow.size() == 0 ? RecursiveSolve(mTree) : ExecutionSolve();
}

Number Solver::RecursiveSolve(const Ref<MathNode>& node)
{
    switch(node->type)
    {
        case EMathNodeType::BinaryFunction:
            {
                // Since the idoneity of each node is checked in the parser,
                // it is safe to instantiate [0] and [1], from the children.
                MTH_ASSERT(node->children.size() == 2, "What kind of sorcery is this?!");
                Ref<MathNode> leftChild  = node->children[0];
                Ref<MathNode> rightChild = node->children[1];

                Number left = RecursiveSolve(leftChild);
                Number right = RecursiveSolve(rightChild);

                // Get the function assigned to the math node.
                FBinaryFunction function = std::any_cast<FBinaryFunction>(node->data);
                return function(left, right);
            }
            break;
        case EMathNodeType::Number:      
            return std::any_cast<Number>(node->data);
            break;
        default:
            MTH_ASSERT(false, "What kind of sorcery is this?!");
            break;
    }
}

Number Solver::ExecutionSolve()
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
			Ref<MathNode> leftChild = operation->children[0];
			Ref<MathNode> rightChild = operation->children[1];

			MTH_ASSERT(leftChild->type  == EMathNodeType::Number, "What kind of sorcery is this?!");
			MTH_ASSERT(rightChild->type == EMathNodeType::Number, "What kind of sorcery is this?!");
            Number left  = std::any_cast<Number>( leftChild->data);
            Number right = std::any_cast<Number>(rightChild->data);

            FBinaryFunction function = std::any_cast<FBinaryFunction>(operation->data);
            Number operationResult = function(left, right);

            Ref<MathNode> newNode = Mathematica::MakeRef<MathNode>();
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
