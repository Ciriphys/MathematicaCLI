#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Real.h"

namespace Mathematica
{
	namespace Real
	{
		namespace Operation
		{
			MathExpression Add(const MathExpression& first, const MathExpression& second)
			{
				Vector<RealNumber> firstAdd  = Mathematica::Real::ExecuteMultiply(first.numerator, second.denominator);
				Vector<RealNumber> secondAdd = Mathematica::Real::ExecuteMultiply(second.numerator, first.denominator);

				Vector<RealNumber> common = Mathematica::Real::ExecuteMultiply(first.denominator, second.denominator);

				// Merge firstAdd and secondAdd and call ExecuteSimplify
				firstAdd.insert(firstAdd.begin(), secondAdd.begin(), secondAdd.end());

				// NOTE : Should simplify using factorization here although it's not strictly necessary right now.

				return { ExecuteSimplify(firstAdd), common };
			}

			MathExpression Subtract(const MathExpression& first, const MathExpression& second)
			{
				Vector<RealNumber> firstSub  = Mathematica::Real::ExecuteMultiply(first.numerator, second.denominator);
				Vector<RealNumber> secondSub = Mathematica::Real::ExecuteMultiply(second.numerator, first.denominator);

				Vector<RealNumber> common = Mathematica::Real::ExecuteMultiply(first.denominator, second.denominator);

				// Merge firstAdd and reversed secondAdd and call ExecuteSimplify
				for (auto& real : secondSub) firstSub.push_back(-real);

				// NOTE : Should simplify using factorization here although it's not strictly necessary right now.

				return { ExecuteSimplify(firstSub), common };
			}

			MathExpression Multiply(const MathExpression& first, const MathExpression& second)
			{
				Vector<RealNumber> newNumerator   = Mathematica::Real::ExecuteMultiply(first.numerator,   second.numerator);
				Vector<RealNumber> newDenominator = Mathematica::Real::ExecuteMultiply(first.denominator, second.denominator);

				// NOTE : Should simplify using factorization here although it's not strictly necessary right now.

				MTH_ASSERT(newDenominator.size() != 0, "DomainError: Denominator cannot be zero!");

				return { newNumerator, newDenominator };
			}

			MathExpression Divide(const MathExpression& first, const MathExpression& second)
			{
				MTH_ASSERT(second.numerator.size() != 0, "DomainError: Cannot divide by zero!");

				Vector<RealNumber> newNumerator   = Mathematica::Real::ExecuteMultiply(first.numerator, second.denominator);
				Vector<RealNumber> newDenominator = Mathematica::Real::ExecuteMultiply(first.denominator, second.numerator);

				// NOTE : Should simplify using factorization here although it's not strictly necessary right now.

				return { newNumerator, newDenominator };
			}
		}

		Vector<RealNumber> ExecuteMultiply(const Vector<RealNumber>& first, const Vector<RealNumber>& second)
		{
			// TODO : Check if ExecuteMultiply can be performed on two MathExpression objects.

			Vector<RealNumber> result = {};

			for (auto& firstReal : first)
			{
				for (auto& secondReal : second)
				{
					RealNumber multiplication;
					multiplication.irrational.PopBack();

					multiplication.rational = firstReal.rational * secondReal.rational;

					// Check if the irrational parts can be simplified.
					// The following Hash Map is used to count the irrational symbols that are found in the reals.
					HashMap<IrrationalNumber, UInt32, HashBinding<IrrationalNumber>, CompareHashable<IrrationalNumber>> symbolMap;

					// Store the irrational symbols stored in firstReal and secondReal.
					for (auto& irrational : firstReal.irrational)
					{
						symbolMap[irrational] = (symbolMap.find(irrational) != symbolMap.end()) ? symbolMap[irrational] + 1 : 1;
					}

					for (auto& irrational : secondReal.irrational)
					{
						symbolMap[irrational] = (symbolMap.find(irrational) != symbolMap.end()) ? symbolMap[irrational] + 1 : 1;
					}

					// After each irrational symbol is stored, we loop through the HashMap to make sure that each symbol
					// is processed correctly. 
					for (auto& [_symbol, _count] : symbolMap)
					{
						// Skip processing for empty irrational.
						if(Hashable::Compare(_symbol, IrrationalNumber())) continue;

						// Do the same thing for both numerator and denominator.
						RealNumber realNumerator   = Mathematica::Irrational::ProcessIrrationalSubTree(_symbol.numerator, _count);
						RealNumber realDenominator = Mathematica::Irrational::ProcessIrrationalSubTree(_symbol.denominator, _count);
						
						multiplication.rational *= realNumerator.rational / realDenominator.rational;
						multiplication.irrational.EmplaceBack(realNumerator.irrational[0].numerator, realDenominator.irrational[0].numerator);
					}

					if (multiplication.irrational.Size() == 0) multiplication.irrational.EmplaceBack();

					result.push_back(multiplication);
				}
			}

		
			return ExecuteSimplify(result);
		}

		Vector<RealNumber> ExecuteSimplify(const Vector<RealNumber>& expression)
		{
			Vector<RealNumber> result = {};
			Vector<bool> used(expression.size(), true);

			for (UInt64 i = 0; i < expression.size(); i++)
			{
				RealNumber iReal = expression[i];

				for (UInt64 j = i + 1; j < expression.size() && used[i]; j++)
				{
					RealNumber jReal = expression[j];

					if (Hashable::Compare(iReal.irrational, jReal.irrational) && used[j])
					{
						iReal.rational += jReal.rational;
						used[j] = false;
					}
				}

				used[i] = false;
				result.push_back(iReal);
			}

			return result;
		}
	}
}

RealNumber Mathematica::Irrational::ProcessIrrationalSubTree(const Ref<MathNode>& subTree, const UInt32& counter)
{
	if (!subTree) return RealNumber();

	// Get the function name
	MTH_ASSERT(subTree->type == EMathNodeType::NamedFunction, 
		"Error: Something went wrong, subTree->type should have been NamedFunction. "
		"Perhaps some function did not generate metadata correctly?"
	);

	String functionName = Mathematica::AnyCast<String>(subTree->data);

	// Check which operation generated the irrational tree.
	// The irrational tree has been generated from a root.
	if (functionName == "Raise")
	{
		// Get both argument and exponent.
		RationalNumber argument = Mathematica::AnyCast<RationalNumber>(subTree->children[0]);
		RationalNumber exponent = Mathematica::AnyCast<RationalNumber>(subTree->children[1]);

		// Multiply the exponent with the symbol count .
		exponent *= counter;

		// Delegate the following operation on exponentiate.
		return Mathematica::Operation::Exponentiate(argument, exponent);
	}


	MTH_ASSERT(false, "What kind of sorcery is this?!");
	return RealNumber();
}
