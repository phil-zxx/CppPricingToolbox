#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <iostream>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Func_Mult_MatVec")
{
    const DynamicMatrix<double> M{ {4,5},{9,2},{7,6} };
    const DynamicVector<int> v{ 8,-4 };

    const auto Mv = mult(M, v);
    CHECK(Mv.size()     == 3);
    CHECK(Mv.rowCount() == 3);
    CHECK(Mv.colCount() == 1);
    CHECK(Mv.shape()    == MatrixShape(3, 1));
    CHECK(Mv            == DynamicVector<int>{12, 64, 32});
    CHECK(Mv            == DynamicMatrix<int>{ {12},{64},{32} });
}

TEST_CASE("UnitTest_Algebra_Func_Mult_VecVec")
{
    const DynamicVector<int>       u{ 8,-4,3,5 };
    const DynamicVector<int, true> v{ 3,9,-7 };

    const auto uv = mult(u, v);
    CHECK(uv.size()     == 12);
    CHECK(uv.rowCount() == 4);
    CHECK(uv.colCount() == 3);
    CHECK(uv.shape()    == MatrixShape(4, 3));
    CHECK(uv            == DynamicMatrix<int>{ {24, 72, -56}, { -12, -36, 28 }, { 9, 27, -21 }, { 15, 45, -35 } });
}

TEST_CASE("UnitTest_Algebra_Func_Mult_MatMat")
{
    const DynamicMatrix<double> A{ {2, 7, -5}, {-12, -6, -12}, {1, -7, -8}, {12, 11, -7}, {2, 3, -5} };
    const DynamicMatrix<double> B{ {-3, 2}, {22, -4}, {9, -2} };

    const auto AB = mult(A, B);
    CHECK(AB.size()     == 10);
    CHECK(AB.rowCount() == 5);
    CHECK(AB.colCount() == 2);
    CHECK(AB.shape()    == MatrixShape(5, 2));
    CHECK(AB            == DynamicMatrix<int>{ {103, -14}, { -204, 24 }, { -229, 46 }, { 143, -6 }, { 15, 2 } });
    CHECK(AB            != DynamicMatrix<int>{ {103, -13}, { -204, 24 }, { -229, 46 }, { 143, -6 }, { 15, 2 } });

    const auto A2 = 2 * A;
    const auto B5 = B - 5;
    const auto A2B5_1 = mult(A2, B5);
    CHECK(A2B5_1.size()     == 10);
    CHECK(A2B5_1.rowCount() == 5);
    CHECK(A2B5_1.colCount() == 2);
    CHECK(A2B5_1.shape()    == MatrixShape(5, 2));
    CHECK(A2B5_1            == DynamicMatrix<int>{ {166, -68}, { -108, 348 }, { -318, 232 }, { 126, -172 }, { 30, 4 } });
    CHECK(A2B5_1            != DynamicMatrix<int>{ {166, -68}, { -108, 348 }, { -318, 232 }, { 126, -172 }, { 30, 0 } });

    const auto A2B5_2 = mult(2 * A, B - 5);
    CHECK(A2B5_2.size()     == 10);
    CHECK(A2B5_2.rowCount() == 5);
    CHECK(A2B5_2.colCount() == 2);
    CHECK(A2B5_2.shape()    == MatrixShape(5, 2));
    CHECK(A2B5_2            == DynamicMatrix<int>{ {166, -68}, { -108, 348 }, { -318, 232 }, { 126, -172 }, { 30, 4 } });
    CHECK(A2B5_2            != DynamicMatrix<int>{ {166, -68}, { -108, 348 }, { -318, 232 }, { 126, -172 }, { 30, 0 } });
}

TEST_CASE("UnitTest_Algebra_Func_MultWithDiagonal")
{
    const DynamicMatrix<double> M{ {4,5},{9,2},{7,6} };
    const DynamicVector<int> v{ 8,-4 };

    const auto Mv = multWithDiagonal(M, v);
    CHECK(Mv.size()     == 6);
    CHECK(Mv.rowCount() == 3);
    CHECK(Mv.colCount() == 2);
    CHECK(Mv.shape()    == MatrixShape(3, 2));
    CHECK(Mv            == DynamicMatrix<int>{ {32,-20},{72,-8},{56,-24} });

    const DynamicMatrix<double> N{ {4,5,1},{9,2,5},{7,6,9} };
    const DynamicVector<int> w{ 8,-4,99 };

    CHECK_NOTHROW(multWithDiagonal(M, v));
    CHECK_NOTHROW(multWithDiagonal(N, w));
    CHECK_THROWS (multWithDiagonal(M, M));
    CHECK_THROWS (multWithDiagonal(N, N));
    CHECK_THROWS (multWithDiagonal(M, w));
    CHECK_THROWS (multWithDiagonal(N, v));
}