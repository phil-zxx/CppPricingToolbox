#pragma once

#include <toolbox/Algebra/Operators/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    /* ========== OpResultUnary ========== */
    template<class OP, class ARG>
    struct OpResultUnary
    {
        using type = MatrixExprUnary<OP, ARG, ARG::storageOrder>;

        static_assert(is_matrix_v<ARG>, "In an unary operation, need input to be a matrix type");
    };

    template<class OP, class ARG>
    using OpResultUnary_t = typename OpResultUnary<OP, ARG>::type;


    /* ========== OpResultBinary ========== */
    template<class OP, class LHS, class RHS>
    struct OpResultBinary
    {
        constexpr static bool lhsSO = matrix_storage_order_flag_v<LHS>;
        constexpr static bool rhsSO = matrix_storage_order_flag_v<RHS>;
        constexpr static bool SO    = if_v<is_matrix_v<LHS>, bool, lhsSO, rhsSO>;

        using type = MatrixExprBinary<OP, LHS, RHS, SO>;

        static_assert(is_matrix_v<LHS> || is_matrix_v<RHS>,
            "In an binary operation, at least one argument must be a matrix type");

        static_assert(!(is_matrix_v<LHS> && is_matrix_v<RHS> && lhsSO != rhsSO),
            "In an binary operation, both matrices must have same storage-order flag");
    };

    template<class OP, class LHS, class RHS>
    using OpResultBinary_t = typename OpResultBinary<OP, LHS, RHS>::type;
}
