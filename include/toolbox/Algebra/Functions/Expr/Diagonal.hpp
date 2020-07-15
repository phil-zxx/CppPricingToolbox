#pragma once

#include <toolbox/Algebra/Expressions/MatrixExprDiagView.hpp>


namespace Toolbox
{
    template<class MT, bool TF = false, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(const MT& arg)
    {
        return MatrixExprDiagView<const MT, TF>(arg);
    }

    template<class MT, bool TF = false, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(MT& arg)
    {
        return MatrixExprDiagView<MT, TF>(arg);
    }
}
