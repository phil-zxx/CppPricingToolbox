#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprRowCol.hpp>
#include <toolbox/Algebra/Expressions/MatrixExprDiag.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) row(const MT& arg, size_t rowIdx)
    {
        return MatrixExprRow<MT>(arg, rowIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) column(const MT& arg, size_t colIdx)
    {
        return MatrixExprCol<MT>(arg, colIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(const MT& arg)
    {
        return MatrixExprDiag<MT>(arg);
    }
}
