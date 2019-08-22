#pragma once


namespace Toolbox
{
    template<class ST>
    struct OperationUnary
    {
        constexpr explicit OperationUnary(ST scalar) noexcept
            : scalar(scalar) { }

        const ST scalar;
    };

    template<class ST>
    struct OperationUnaryAdd : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type val) const noexcept
        {
            return val + scalar;
        }
    };

    template<class ST>
    struct OperationUnarySubLhs : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type lhs) const noexcept
        {
            return lhs - scalar;
        }
    };

    template<class ST>
    struct OperationUnarySubRhs : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type rhs) const noexcept
        {
            return scalar - rhs;
        }
    };

    template<class ST>
    struct OperationUnaryMul : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type val) const noexcept
        {
            return val * scalar;
        }
    };

    template<class ST>
    struct OperationUnaryDivLhs : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type lhs) const noexcept
        {
            return lhs / scalar;
        }
    };

    template<class ST>
    struct OperationUnaryDivRhs : public OperationUnary<ST>
    {
        using OperationUnary::OperationUnary;

        template<class Type>
        constexpr auto operator()(Type rhs) const noexcept
        {
            return scalar / rhs;
        }
    };
}
