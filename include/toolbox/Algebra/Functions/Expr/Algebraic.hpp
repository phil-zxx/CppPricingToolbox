#pragma once

#include <toolbox/Algebra/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Expressions/MatrixExprTrans.hpp>
#include <toolbox/Algebra/Expressions/MatrixExprReshape.hpp>
#include <toolbox/Algebra/Operations/AlgebraicOperations.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) trans(const MT& arg)
    {
        return MatrixExprTrans<MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) reshape(const MT& arg, const size_t& rowCount, const size_t& colCount)
    {
        return MatrixExprReshape<MT>(arg, rowCount, colCount);
    }

    template<class T, class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) asType(const MT& arg)
    {
        return MatrixExprUnary<OperationId<T>, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) abs(const MT& arg)
    {
        return MatrixExprUnary<OperationAbs, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) sqrt(const MT& arg)
    {
        return MatrixExprUnary<OperationSqrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) cbrt(const MT& arg)
    {
        return MatrixExprUnary<OperationCbrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) squared(const MT& arg)
    {
        return MatrixExprUnary<OperationSquared, MT>(arg);
    }

    template<class MT, class ST, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) power(const MT& arg, const ST& n)
    {
        return MatrixExprBinary<OperationPower, MT, ST>(arg, n);
    }
}
