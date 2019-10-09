#pragma once

#include <type_traits>


namespace Toolbox
{
    /* ========== RemoveCVRef ==========*/

    template<class T >
    struct RemoveCVRef
    {
        using Type = typename std::remove_cv<typename std::remove_reference<T>::type >::type;
    };

    template<class T >
    using RemoveCVRef_t = typename RemoveCVRef<T>::Type;


    /* ========== is_boolean ==========*/

    template<class T>
    constexpr bool is_boolean_v = std::is_same_v<bool, RemoveCVRef_t<T>>;


    /* ========== is_numeric ==========*/

    template<class T>
    constexpr bool is_numeric_v = std::bool_constant<std::is_arithmetic_v<T> && !is_boolean_v<T>>::value;
}
