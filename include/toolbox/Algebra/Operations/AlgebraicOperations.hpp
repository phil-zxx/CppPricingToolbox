#pragma once

#include <cmath>


namespace TB
{
    template<class TypeOut = void>
    struct OperationId
    {
        template<class TypeIn>
        constexpr auto operator()(TypeIn arg) const noexcept
        {
            if constexpr(std::is_same_v<TypeOut, void>)
                return arg;
            else
                return static_cast<TypeOut>(arg);
        }
    };

    struct OperationAbs
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::abs(arg);
        }
    };

    struct OperationSqrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::sqrt(arg);
        }
    };

    struct OperationCbrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::cbrt(arg);
        }
    };

    struct OperationSquared
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return arg * arg;
        }
    };

    struct OperationPower
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 arg, Type2 n) const noexcept
        {
            return std::pow(arg, n);
        }
    };
}
