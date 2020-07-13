#include <doctest/doctest.h>
#include <iostream>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/CholeskyDecomp.hpp>

using namespace Toolbox;

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky1x1")
{
    const DynamicMatrix<double> mat{ {121} };
    const CholeskyDecomp cholesky(mat);

    CHECK(cholesky.lowerTriangular == DynamicMatrix<double>{ {11} });

    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky2x2")
{
    const DynamicMatrix<double> mat{ {16,12},{12,58} };
    const CholeskyDecomp cholesky(mat);

    CHECK(cholesky.lowerTriangular == DynamicMatrix<double>{ {4,0},{3,7} });

    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky3x3")
{
    const DynamicMatrix<double> mat{ {9,0,0},{0,49,0},{0,0,16} };
    const CholeskyDecomp cholesky(mat);

    CHECK(cholesky.lowerTriangular == DynamicMatrix<double>{ {3,0,0},{0,7,0},{0,0,4} });

    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky10x10")
{
    const StaticMatrix<double, 10, 10> mat{
        {196, 112, -70, 112, -168, 70, -140, 70, -14, 126},
        {112, 208, -208,208, -276, 160, -236, 124, 40, 120},
        {-70, -208, 446, -298, 495, -135, 292, -33, 39, -41},
        {112, 208, -298, 293, -429, 239, -295, 25, -101, 145},
        {-168, -276, 495, -429, 871, -129, 406, -134, 247, -339},
        {70, 160, -135, 239, -129, 458, -237, -174, -100, 76},
        {-140, -236, 292, -295, 406, -237, 464, -107, -5, -110},
        {70, 124, -33, 25, -134, -174, -107, 494, 262, -9},
        {-14, 40, 39, -101, 247, -100, -5, 262, 413, -238},
        {126, 120, -41, 145, -339, 76, -110, -9, -238, 631} };
    const CholeskyDecomp cholesky(mat);

    const StaticMatrix<double, 10, 10> L_true{
        {14, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 8, 12, 0, 0, 0, 0, 0, 0, 0, 0 },
        { -5, -14, 15, 0, 0, 0, 0, 0, 0, 0 },
        { 8, 12, -6, 7, 0, 0, 0, 0, 0, 0 },
        { -12, -15, 15, -9, 14, 0, 0, 0, 0, 0 },
        { 5, 10, 2, 13, 12, 4, 0, 0, 0, 0 },
        { -10, -13, 4, -5, -1, 3, 12, 0, 0, 0 },
        { 5, 7, 6, -9, -10, -11, -1, 9, 0, 0 },
        { -1, 4, 6, -15, 5, -3, -4, 9, 2, 0 },
        { 9, 4, 4, 7, -12, 9, 1, -7, -5, 13 } };
    CHECK(cholesky.lowerTriangular == L_true);

    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky_Singular1")
{
    const DynamicMatrix<double> mat{ {9,0},{0,0} };
    const CholeskyDecomp cholesky(mat);
    
    CHECK(cholesky.lowerTriangular == DynamicMatrix<double>{ {3,0},{0,0} });
    
    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky_Singular2")
{
    const DynamicMatrix<double> mat{ {16,12},{12,9} };
    const CholeskyDecomp cholesky(mat);
    
    CHECK(cholesky.lowerTriangular == DynamicMatrix<double>{ {4,0},{3,0} });
    
    const auto LLT = mult(cholesky.lowerTriangular, trans(cholesky.lowerTriangular));
    CHECK(LLT == mat);
}

TEST_CASE("UnitTest_Algebra_LAPACK_Cholesky_Throw")
{
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>()));
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>{ {0,0},{0,0} }));
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>{ {121, 5} }));
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>{ {16,12},{13,58} }));
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>{ {9,0,0},{0,49,0} }));
    CHECK_THROWS(CholeskyDecomp(DynamicMatrix<double>{ {9,6,6,9},{6,29,9,36},{6,9,5,12},{9,36,12,49} }));

    CHECK_NOTHROW(CholeskyDecomp(DynamicMatrix<double>{ {121} }));
    CHECK_NOTHROW(CholeskyDecomp(DynamicMatrix<double>{ {16,12},{12,58} }));
    CHECK_NOTHROW(CholeskyDecomp(DynamicMatrix<double>{ {9,0,0},{0,49,0 },{0,0,16} }));
}
