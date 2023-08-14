#include "mthpch.h"

#include "Core/ExplanationSystem.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Types.h"
#include "Core/Utility/Utils.h"

#include "Core/Math/Number.h"

void ExplanationSystem::Explain(Ref<MathNode> tree)
{
	MTH_PROFILE_FUNCTION();

	mCurrentStep = "";
	RecursiveExplain(tree);

	mSolution.push_back(mCurrentStep);
}

ExplanationSystem& ExplanationSystem::Get()
{
	static ExplanationSystem sInstance;
	return sInstance;
}

void ExplanationSystem::Flush()
{
	mSolution.clear();
	mCurrentStep = "";
}

void ExplanationSystem::RecursiveExplain(Ref<MathNode> node)
{
	MTH_PROFILE_FUNCTION();

	switch (node->type)
	{
	case EMathNodeType::BinaryFunction:
		mCurrentStep += node->scope != 0 ? "(" : "";
		RecursiveExplain(node->children[0]);
		mCurrentStep += " ";
		mCurrentStep += Mathematica::ToChar(Mathematica::AnyCast<FRationalBinaryRational>(node->data));
		mCurrentStep += " ";
		RecursiveExplain(node->children[1]);
		mCurrentStep += node->scope != 0 ? ")" : "";
		return;
	case EMathNodeType::Number:
		mCurrentStep += Mathematica::Stringify(Mathematica::AnyCast<RationalNumber>(node->data));
		return;
	default:
		MTH_ASSERT(false, "What kind of sorcery is this?!");
		return;
	}
}
