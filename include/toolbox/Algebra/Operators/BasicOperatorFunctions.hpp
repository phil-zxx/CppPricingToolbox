#pragma once

#include <toolbox/Algebra/Typetraits/OpResultClass.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorClasses.hpp>


namespace Toolbox
{
    template<class LHS, class RHS, class = std::enable_if_t<is_binary_op_valid_v<LHS, RHS>>>
    decltype(auto) operator+(const LHS& lhs, const RHS& rhs)
    {
        return OpResultBinary_t<OperatorAdd, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<is_binary_op_valid_v<LHS, RHS>>>
    decltype(auto) operator-(const LHS& lhs, const RHS& rhs)
    {
        return OpResultBinary_t<OperatorSub, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<is_binary_op_valid_v<LHS, RHS>>>
    decltype(auto) operator*(const LHS& lhs, const RHS& rhs)
    {
        return OpResultBinary_t<OperatorMul, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<is_binary_op_valid_v<LHS, RHS>>>
    decltype(auto) operator/(const LHS& lhs, const RHS& rhs)
    {
        return OpResultBinary_t<OperatorDiv, LHS, RHS>(lhs, rhs);
    }

    template<class ARG, class = std::enable_if_t<is_matrix_v<ARG>>>
    decltype(auto) operator-(const ARG& arg)
    {
        return OpResultUnary_t<OperatorNeg, ARG>(arg);
    }
}
