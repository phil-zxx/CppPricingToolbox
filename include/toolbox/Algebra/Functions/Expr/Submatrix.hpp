#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprSubmatrix.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(const MT& arg, const size_t& rowIdx1, const size_t& rowIdx2, const size_t& colIdx1, const size_t& colIdx2)
    {
        return MatrixExprSubmatrixView<const MT>(arg, rowIdx1, rowIdx2, colIdx1, colIdx2);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(MT& arg, const size_t& rowIdx1, const size_t& rowIdx2, const size_t& colIdx1, const size_t& colIdx2)
    {
        return MatrixExprSubmatrixView<MT>(arg, rowIdx1, rowIdx2, colIdx1, colIdx2);
    }
}
