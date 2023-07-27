#pragma once

#include "Core/Utility/Types.h"

#include "Core/MathNode.h"

class ExplanationSystem
{
public: 
	void Explain(Ref<MathNode> tree);

	Vector<String> GetSolution() const { return mSolution; }

	static ExplanationSystem& Get();
	void Flush();

private:
	void RecursiveExplain(Ref<MathNode> node);

	String mCurrentStep;
	Vector<String> mSolution;
};