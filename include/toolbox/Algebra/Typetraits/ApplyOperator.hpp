#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    /* ========== apply_unary ========== */
    template<class OP, class LHS>
    auto apply_unary(const LHS& lhs, size_t i)
    {
        constexpr OP operation;

        return operation(lhs[i]);
    }


    /* ========== apply_binary ========== */
    template<class OP, class LHS, class RHS>
    auto apply_binary(const LHS& lhs, const RHS& rhs, size_t i)
    {
        constexpr OP operation;

        if constexpr (is_vector_v<LHS>&& is_vector_v<RHS>)
            return operation(lhs[i], rhs[i]);
        else if constexpr (is_vector_v<LHS> && !is_vector_v<RHS>)
            return operation(lhs[i], rhs);
        else if constexpr (!is_vector_v<LHS>&& is_vector_v<RHS>)
            return operation(lhs, rhs[i]);
        else
            static_assert(false, "Need at least one input to be a vector");
    }
}
