#pragma once

#include <toolbox/Algebra/Operators/EqualityOperators.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) isSquare(const MT& arg)
    {
        return arg.rowCount() == arg.colCount();
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) isSymmetric(const MT& arg)
    {
        if (!isSquare(arg))
            return false;

        const size_t n = arg.colCount();
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (detail::isApproxEqual(arg(i, j), arg(j, i)) == false)
                    return false;
            }
        }

        return true;
    }
}
