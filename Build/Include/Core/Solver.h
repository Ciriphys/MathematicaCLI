#pragma once

#include "Utility/Types.h"

#include "Core/MathNode.h"
#include "Core/Number.h"

class MSolver
{
public:
    MSolver() = default;
    void InitSolver(const MRef<MMathNode>& tree);

    MNumber SolveTree();

private:
    MNumber RecursiveSolve(const MRef<MMathNode>& node);

    MRef<MMathNode> mTree;
};