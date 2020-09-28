#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/QRDecomp.hpp>

using namespace TB;

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp1x1")
{
    const DynamicMatrix<double> mat{ {121} };
    const QRDecomp qrDecomp(mat);

    CHECK(qrDecomp.matrixQ == DynamicMatrix<double>{ {-1} });
    CHECK(qrDecomp.matrixR == DynamicMatrix<double>{ {-121} });

    const auto QR = mult(qrDecomp.matrixQ, qrDecomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp2x2")
{
    const StaticMatrix<double, 2, 2> mat{ {16,10},{12,58} };
    const QRDecomp decomp(mat);

    CHECK(decomp.matrixQ == DynamicMatrix<double>{ {-4. / 5, 3. / 5}, { -3. / 5, -4. / 5 } });
    CHECK(decomp.matrixR == DynamicMatrix<double>{ {-20, -214. / 5}, {0, -202. / 5} });

    const auto QR = mult(decomp.matrixQ, decomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp3x3")
{
    const DynamicMatrix<double> mat{ {4, 8, 16}, {0, 2, 26}, {4, 10, 27} };
    const QRDecomp decomp(mat);

    CHECK(decomp.matrixQ == DynamicMatrix<double>{ { -1. / std::sqrt(2), 1. / std::sqrt(6), 1. / std::sqrt(3)}, { 0, -std::sqrt(2. / 3), 1. / std::sqrt(3)}, { -1. / std::sqrt(2), -1. / std::sqrt(6) , -1. / std::sqrt(3) } });
    CHECK(decomp.matrixR == DynamicMatrix<double>{ { -4 * std::sqrt(2), -9 * std::sqrt(2), -27. / std::sqrt(2) - 8 * std::sqrt(2) },  { 0, -std::sqrt(6), -9 * std::sqrt(3. / 2) - 6 * std::sqrt(6) }, { 0, 0, 5 * std::sqrt(3) } });

    const auto QR = mult(decomp.matrixQ, decomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp3x3_Diagonal")
{
    const DynamicMatrix<double> mat{ {9,0,0},{0,49,0},{0,0,16} };
    const QRDecomp decomp(mat);

    CHECK(decomp.matrixQ == -DynamicMatrix<double>::Identity(3));
    CHECK(decomp.matrixR == -mat);

    const auto QR = mult(decomp.matrixQ, decomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp_Singular1")
{
    const DynamicMatrix<double> mat{ {9,0},{0,0} };
    const QRDecomp decomp(mat);

    CHECK(decomp.matrixQ == DynamicMatrix<double>{ {-1, 0}, {0, 1} });
    CHECK(decomp.matrixR == DynamicMatrix<double>{ {-9, 0}, {0, 0} });

    const auto QR = mult(decomp.matrixQ, decomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}

TEST_CASE("UnitTest_Algebra_LAPACK_QRDecomp_Singular2")
{
    const DynamicMatrix<double> mat{ {16,12},{12,9} };
    const QRDecomp decomp(mat);

    CHECK(decomp.matrixQ == DynamicMatrix<double>{ {-4. / 5, -3. / 5}, {-3. / 5, 4. / 5} });
    CHECK(decomp.matrixR == DynamicMatrix<double>{ {-20, -15}, {0, 0} });

    const auto QR = mult(decomp.matrixQ, decomp.matrixR);
    CHECK(  QR == mat);
    CHECK(!(QR != mat));
}
