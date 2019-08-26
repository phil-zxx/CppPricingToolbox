#pragma once

#include <toolbox/Algebra/Core/Vector.hpp>
#include <toolbox/Algebra/Expressions/ExprVecVecMap.hpp>


namespace Toolbox
{
    struct OperationAlgebraic
    {

    };

    struct OperationAlgebraicId : public OperationAlgebraic
    {
        template<class Type>
        constexpr auto operator()(Type val) const noexcept
        {
            return val;
        }
    };

    struct OperationAlgebraicAbs : public OperationAlgebraic
    {
        template<class Type>
        constexpr auto operator()(Type val) const noexcept
        {
            return std::abs(val);
        }
    };
}
