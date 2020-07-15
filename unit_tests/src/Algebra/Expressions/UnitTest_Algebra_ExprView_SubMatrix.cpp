#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_ExprView_SubMatrix")
{
    const DynamicMatrix<int> mat = { { 5, 7, 2,-4, 8, 8,15,20},
                                     { 9, 3,-1, 6,-7,-4,16,21},
                                     { 5,-8, 2, 1, 0,12,17,22},
                                     { 9, 0,18, 4,-9,-3,18,23},
                                     {-5,17, 4, 5,-1,20,19,24} };

    auto subMat1 = subMatrix(mat, 2, 4, 0, 1);
    CHECK(subMat1.size()     == 6);
    CHECK(subMat1.rowCount() == 3);
    CHECK(subMat1.colCount() == 2);
    CHECK(subMat1.shape()    == MatrixShape(3, 2));
    CHECK(subMat1(0, 0) ==  5);
    CHECK(subMat1(0, 1) == -8);
    CHECK(subMat1(1, 0) ==  9);
    CHECK(subMat1(1, 1) ==  0);
    CHECK(subMat1(2, 0) == -5);
    CHECK(subMat1(2, 1) == 17);
    CHECK(subMat1[0]    ==  5);
    CHECK(subMat1[1]    == -8);
    CHECK(subMat1[2]    ==  9);
    CHECK(subMat1[3]    ==  0);
    CHECK(subMat1[4]    == -5);
    CHECK(subMat1[5]    == 17);

    CHECK_NOTHROW(subMat1(0, 1));
    CHECK_THROWS (subMat1(0, 2));
    CHECK_THROWS (subMat1(1, 2));
    CHECK_THROWS (subMat1(2, 2));
    CHECK_THROWS (subMat1(3, 2));
    CHECK_NOTHROW(subMat1(2, 0));
    CHECK_THROWS (subMat1(3, 0));
    CHECK_THROWS (subMat1(3, 1));
    CHECK_THROWS (subMat1(3, 2));
    CHECK_THROWS (subMat1(3, 4));
    CHECK_NOTHROW(subMat1[5]);
    CHECK_THROWS (subMat1[6]);
    CHECK_THROWS (subMat1[7]);

    const auto subMat2 = subMatrix(mat, 1, 3, 2, 6);
    CHECK(subMat2.size()     == 15);
    CHECK(subMat2.rowCount() == 3);
    CHECK(subMat2.colCount() == 5);
    CHECK(subMat2.shape()    == MatrixShape(3, 5));
    CHECK(subMat2(0, 0) == -1);
    CHECK(subMat2(0, 1) ==  6);
    CHECK(subMat2(0, 2) == -7);
    CHECK(subMat2(0, 3) == -4);
    CHECK(subMat2(0, 4) == 16);
    CHECK(subMat2(1, 0) ==  2);
    CHECK(subMat2(1, 1) ==  1);
    CHECK(subMat2(1, 2) ==  0);
    CHECK(subMat2(1, 3) == 12);
    CHECK(subMat2(1, 4) == 17);
    CHECK(subMat2(2, 0) == 18);
    CHECK(subMat2(2, 1) ==  4);
    CHECK(subMat2(2, 2) == -9);
    CHECK(subMat2(2, 3) == -3);
    CHECK(subMat2(2, 4) == 18);
    CHECK(subMat2[0]    == -1);
    CHECK(subMat2[1]    ==  6);
    CHECK(subMat2[2]    == -7);
    CHECK(subMat2[3]    == -4);
    CHECK(subMat2[4]    == 16);
    CHECK(subMat2[5]    ==  2);
    CHECK(subMat2[6]    ==  1);
    CHECK(subMat2[7]    ==  0);
    CHECK(subMat2[8]    == 12);
    CHECK(subMat2[9]    == 17);
    CHECK(subMat2[10]   == 18);
    CHECK(subMat2[11]   ==  4);
    CHECK(subMat2[12]   == -9);
    CHECK(subMat2[13]   == -3);
    CHECK(subMat2[14]   == 18);

    CHECK_NOTHROW(subMat2(0, 4));
    CHECK_THROWS (subMat2(0, 5));
    CHECK_THROWS (subMat2(1, 5));
    CHECK_THROWS (subMat2(2, 5));
    CHECK_THROWS (subMat2(3, 5));
    CHECK_THROWS (subMat2(4, 5));
    CHECK_THROWS (subMat2(5, 5));
    CHECK_THROWS (subMat2(6, 5));
    CHECK_NOTHROW(subMat2(2, 0));
    CHECK_THROWS (subMat2(3, 0));
    CHECK_THROWS (subMat2(3, 1));
    CHECK_THROWS (subMat2(3, 2));
    CHECK_THROWS (subMat2(3, 3));
    CHECK_THROWS (subMat2(3, 4));
    CHECK_NOTHROW(subMat2[14]);
    CHECK_THROWS (subMat2[15]);
    CHECK_THROWS (subMat2[16]);
}

TEST_CASE("UnitTest_Algebra_ExprView_SubMatrix_Operator")
{
    DynamicMatrix<int> mat = { { 5, 7, 2,-4, 8, 8,15,20},
                               { 9, 3,-1, 6,-7,-4,16,21},
                               { 5,-8, 2, 1, 0,12,17,22},
                               { 9, 0,18, 4,-9,-3,18,23},
                               {-5,17, 4, 5,-1,20,19,24} };

    auto subMat = subMatrix(mat, 2, 4, 1,5);
    CHECK(subMat == DynamicMatrix<int>{ {-8,2,1,0,12},{0,18, 4,-9,-3},{17,4,5,-1,20} });

    subMat *= 3;
    CHECK(subMat == DynamicMatrix<int>{ {-24,6,3,0,36},{0,54,12,-27,-9},{51,12,15,-3,60} });

    CHECK(mat == DynamicMatrix<int>{ { 5, 7, 2, -4, 8, 8, 15, 20},
                                     { 9, 3,-1, 6,-7,-4,16,21 },
                                     { 5,-24,6,3,0,36,17,22 },
                                     { 9, 0,54,12,-27,-9,18,23 },
                                     { -5,51,12,15,-3,60,19,24 } });
}
