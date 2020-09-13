#pragma once

#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    /* Based on https://www.cs.cornell.edu/~bindel/class/cs6210-f09/lec18.pdf */

    template<size_t R, size_t C>
    class QRDecomp
    {
    public:
        DenseMatrix<double, R, C> matrixQ, matrixR;

        explicit QRDecomp(const DenseMatrix<double, R, C>& matrix);
    };

    // Inline Definitions

    template<size_t R, size_t C>
    inline QRDecomp<R, C>::QRDecomp(const DenseMatrix<double, R, C>& matrix)
        : matrixQ(DenseMatrix<double, R, C>::Identity(matrix.rowCount())),
          matrixR(matrix)
    {
        const size_t rowCount = matrixR.rowCount();
        const size_t colCount = matrixR.colCount();

        for (size_t j = 0; j < colCount; ++j)
        {
            const double colNorm = norm(submatrix(matrixR, j, j, rowCount - j, 1), 2);

            if (colNorm != 0)
            {
                const double Rjj = matrixR(j, j);
                const double s   = Rjj > 0 ? -1 : 1;
                const double u1  = Rjj - s * colNorm;
                const double tau = -s * u1 / colNorm;

                DenseMatrix<double, R, C> w = submatrix(matrixR, j, j, rowCount - j, 1) / u1;
                w(0, 0) = 1;

                rows(matrixR, j)    -= mult(tau * w, mult(trans(w), submatrix(matrixR, j, 0, rowCount - j, colCount)));
                columns(matrixQ, j) -= mult(mult(submatrix(matrixQ, 0, j, rowCount, colCount - j), w), trans(tau * w));

            }
        }
    }
}
