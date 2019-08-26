#pragma once


namespace Toolbox
{
    struct ResultType
    {
        template<class T1, class T2> using Add = decltype(std::declval<T1>() + std::declval<T2>());
        template<class T1, class T2> using Sub = decltype(std::declval<T1>() - std::declval<T2>());
        template<class T1, class T2> using Mul = decltype(std::declval<T1>() * std::declval<T2>());
        template<class T1, class T2> using Div = decltype(std::declval<T1>() / std::declval<T2>());
    };
}
