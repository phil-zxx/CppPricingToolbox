#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    /* ========== apply_unary ========== */
    template<class OP, class LHS>
    decltype(auto) apply_unary(const LHS& lhs, size_t idx)
    {
        constexpr OP operation;

        return operation(lhs[idx]);
    }
    
    template<class OP, class LHS>
    decltype(auto) apply_unary(const LHS& lhs, size_t rowIdx, size_t colIdx)
    {
        constexpr OP operation;

        return operation(lhs(rowIdx, colIdx));
    }


    /* ========== apply_binary ========== */
    template<class OP, class LHS, class RHS>
    decltype(auto) apply_binary(const LHS& lhs, const RHS& rhs, size_t idx)
    {
        constexpr OP operation;

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs[idx], rhs[idx]);
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
            return operation(lhs[idx], rhs);
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs, rhs[idx]);
        else
            static_assert(false_template<OP, LHS, RHS>::value, "Need at least one input to be a matrix");
    }

    template<class OP, class LHS, class RHS>
    decltype(auto) apply_binary(const LHS& lhs, const RHS& rhs, size_t rowIdx, size_t colIdx)
    {
        constexpr OP operation;

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs(rowIdx, colIdx), rhs(rowIdx, colIdx));
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
            return operation(lhs(rowIdx, colIdx), rhs);
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs, rhs(rowIdx, colIdx));
        else
            static_assert(false_template<OP, LHS, RHS>::value, "Need at least one input to be a matrix");
    }
}
