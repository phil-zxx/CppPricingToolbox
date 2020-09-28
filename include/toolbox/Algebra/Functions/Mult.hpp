#pragma once

#include <toolbox/Algebra/Types/DenseMatrix.hpp>


namespace TB
{
    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) mult(const MT1& lhs, const MT2& rhs)
    {
        const size_t rowCountL = lhs.rowCount();
        const size_t colCountL = lhs.colCount();
        const size_t rowCountR = rhs.rowCount();
        const size_t colCountR = rhs.colCount();
        TB_ENSURE(colCountL == rowCountR, "Need lhs matrix column count (" << colCountL << ") to be equal to rhs matrix row count (" << rowCountR << ") when multiplying");

        using ET = OpResultType_t<OperationMul, MT1, MT2>;
        DenseMatrix<ET, DynamicSize, DynamicSize> result(rowCountL, colCountR, 0);

        for (size_t iCol = 0; iCol < colCountR; ++iCol)
        {
            for (size_t iRow = 0; iRow < rowCountL; ++iRow)
            {
                for (size_t j = 0; j < colCountL; ++j)
                    result(iRow, iCol) += lhs(iRow, j) * rhs(j, iCol);
            }
        }

        return result;
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) multWithDiagonal(const MT1& lhs, const MT2& rhs)
    {
        const size_t rowCountL = lhs.rowCount();
        const size_t colCountL = lhs.colCount();
        const size_t sizeR     = rhs.size();
        TB_ENSURE(rhs.rowCount() == 1 || rhs.colCount() == 1, "Need rhs to be a row or column vector, but have dimensions " << rhs.rowCount() << "x" << rhs.colCount() << "");
        TB_ENSURE(colCountL == sizeR,                         "Need lhs matrix column count (" << colCountL << ") to be equal to rhs vector size (" << sizeR << ") when multiplying");

        using ET = OpResultType_t<OperationMul, MT1, MT2>;
        DenseMatrix<ET, DynamicSize, DynamicSize> result(rowCountL, sizeR, 0);

        for (size_t k = 0; k < sizeR; ++k)
        {
            for (size_t i = 0; i < rowCountL; ++i)
            {
                result(i, k) += lhs(i, k) * rhs[k];
            }
        }

        return result;
    }
}
