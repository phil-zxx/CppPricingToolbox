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

    template<class ARG, class = std::enable_if_t<is_unary_op_valid_v<ARG>>>
    decltype(auto) operator-(const ARG& arg)
    {
        return OpResultUnary_t<OperatorNeg, ARG>(arg);
    }

    template<class VT1, class VT2, class = std::enable_if_t<is_vector_v<VT1> && is_vector_v<VT2>>>
    bool operator==(const VT1& lhs, const VT2& rhs)
    {
        if (lhs.size() != rhs.size() || lhs.transposeFlag != rhs.transposeFlag)
            return false;
    
        for (size_t i = 0, size = lhs.size(); i < size; ++i)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
    
        return true;
    }

    template<class VT1, class VT2, class = std::enable_if_t<is_vector_v<VT1> && is_vector_v<VT2>>>
    bool operator!=(const VT1& lhs, const VT2& rhs)
    {
        return !(lhs == rhs);
    }
}
