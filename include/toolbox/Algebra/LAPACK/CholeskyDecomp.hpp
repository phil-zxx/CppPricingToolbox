#pragma once

#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    /* Based on https://www.geeksforgeeks.org/cholesky-decomposition-matrix-decomposition */

    template<class MT>
    class CholeskyDecomp
    {
    public:
        MT lowerTriangular;

        explicit CholeskyDecomp(const MT& matrix);
    };

    // Inline Definitions

    template<class MT>
    inline CholeskyDecomp<MT>::CholeskyDecomp(const MT& matrix)
        : lowerTriangular(matrix.shape())
    {
        TB_ENSURE(matrix.size() > 0,   "Input matrix in CholeskyDecomp cannot be empty");
        TB_ENSURE(isSymmetric(matrix), "Only square symmetric matrices are allowed in CholeskyDecomp");

        const size_t n = matrix.rowCount();

        // Decomposing a matrix into Lower Triangular
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j <= i; ++j)
            {
                double sum = 0;

                if (i == j)  // Summation for diagonals
                {
                    for (int k = 0; k < j; k++)
                        sum += lowerTriangular(j, k) * lowerTriangular(j, k);
                    lowerTriangular(j, j) = std::sqrt(matrix(j, j) - sum);
                }
                else
                {
                    // Evaluating L(i, j) using L(j, j)
                    for (size_t k = 0; k < j; ++k)
                        sum += lowerTriangular(i, k) * lowerTriangular(j, k);

                    TB_ENSURE(std::abs(lowerTriangular(j, j)) > 0, "Input matrix in CholeskyDecomp cannot be processed (possibly singular)");

                    lowerTriangular(i, j) = (matrix(i, j) - sum) / lowerTriangular(j, j);
                }
            }
        }
    }
}
