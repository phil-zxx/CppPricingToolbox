#pragma once

#include <toolbox/Algebra/Types/DenseVector.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorFunctions.hpp>
#include <toolbox/Algebra/Operators/AlgebraicOperatorFunctions.hpp>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF = false>
    using StaticVector = DenseVector<Type, Size, TF>;

    template<class Type, bool TF = false>
    using DynamicVector = DenseVector<Type, DynamicSize, TF>;
}
