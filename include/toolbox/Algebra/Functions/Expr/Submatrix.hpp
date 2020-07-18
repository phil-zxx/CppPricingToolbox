#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprSubmatrix.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(const MT& arg, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
    {
        return MatrixExprSubmatrixView<const MT>(arg, rowIdx, colIdx, rowSize, colSize);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(MT& arg, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
    {
        return MatrixExprSubmatrixView<MT>(arg, rowIdx, colIdx, rowSize, colSize);
    }
}
