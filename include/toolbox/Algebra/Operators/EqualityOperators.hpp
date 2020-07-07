#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    namespace detail
    {
        template<class T, class U, bool isFloatingPoint = std::is_floating_point_v<T> || std::is_floating_point_v<U>>
        bool isApproxEqual(const T& lhs, const U& rhs)
        {
            if constexpr (isFloatingPoint)
            {
                return std::abs(lhs - rhs) < 1.e-13;
            }
            else
            {
                return lhs == rhs;
            }
        }
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    bool operator==(const MT1& lhs, const MT2& rhs)
    {
        if (lhs.rowCount() != rhs.rowCount() || lhs.colCount() != rhs.colCount())
            return false;

        constexpr bool haveSameSO = matrix_storage_order_flag_v<MT1> == matrix_storage_order_flag_v<MT2>;

        if constexpr (haveSameSO)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
            {
                if (detail::isApproxEqual(lhs[i], rhs[i]) == false)
                    return false;
            }
        }
        else
        {
            for (size_t iRow = 0, rowCount = rhs.rowCount(); iRow < rowCount; ++iRow)
            {
                for (size_t iCol = 0, colCount = rhs.colCount(); iCol < colCount; ++iCol)
                {
                    if (detail::isApproxEqual(lhs(iRow, iCol), rhs(iRow, iCol)) == false)
                        return false;
                }
            }
        }

        return true;
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    bool operator!=(const MT1& lhs, const MT2& rhs)
    {
        return !(lhs == rhs);
    }
}
