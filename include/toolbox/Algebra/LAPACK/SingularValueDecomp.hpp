#pragma once

#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/JacobiRotation.hpp>


namespace TB
{
    /* Based on https://gitlab.com/libeigen/eigen/-/blob/master/Eigen/src/SVD/JacobiSVD.h */

    template<size_t R, size_t C>
    class SingularValueDecomp
    {
        using DenseVectorType = DenseVector<double, R == DynamicSize ? DynamicSize : (R < C ? R : C), false>;

    public:
        DenseMatrix<double, R, C> matrixU, matrixV, invertedMatrix;
        DenseVectorType singularValues;

        explicit SingularValueDecomp(const DenseMatrix<double, R, C>& matrix);

        DenseVectorType solve(const DenseVectorType& y) const;

    private:
        static void JacobiSVD2x2(const DenseMatrix<double, R, C>& matrix, const size_t& p, const size_t& q, JacobiRotation& j_left, JacobiRotation& j_right);
    };

    // Inline Definitions

    template<size_t R, size_t C>
    inline SingularValueDecomp<R, C>::SingularValueDecomp(const DenseMatrix<double, R, C>& matrix)
        : matrixU(DenseMatrix<double, R, C>::Identity(TB_min(matrix.rowCount(), matrix.colCount()))),
          matrixV(DenseMatrix<double, R, C>::Identity(TB_min(matrix.rowCount(), matrix.colCount()))),
          invertedMatrix(),
          singularValues(TB_min(matrix.rowCount(), matrix.colCount()))
    {
        constexpr double precision = 2.0 * TB_EPS;

        // Scaling factor to reduce over/under-flows
        double scale = maxEl(abs(matrix));
        if (scale == 0.)
            return;

        /*** step 1. The R-SVD step: we use a QR decomposition to reduce to the case of a square matrix */
        DenseMatrix<double, R, C> workMatrix = matrix / scale;

        /*** step 2. The main Jacobi SVD iteration. ***/
        double maxDiagEntry = maxEl(abs(diagonal(workMatrix)));
        const size_t mSize  = diagonal(workMatrix).size();

        bool finished = false;
        while (!finished)
        {
            finished = true;

            // do a sweep: for all index pairs (p,q), perform SVD of the corresponding 2x2 sub-matrix
            for (size_t p = 1; p < mSize; ++p)
            {
                for (size_t q = 0; q < p; ++q)
                {
                    // if this 2x2 sub-matrix is not diagonal already...
                    // notice that this comparison will evaluate to false if any NaN is involved, ensuring that NaN's don't
                    // keep us iterating forever. Similarly, small denormal numbers are considered zero.
                    const double threshold = TB_max(TB_ZERO, precision * maxDiagEntry);
                    if (std::abs(workMatrix(p, q)) > threshold || std::abs(workMatrix(q, p)) > threshold)
                    {
                        finished = false;
                        // perform SVD decomposition of 2x2 sub-matrix corresponding to indices p,q to make it diagonal
                        JacobiRotation j_left, j_right;
                        JacobiSVD2x2(workMatrix, p, q, j_left, j_right);

                        j_left.rotateMatrixFromLeft(p, q, workMatrix);
                        j_left.transposed().rotateMatrixFromRight(p, q, matrixU);

                        j_right.rotateMatrixFromRight(p, q, workMatrix);
                        j_right.rotateMatrixFromRight(p, q, matrixV);

                        // keep track of the largest diagonal coefficient
                        maxDiagEntry = TB_max(maxDiagEntry, std::abs(workMatrix(p, p)), std::abs(workMatrix(q, q)));
                    }
                }
            }
        }

        /*** step 3. The work matrix is now diagonal, so ensure it's positive so its diagonal entries are the singular values ***/
        for (size_t i = 0; i < mSize; ++i)
        {
            const double a    = workMatrix(i, i);
            singularValues[i] = std::abs(a);
            if (a < 0.)
                column(matrixU, i) *= -1.;
        }

        singularValues *= scale;

        /*** step 4. Sort singular values in descending order and compute the number of nonzero singular values ***/
        for (size_t i = 0; i < mSize; i++)
        {
            size_t pos = argMaxFrom(singularValues, i);
            const double maxRemainingSingularValue = singularValues[pos];

            if (maxRemainingSingularValue == 0.)
                break;

            if (i != pos)
            {
                std::swap(singularValues[i], singularValues[pos]);
                swapColumns(matrixU, i, pos);
                swapColumns(matrixV, i, pos);
            }
        }

        if (minEl(abs(singularValues)) > 0)
            invertedMatrix = mult(multWithDiagonal(matrixV, 1. / singularValues), trans(matrixU));
    }

    template<size_t R, size_t C>
    inline void SingularValueDecomp<R, C>::JacobiSVD2x2(const DenseMatrix<double, R, C>& matrix, const size_t& p, const size_t& q, JacobiRotation& j_left, JacobiRotation& j_right)
    {
        StaticMatrix<double, 2, 2> m(2, 2);
        m(0, 0) = matrix(p, p);
        m(0, 1) = matrix(p, q);
        m(1, 0) = matrix(q, p);
        m(1, 1) = matrix(q, q);

        JacobiRotation rot1;
        const double t = m(0, 0) + m(1, 1);
        const double d = m(1, 0) - m(0, 1);

        if (std::abs(d) < std::numeric_limits<double>::min())
        {
            rot1.s = 0.;
            rot1.c = 1.;
        }
        else
        {
            const double u   = t / d;
            const double tmp = std::sqrt(1. + u * u);
            rot1.s = 1. / tmp;
            rot1.c = u / tmp;
        }

        rot1.rotateMatrixFromLeft(0, 1, m);
        j_right = JacobiRotation(0, 1, m);
        j_left  = rot1.mult(j_right.transposed());
    }

    template<size_t R, size_t C>
    inline typename SingularValueDecomp<R, C>::DenseVectorType SingularValueDecomp<R, C>::solve(const DenseVectorType& y) const
    {
        return mult(invertedMatrix, y);
    }
}
