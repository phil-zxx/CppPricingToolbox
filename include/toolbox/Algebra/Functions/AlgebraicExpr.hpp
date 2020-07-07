#pragma once

#include <toolbox/Algebra/Typetraits/OpResultClass.hpp>
#include <toolbox/Algebra/Expressions/MatrixExprTrans.hpp>
#include <toolbox/Algebra/Operations/AlgebraicOperations.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) trans(const MT& arg)
    {
        constexpr bool SO = !matrix_storage_order_flag_v<MT>;
        return MatrixExprTrans<OperationId<>, MT, SO>(arg);
    }

    template<class T, class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) asType(const MT& arg)
    {
        return OpResultUnary_t<OperationId<T>, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) abs(const MT& arg)
    {
        return OpResultUnary_t<OperationAbs, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) sqrt(const MT& arg)
    {
        return OpResultUnary_t<OperationSqrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) cbrt(const MT& arg)
    {
        return OpResultUnary_t<OperationCbrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) squared(const MT& arg)
    {
        return OpResultUnary_t<OperationSquared, MT>(arg);
    }

    template<class MT, class ST, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) power(const MT& arg, const ST& n)
    {
        return OpResultBinary_t<OperationPower, MT, ST>(arg, n);
    }
}
