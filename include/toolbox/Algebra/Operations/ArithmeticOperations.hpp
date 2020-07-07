#pragma once


namespace Toolbox
{
    struct OperationAdd
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs + rhs;
        }
    };

    struct OperationSub
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs - rhs;
        }
    };

    struct OperationMul
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs * rhs;
        }
    };

    struct OperationDiv
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs / rhs;
        }
    };

    struct OperationNeg
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return -arg;
        }
    };
}
