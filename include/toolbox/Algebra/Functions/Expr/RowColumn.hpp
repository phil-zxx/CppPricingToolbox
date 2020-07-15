#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprRowColView.hpp>


namespace Toolbox
{
    /* ===== Row Views =====*/

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) row(const MT& arg, size_t rowIdx)
    {
        return MatrixExprRowView<const MT>(arg, rowIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) row(MT& arg, size_t rowIdx)
    {
        return MatrixExprRowView<MT>(arg, rowIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(const MT& arg, size_t rowIdx1, size_t rowIdx2)
    {
        return MatrixExprRowView<const MT>(arg, rowIdx1, rowIdx2);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(MT& arg, size_t rowIdx1, size_t rowIdx2)
    {
        return MatrixExprRowView<MT>(arg, rowIdx1, rowIdx2);
    }


    /* ===== Columns Views =====*/

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) column(const MT& arg, size_t colIdx)
    {
        return MatrixExprColView<const MT>(arg, colIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) column(MT& arg, size_t colIdx)
    {
        return MatrixExprColView<MT>(arg, colIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(const MT& arg, size_t colIdx1, size_t colIdx2)
    {
        return MatrixExprColView<const MT>(arg, colIdx1, colIdx2);
    }
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(MT& arg, size_t colIdx1, size_t colIdx2)
    {
        return MatrixExprColView<MT>(arg, colIdx1, colIdx2);
    }
}
