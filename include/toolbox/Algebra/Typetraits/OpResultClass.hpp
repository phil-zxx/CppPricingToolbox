#pragma once

#include <toolbox/Algebra/Operators/Expressions/VectorExpr.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    /* ========== vector_transpose_flag ========== */
    template<class ARG>
    struct vector_transpose_flag
    {
        template<class VT> constexpr static std::true_type test(Vector<VT, true>*);
        template<class VT> constexpr static std::false_type test(Vector<VT, false>*);
        constexpr static std::false_type test(void*);

        constexpr static bool value = decltype(test(std::declval<ARG*>()))::value;
    };

    template<class ARG>
    constexpr bool vector_transpose_flag_v = vector_transpose_flag<ARG>::value;


    /* ========== matrix_storage_order_flag ========== */
    template<class ARG>
    struct matrix_storage_order_flag
    {
        template<class MT> constexpr static std::true_type test(Matrix<MT, true>*);
        template<class MT> constexpr static std::false_type test(Matrix<MT, false>*);
        constexpr static std::false_type test(void*);

        constexpr static bool value = decltype(test(std::declval<ARG*>()))::value;
    };

    template<class ARG>
    constexpr bool matrix_storage_order_flag_v = matrix_storage_order_flag<ARG>::value;


    /* ========== OpResultUnary ========== */
    template<class OP, class ARG>
    struct OpResultUnary
    {
        using type = VectorExprUnary<OP, ARG, ARG::transposeFlag>;

        static_assert(is_vector_v<ARG>, "In an unary operation, need input to be a vector type");
    };

    template<class OP, class ARG>
    using OpResultUnary_t = typename OpResultUnary<OP, ARG>::type;


    /* ========== OpResultBinary ========== */
    template<class OP, class LHS, class RHS, bool ElementWise = true>
    struct OpResultBinary
    {
        using Combined = std::conditional_t<is_vector_v<LHS>, LHS, RHS>;

        constexpr static bool TF    = vector_transpose_flag_v<Combined>;
        constexpr static bool lhsTF = vector_transpose_flag_v<LHS>;
        constexpr static bool rhsTF = vector_transpose_flag_v<RHS>;

        using type = VectorExprBinary<OP, LHS, RHS, TF>;

        static_assert(is_vector_v<LHS> || is_vector_v<RHS>,
            "In a binary operation, at least one argument must be a vector type");
        static_assert(!(ElementWise && is_vector_v<LHS> && is_vector_v<RHS> && lhsTF != rhsTF),
            "In an elementwise-binary operation, both vectors must have same transpose flag");
    };

    template<class OP, class LHS, class RHS>
    using OpResultBinary_t = typename OpResultBinary<OP, LHS, RHS>::type;
}
