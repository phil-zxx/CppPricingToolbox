#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>
#include <toolbox/Algebra/Expressions/ExprVecVecMap.hpp>


namespace Toolbox
{
    struct OperationBinary
    {

    };

    struct OperationBinaryAdd : public OperationBinary
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs + rhs;
        }
    };

    struct OperationBinarySub : public OperationBinary
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs - rhs;
        }
    };

    struct OperationBinaryMul : public OperationBinary
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs * rhs;
        }
    };

    struct OperationBinaryDiv : public OperationBinary
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs / rhs;
        }
    };
}
