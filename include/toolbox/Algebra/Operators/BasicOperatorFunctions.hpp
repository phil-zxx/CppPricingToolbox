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

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    bool operator==(const MT1& lhs, const MT2& rhs)
    {
        if (lhs.rowCount() != rhs.rowCount() || lhs.colCount() != rhs.colCount())
            return false;

        constexpr bool SO1 = matrix_storage_order_flag_v<MT1>;
        constexpr bool SO2 = matrix_storage_order_flag_v<MT2>;

        if constexpr (SO1 == SO2)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
            {
                if (lhs[i] != rhs[i])
                    return false;
            }
        }
        else
        {
            for (size_t iRow = 0, rowCount = rhs.rowCount(); iRow < rowCount; ++iRow)
                for (size_t iCol = 0, colCount = rhs.colCount(); iCol < colCount; ++iCol)
                    if (lhs(iRow, iCol) != rhs(iRow, iCol))
                        return false;
        }

        return true;
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    bool operator!=(const MT1& lhs, const MT2& rhs)
    {
        return !(lhs == rhs);
    }
}
