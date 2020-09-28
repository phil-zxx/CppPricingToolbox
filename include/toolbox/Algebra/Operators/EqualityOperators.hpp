#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace TB
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

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    bool operator==(const LHS& lhs, const RHS& rhs)
    {
        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            if (lhs.shape() != rhs.shape())
                return false;
        }

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs[i], rhs[i]) == false)
                    return false;
        }
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs[i], rhs) == false)
                    return false;
        }
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs, rhs[i]) == false)
                    return false;
        }

        return true;
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    bool operator!=(const LHS& lhs, const RHS& rhs)
    {
        return !(lhs == rhs);
    }
}
