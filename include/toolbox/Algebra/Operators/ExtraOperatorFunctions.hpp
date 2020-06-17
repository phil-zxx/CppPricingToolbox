#pragma once

#include <toolbox/Algebra/Typetraits/OpResultClass.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorClasses.hpp>


namespace Toolbox
{
    namespace detail
    {
        template<class T, class U, bool isFloatingPoint = std::is_floating_point_v<T> || std::is_floating_point_v<U>>
        bool isApproxNotEqual(const T& lhs, const U& rhs)
        {
            if constexpr (isFloatingPoint)
            {
                return std::abs(lhs - rhs) > 1.e-14;
            }
            else
            {
                return lhs != rhs;
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
                if (detail::isApproxNotEqual(lhs[i], rhs[i]))
                    return false;
            }
        }
        else
        {
            for (size_t iRow = 0, rowCount = rhs.rowCount(); iRow < rowCount; ++iRow)
            {
                for (size_t iCol = 0, colCount = rhs.colCount(); iCol < colCount; ++iCol)
                {
                    if (detail::isApproxNotEqual(lhs(iRow, iCol), rhs(iRow, iCol)))
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
                if (detail::isApproxNotEqual(arg(i, j), arg(j, i)))
                    return false;
            }
        }

        return true;
    }
}
