#pragma once

#include <toolbox/Algebra/Typetraits/OpResultType.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace TB
{
    template <class OP, class LHS, class RHS, class = std::enable_if_t<is_matrix_v<LHS> && is_matrix_v<RHS>>>
    struct SumExprBinary
    {
        constexpr static decltype(auto) evaluate(const LHS& lhs, const RHS& rhs)
        {
            constexpr OP pairwiseOperation;

            if (lhs.size() != rhs.size())
                throw("Vector sizes do not match");

            using ElementType = OpResultType_t<OP, LHS, RHS>;

            const size_t N = lhs.size();
            if (N == 0)
                return ElementType(0);

            ElementType totalSum = pairwiseOperation(lhs[0], rhs[0]);
            for (size_t i = 1; i < N; ++i)
                totalSum += pairwiseOperation(lhs[i], rhs[i]);

            return totalSum;
        }
    };

    template <class OP, class VT1, class VT2>
    using SumExprBinary_t = SumExprBinary<OP, VT1, VT2>;
}
