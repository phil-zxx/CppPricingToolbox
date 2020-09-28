#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprDiagView.hpp>


namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(const MT& arg)
    {
        return MatrixExprDiagView<const MT, false>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(MT& arg)
    {
        return MatrixExprDiagView<MT, false>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonalT(const MT& arg)
    {
        return MatrixExprDiagView<const MT, true>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonalT(MT& arg)
    {
        return MatrixExprDiagView<MT, true>(arg);
    }
}
