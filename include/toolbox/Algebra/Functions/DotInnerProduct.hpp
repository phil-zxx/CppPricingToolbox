#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Expressions/SumExprBinary.hpp>


namespace TB
{
    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) dot(const MT1& lhs, const MT2& rhs)
    {
        return SumExprBinary<OperationMul, MT1, MT2>::evaluate(lhs, rhs);
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) innerProduct(const MT1& lhs, const MT2& rhs)
    {
        TB_ENSURE(lhs.rowCount() == 1 && rhs.colCount() == 1 && lhs.colCount() == rhs.rowCount(), "Inner-product requires LHS to be a row vector (1 x M) and RHS to be a column vector (M x 1)");

        return dot(lhs, rhs);
    }
}
