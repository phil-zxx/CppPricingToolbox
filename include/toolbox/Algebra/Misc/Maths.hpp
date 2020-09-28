#pragma once

#include <limits>


namespace TB
{
    template<class T>
    T TB_min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    template<class T>
    T TB_min(const T a, const T b, const T c)
    {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    template<class T>
    T TB_max(const T a, const T b)
    {
        return a > b ? a : b;
    }

    template<class T>
    T TB_max(const T a, const T b, const T c)
    {
        return a > b ? (a > c ? a : c) : (b > c ? b : c);
    }

    constexpr double TB_INF_NEG = -std::numeric_limits<double>::infinity();
    constexpr double TB_INF_POS = std::numeric_limits<double>::infinity();
    constexpr double TB_EPS     = std::numeric_limits<double>::epsilon();
    constexpr double TB_NAN     = std::numeric_limits<double>::quiet_NaN();
    constexpr double TB_ZERO    = std::numeric_limits<double>::min();
}
