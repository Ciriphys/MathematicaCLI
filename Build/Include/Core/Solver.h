#pragma once

#include "Core/Utility/Types.h"

#include "Core/Math/Number.h"

#include "Core/MathNode.h"

class Solver
{
public:
    Solver() = default;
    void InitSolver(const Ref<MathNode>& tree);
    void InitSolver(const Ref<MathNode>& tree, const Map<uint32, Vector<Ref<MathNode>>>& executionFlow);

    Number SolveTree();

private:
    Number RecursiveSolve(const Ref<MathNode>& node);
    Number ExecutionSolve();

	Map<uint32, Vector<Ref<MathNode>>> mExecutionFlow;
    Ref<MathNode> mTree;
};