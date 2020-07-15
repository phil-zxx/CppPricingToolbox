#pragma once

#include <toolbox/Algebra/Types/DenseVector.hpp>
#include <toolbox/Algebra/Types/DenseMatrix.hpp>

#include <toolbox/Algebra/Operators/ArithmeticOperators.hpp>
#include <toolbox/Algebra/Operators/EqualityOperators.hpp>

#include <toolbox/Algebra/Functions/Expr/Algebraic.hpp>
#include <toolbox/Algebra/Functions/Expr/Diagonal.hpp>
#include <toolbox/Algebra/Functions/Expr/RowColumn.hpp>
#include <toolbox/Algebra/Functions/DotInnerProduct.hpp>
#include <toolbox/Algebra/Functions/IsSquareSymmetric.hpp>
#include <toolbox/Algebra/Functions/MinMax.hpp>
#include <toolbox/Algebra/Functions/Mult.hpp>
#include <toolbox/Algebra/Functions/SumProd.hpp>
#include <toolbox/Algebra/Functions/SwapRowsCols.hpp>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF = false>
    using StaticVector = DenseVector<Type, Size, TF>;

    template<class Type, bool TF = false>
    using DynamicVector = DenseVector<Type, DynamicSize, TF>;

    template<class Type, size_t Rows, size_t Cols>
    using StaticMatrix = DenseMatrix<Type, Rows, Cols>;

    template<class Type>
    using DynamicMatrix = DenseMatrix<Type, DynamicSize, DynamicSize>;
}
