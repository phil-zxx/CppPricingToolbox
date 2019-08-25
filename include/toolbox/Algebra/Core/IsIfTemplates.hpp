#pragma once

#include <type_traits>


namespace Toolbox
{
    template<class T, T N>
    struct IntegralConstant : public std::integral_constant<T, N>
    {
        using ValueType = T;
        using Type      = IntegralConstant<T, N>;
    };

    template<bool B>
    using BoolConstant = IntegralConstant<bool, B>;
    
    using FalseType = BoolConstant<false>;
    using TrueType  = BoolConstant<true>;

    /* ========== IsBuiltin ==========*/

    template<class T>
    struct IsBuiltin : public BoolConstant<std::is_fundamental<T>::value> {};
    
    template<typename T>
    constexpr bool IsBuiltin_v = IsBuiltin<T>::value;


    /* ========== IsBoolean ==========*/

    template<class T> struct IsBoolean : public FalseType {};

    template<>
    struct IsBoolean<bool> : public TrueType {};

    template<>
    struct IsBoolean<const bool> : public TrueType {};

    template<>
    struct IsBoolean<volatile bool> : public TrueType {};

    template<>
    struct IsBoolean<const volatile bool> : public TrueType {};

    template<class T>
    constexpr bool IsBoolean_v = IsBoolean<T>::value;


    /* ========== IsVoid ==========*/

    template<class T>
    struct IsVoid : public BoolConstant<std::is_void<T>::value> {};

    template<class T>
    constexpr bool IsVoid_v = IsVoid<T>::value;


    /* ========== IsNumeric ==========*/

    template<class T>
    struct IsNumeric : public BoolConstant<IsBuiltin_v<T> && !IsBoolean_v<T> && !IsVoid_v<T>> {};

    template<class T>
    constexpr bool IsNumeric_v = IsNumeric<T>::value;


    /* ========== EnableIf ==========*/
    
    template<bool Condition, typename T = void>
    struct EnableIf
    {
        using Type = T;
    };

    template<typename T>
    struct EnableIf<false, T> {};

    template<bool Condition, typename T = void>
    using EnableIf_t = typename EnableIf<Condition, T>::Type;
}
