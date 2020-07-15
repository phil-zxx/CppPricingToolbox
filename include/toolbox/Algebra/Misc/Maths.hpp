#pragma once


namespace Toolbox
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
        return a > b ? (a > c ? a : c) : (b > c ? b : c)
    }
}
