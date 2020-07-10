#pragma once

#include <toolbox/Algebra/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    /* ========== OpResultUnary ========== */
    template<class OP, class ARG>
    struct OpResultUnary
    {
        using type = MatrixExprUnary<OP, ARG>;

        static_assert(is_matrix_v<ARG>, "In an unary operation, need input to be a matrix type");
    };

    template<class OP, class ARG>
    using OpResultUnary_t = typename OpResultUnary<OP, ARG>::type;


    /* ========== OpResultBinary ========== */
    template<class OP, class LHS, class RHS>
    struct OpResultBinary
    {
        using type = MatrixExprBinary<OP, LHS, RHS>;

        static_assert(is_matrix_v<LHS> || is_matrix_v<RHS>,
            "In an binary operation, at least one argument must be a matrix type");
    };

    template<class OP, class LHS, class RHS>
    using OpResultBinary_t = typename OpResultBinary<OP, LHS, RHS>::type;
}
