#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_ExprView_Submatrix")
{
    const DynamicMatrix<int> mat = { { 5, 7, 2,-4, 8, 8,15,20},
                                     { 9, 3,-1, 6,-7,-4,16,21},
                                     { 5,-8, 2, 1, 0,12,17,22},
                                     { 9, 0,18, 4,-9,-3,18,23},
                                     {-5,17, 4, 5,-1,20,19,24} };

    auto submat1 = submatrix(mat, 2, 4, 0, 1);
    CHECK(submat1.size()     == 6);
    CHECK(submat1.rowCount() == 3);
    CHECK(submat1.colCount() == 2);
    CHECK(submat1.shape()    == MatrixShape(3, 2));
    CHECK(submat1(0, 0) ==  5);
    CHECK(submat1(0, 1) == -8);
    CHECK(submat1(1, 0) ==  9);
    CHECK(submat1(1, 1) ==  0);
    CHECK(submat1(2, 0) == -5);
    CHECK(submat1(2, 1) == 17);
    CHECK(submat1[0]    ==  5);
    CHECK(submat1[1]    == -8);
    CHECK(submat1[2]    ==  9);
    CHECK(submat1[3]    ==  0);
    CHECK(submat1[4]    == -5);
    CHECK(submat1[5]    == 17);

    CHECK_NOTHROW(submat1(0, 1));
    CHECK_THROWS (submat1(0, 2));
    CHECK_THROWS (submat1(1, 2));
    CHECK_THROWS (submat1(2, 2));
    CHECK_THROWS (submat1(3, 2));
    CHECK_NOTHROW(submat1(2, 0));
    CHECK_THROWS (submat1(3, 0));
    CHECK_THROWS (submat1(3, 1));
    CHECK_THROWS (submat1(3, 2));
    CHECK_THROWS (submat1(3, 4));
    CHECK_NOTHROW(submat1[5]);
    CHECK_THROWS (submat1[6]);
    CHECK_THROWS (submat1[7]);

    const auto submat2 = submatrix(mat, 1, 3, 2, 6);
    CHECK(submat2.size()     == 15);
    CHECK(submat2.rowCount() == 3);
    CHECK(submat2.colCount() == 5);
    CHECK(submat2.shape()    == MatrixShape(3, 5));
    CHECK(submat2(0, 0) == -1);
    CHECK(submat2(0, 1) ==  6);
    CHECK(submat2(0, 2) == -7);
    CHECK(submat2(0, 3) == -4);
    CHECK(submat2(0, 4) == 16);
    CHECK(submat2(1, 0) ==  2);
    CHECK(submat2(1, 1) ==  1);
    CHECK(submat2(1, 2) ==  0);
    CHECK(submat2(1, 3) == 12);
    CHECK(submat2(1, 4) == 17);
    CHECK(submat2(2, 0) == 18);
    CHECK(submat2(2, 1) ==  4);
    CHECK(submat2(2, 2) == -9);
    CHECK(submat2(2, 3) == -3);
    CHECK(submat2(2, 4) == 18);
    CHECK(submat2[0]    == -1);
    CHECK(submat2[1]    ==  6);
    CHECK(submat2[2]    == -7);
    CHECK(submat2[3]    == -4);
    CHECK(submat2[4]    == 16);
    CHECK(submat2[5]    ==  2);
    CHECK(submat2[6]    ==  1);
    CHECK(submat2[7]    ==  0);
    CHECK(submat2[8]    == 12);
    CHECK(submat2[9]    == 17);
    CHECK(submat2[10]   == 18);
    CHECK(submat2[11]   ==  4);
    CHECK(submat2[12]   == -9);
    CHECK(submat2[13]   == -3);
    CHECK(submat2[14]   == 18);

    CHECK_NOTHROW(submat2(0, 4));
    CHECK_THROWS (submat2(0, 5));
    CHECK_THROWS (submat2(1, 5));
    CHECK_THROWS (submat2(2, 5));
    CHECK_THROWS (submat2(3, 5));
    CHECK_THROWS (submat2(4, 5));
    CHECK_THROWS (submat2(5, 5));
    CHECK_THROWS (submat2(6, 5));
    CHECK_NOTHROW(submat2(2, 0));
    CHECK_THROWS (submat2(3, 0));
    CHECK_THROWS (submat2(3, 1));
    CHECK_THROWS (submat2(3, 2));
    CHECK_THROWS (submat2(3, 3));
    CHECK_THROWS (submat2(3, 4));
    CHECK_NOTHROW(submat2[14]);
    CHECK_THROWS (submat2[15]);
    CHECK_THROWS (submat2[16]);
}

TEST_CASE("UnitTest_Algebra_ExprView_Submatrix_Operator")
{
    DynamicMatrix<int> mat = { { 5, 7, 2,-4, 8, 8,15,20},
                               { 9, 3,-1, 6,-7,-4,16,21},
                               { 5,-8, 2, 1, 0,12,17,22},
                               { 9, 0,18, 4,-9,-3,18,23},
                               {-5,17, 4, 5,-1,20,19,24} };

    auto submat = submatrix(mat, 2, 4, 1,5);
    CHECK(submat == DynamicMatrix<int>{ {-8,2,1,0,12},{0,18, 4,-9,-3},{17,4,5,-1,20} });

    submat *= 3;
    CHECK(submat == DynamicMatrix<int>{ {-24,6,3,0,36},{0,54,12,-27,-9},{51,12,15,-3,60} });

    CHECK(mat == DynamicMatrix<int>{ { 5, 7, 2, -4, 8, 8, 15, 20},
                                     { 9, 3,-1, 6,-7,-4,16,21 },
                                     { 5,-24,6,3,0,36,17,22 },
                                     { 9, 0,54,12,-27,-9,18,23 },
                                     { -5,51,12,15,-3,60,19,24 } });
}
