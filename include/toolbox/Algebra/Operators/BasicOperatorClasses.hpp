#pragma once


namespace Toolbox
{
    struct OperatorAdd
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs + rhs;
        }
    };

    struct OperatorSub
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs - rhs;
        }
    };

    struct OperatorMul
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs * rhs;
        }
    };

    struct OperatorDiv
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs / rhs;
        }
    };

    struct OperatorNeg
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return -arg;
        }
    };

    template<class TypeOut = void>
    struct OperatorId
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

    struct OperatorAbs
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::abs(arg);
        }
    };

    struct OperatorSqrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::sqrt(arg);
        }
    };

    struct OperatorCbrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::cbrt(arg);
        }
    };

    struct OperatorSquared
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return arg * arg;
        }
    };

    struct OperatorPower
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 arg, Type2 n) const noexcept
        {
            return std::pow(arg, n);
        }
    };
}
