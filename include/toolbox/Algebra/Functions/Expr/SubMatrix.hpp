#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprSubMatrix.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) subMatrix(const MT& arg, const size_t& rowIdx1, const size_t& rowIdx2, const size_t& colIdx1, const size_t& colIdx2)
    {
        return MatrixExprSubMatrixView<const MT>(arg, rowIdx1, rowIdx2, colIdx1, colIdx2);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) subMatrix(MT& arg, const size_t& rowIdx1, const size_t& rowIdx2, const size_t& colIdx1, const size_t& colIdx2)
    {
        return MatrixExprSubMatrixView<MT>(arg, rowIdx1, rowIdx2, colIdx1, colIdx2);
    }
}
