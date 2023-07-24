#pragma once

#include "Utility/Types.h"

#include "Core/MathNode.h"
#include "Core/Number.h"

class MSolver
{
public:
    MSolver() = default;
    void InitSolver(const MRef<MMathNode>& tree);
    void InitSolver(const MRef<MMathNode>& tree, const MMap<uint32, MVector<MRef<MMathNode>>>& executionFlow);

    MNumber SolveTree();

private:
    MNumber RecursiveSolve(const MRef<MMathNode>& node);
    MNumber ExecutionSolve();

	MMap<uint32, MVector<MRef<MMathNode>>> mExecutionFlow;
    MRef<MMathNode> mTree;
};