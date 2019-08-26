#pragma once

#include <toolbox/Algebra/Core/Vector.hpp>
#include <toolbox/Algebra/Core/ResultType.hpp>
#include <toolbox/Algebra/Expressions/ExprVecTransposed.hpp>
#include <toolbox/Algebra/Operations/Classes/AlgebraOperations.hpp>

#include <numeric>


namespace Toolbox
{
    template<class VT, bool TF>
    inline decltype(auto) transpose(const Vector<VT, TF>& vector)
    {
        return ExprVecTransposed<VT, !TF>(~vector);
    }

    template<class VT, bool TF>
    inline decltype(auto) abs(const Vector<VT, TF>& vector)
    {
        return ExprVecMap(~vector, OperationAlgebraicAbs{});
    }

    template<class VT1, bool TF1, class VT2, bool TF2>
    inline decltype(auto) dot(const Vector<VT1, TF1>& lhs, const Vector<VT2, TF2>& rhs)
    {
        using ElementType = ResultType::Add<VT1::ElementType, VT2::ElementType>;
        return std::inner_product((~lhs).begin(), (~lhs).end(), (~rhs).begin(), ElementType(0));
    }
}
