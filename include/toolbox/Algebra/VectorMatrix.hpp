#pragma once

#include <toolbox/Algebra/Types/DenseVector.hpp>
#include <toolbox/Algebra/Types/DenseMatrix.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorFunctions.hpp>
#include <toolbox/Algebra/Operators/AlgebraicOperatorFunctions.hpp>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF = false>
    using StaticVector = DenseVector<Type, Size, TF>;

    template<class Type, bool TF = false>
    using DynamicVector = DenseVector<Type, DynamicSize, TF>;

    template<class Type, size_t Rows, size_t Cols, bool SO = false>
    using StaticMatrix = DenseMatrix<Type, Rows, Cols, SO>;

    template<class Type, bool SO = false>
    using DynamicMatrix = DenseMatrix<Type, DynamicSize, DynamicSize, SO>;
}
