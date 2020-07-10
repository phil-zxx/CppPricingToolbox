#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/VectorMatrix.hpp>


namespace Toolbox
{
    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1>&& is_matrix_v<MT2>>>
    decltype(auto) mult(const MT1& lhs, const MT2& rhs)
    {
        const size_t rowCountL = lhs.rowCount();
        const size_t colCountL = lhs.colCount();
        const size_t rowCountR = rhs.rowCount();
        const size_t colCountR = rhs.colCount();
        TB_ENSURE(colCountL == rowCountR, "Need lhs matrix column count (" << colCountL << ") to be equal to rhs matrix row count (" << rowCountR << ") when multiplying");

        using ET = OpResultType_t<OperationMul, ElementType_t<MT1>, ElementType_t<MT2>>;
        DynamicMatrix<ET> result(rowCountL, colCountR, 0.);

        for (size_t k = 0; k < colCountR; ++k)
        {
            for (size_t i = 0; i < rowCountL; ++i)
            {
                for (size_t j = 0; j < colCountL; ++j)
                    result(i, k) += lhs(i, j) * rhs(j, k);
            }
        }

        return result;
    }
}
