#pragma once

#include <toolbox/Algebra/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Operations/ArithmeticOperations.hpp>


namespace TB
{
    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator+(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationAdd, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator-(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationSub, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator*(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationMul, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator/(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationDiv, LHS, RHS>(lhs, rhs);
    }

    template<class ARG, class = std::enable_if_t<is_matrix_v<ARG>>>
    decltype(auto) operator-(const ARG& arg)
    {
        return MatrixExprUnary<OperationNeg, ARG>(arg);
    }
}
