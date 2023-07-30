#pragma once

#include "Core/Utility/Types.h"

#include "Core/Math/Number.h"

#include "Core/ExplanationSystem.h"
#include "Core/MathNode.h"

class Solver
{
public:
    Solver();
    void InitSolver(const Ref<MathNode>& tree);
    void InitSolver(const Ref<MathNode>& tree, const Map<uint32, Vector<Ref<MathNode>>>& executionFlow);

    RationalNumber SolveTree();

private:
    RationalNumber RecursiveSolve(const Ref<MathNode>& node);
    RationalNumber ExecutionSolve();

	Map<uint32, Vector<Ref<MathNode>>> mExecutionFlow;
    ExplanationSystem& mExplanationSystem;
    Ref<MathNode> mTree;
};