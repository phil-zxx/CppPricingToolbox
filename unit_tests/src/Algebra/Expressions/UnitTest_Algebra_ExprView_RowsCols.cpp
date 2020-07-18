#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_ExprView_Rows1")
{
    const DynamicMatrix<int> mat1 = { { 5, 7, 2,-4},
                                      { 9, 3,-1, 6},
                                      { 5,-8, 2, 1},
                                      { 9, 0, 8, 4},
                                      {-5, 7, 4, 5} };
    const auto rows12 = rows(mat1, 1, 2);
    CHECK(rows12.size()     == 8);
    CHECK(rows12.rowCount() == 2);
    CHECK(rows12.colCount() == 4);
    CHECK(rows12.shape()    == MatrixShape(2, 4));
    CHECK(rows12(0, 0) ==  9);
    CHECK(rows12(0, 1) ==  3);
    CHECK(rows12(0, 2) == -1);
    CHECK(rows12(0, 3) ==  6);
    CHECK(rows12(1, 0) ==  5);
    CHECK(rows12(1, 1) == -8);
    CHECK(rows12(1, 2) ==  2);
    CHECK(rows12(1, 3) ==  1);
    CHECK(rows12[0]    ==  9);
    CHECK(rows12[1]    ==  3);
    CHECK(rows12[2]    == -1);
    CHECK(rows12[3]    ==  6);
    CHECK(rows12[4]    ==  5);
    CHECK(rows12[5]    == -8);
    CHECK(rows12[6]    ==  2);
    CHECK(rows12[7]    ==  1);

    CHECK_NOTHROW(rows12(0, 3));
    CHECK_THROWS (rows12(0, 4));
    CHECK_THROWS (rows12(1, 4));
    CHECK_THROWS (rows12(2, 4));
    CHECK_THROWS (rows12(3, 4));
    CHECK_THROWS (rows12(4, 4));
    CHECK_THROWS (rows12(5, 4));
    CHECK_NOTHROW(rows12(1, 0));
    CHECK_THROWS (rows12(2, 0));
    CHECK_THROWS (rows12(2, 1));
    CHECK_THROWS (rows12(2, 2));
    CHECK_THROWS (rows12(2, 3));
    CHECK_NOTHROW(rows12[7]);
    CHECK_THROWS (rows12[8]);
    CHECK_THROWS (rows12[9]);

    DynamicMatrix<int> mat2 = { { 5, 7, 2,-4},
                                { 9, 3,-1, 6},
                                { 5,-8, 2, 1},
                                { 9, 0, 8, 4},
                                {-5, 7, 4, 5} };
    auto rows24 = rows(mat2, 2, 3);
    CHECK(rows24.size()     == 12);
    CHECK(rows24.rowCount() == 3);
    CHECK(rows24.colCount() == 4);
    CHECK(rows24.shape()    == MatrixShape(3, 4));
    CHECK(rows24(0, 0) ==  5);
    CHECK(rows24(0, 1) == -8);
    CHECK(rows24(0, 2) ==  2);
    CHECK(rows24(0, 3) ==  1);
    CHECK(rows24(1, 0) ==  9);
    CHECK(rows24(1, 1) ==  0);
    CHECK(rows24(1, 2) ==  8);
    CHECK(rows24(1, 3) ==  4);
    CHECK(rows24(2, 0) == -5);
    CHECK(rows24(2, 1) ==  7);
    CHECK(rows24(2, 2) ==  4);
    CHECK(rows24(2, 3) ==  5);
    CHECK(rows24[0]    ==  5);
    CHECK(rows24[1]    == -8);
    CHECK(rows24[2]    ==  2);
    CHECK(rows24[3]    ==  1);
    CHECK(rows24[4]    ==  9);
    CHECK(rows24[5]    ==  0);
    CHECK(rows24[6]    ==  8);
    CHECK(rows24[7]    ==  4);
    CHECK(rows24[8]    == -5);
    CHECK(rows24[9]    ==  7);
    CHECK(rows24[10]   ==  4);
    CHECK(rows24[11]   ==  5);

    CHECK_NOTHROW(rows24(0, 3));
    CHECK_THROWS (rows24(0, 4));
    CHECK_THROWS (rows24(1, 4));
    CHECK_THROWS (rows24(2, 4));
    CHECK_THROWS (rows24(3, 4));
    CHECK_THROWS (rows24(4, 4));
    CHECK_THROWS (rows24(5, 4));
    CHECK_NOTHROW(rows24(2, 0));
    CHECK_THROWS (rows24(3, 0));
    CHECK_THROWS (rows24(3, 1));
    CHECK_THROWS (rows24(3, 2));
    CHECK_THROWS (rows24(3, 3));
    CHECK_THROWS (rows24(3, 4));
    CHECK_NOTHROW(rows24[11]);
    CHECK_THROWS (rows24[12]);
    CHECK_THROWS (rows24[13]);
}

TEST_CASE("UnitTest_Algebra_ExprView_Rows2")
{
    const DynamicMatrix<int> mat1 = { { 5, 7},
                                      { 9, 3},
                                      { 5,-8},
                                      { 9, 0},
                                      {-5, 7} };
    const auto rows2 = rows(mat1, 2);
    CHECK(rows2.size()     == 6);
    CHECK(rows2.rowCount() == 3);
    CHECK(rows2.colCount() == 2);
    CHECK(rows2.shape()    == MatrixShape(3, 2));
    CHECK(rows2(0, 0) ==  5);
    CHECK(rows2(0, 1) == -8);
    CHECK(rows2(1, 0) ==  9);
    CHECK(rows2(1, 1) ==  0);
    CHECK(rows2(2, 0) == -5);
    CHECK(rows2(2, 1) ==  7);
    CHECK(rows2[0]    ==  5);
    CHECK(rows2[1]    == -8);
    CHECK(rows2[2]    ==  9);
    CHECK(rows2[3]    ==  0);
    CHECK(rows2[4]    == -5);
    CHECK(rows2[5]    ==  7);

    CHECK_NOTHROW(rows2(0, 1));
    CHECK_THROWS (rows2(0, 2));
    CHECK_THROWS (rows2(1, 2));
    CHECK_THROWS (rows2(2, 2));
    CHECK_THROWS (rows2(3, 2));
    CHECK_NOTHROW(rows2(2, 0));
    CHECK_THROWS (rows2(3, 0));
    CHECK_THROWS (rows2(3, 1));
    CHECK_THROWS (rows2(3, 2));
    CHECK_THROWS (rows2(3, 3));
    CHECK_THROWS (rows2(3, 4));
    CHECK_NOTHROW(rows2[5]);
    CHECK_THROWS (rows2[6]);
    CHECK_THROWS (rows2[7]);

    DynamicMatrix<int> mat2 = { { 5, 7},
                                { 9, 3},
                                { 5,-8},
                                { 9, 0},
                                {-5, 7} };
    auto rows3 = rows(mat2, 3);
    CHECK(rows3.size()     == 4);
    CHECK(rows3.rowCount() == 2);
    CHECK(rows3.colCount() == 2);
    CHECK(rows3.shape()    == MatrixShape(2, 2));
    CHECK(rows3(0, 0) ==  9);
    CHECK(rows3(0, 1) ==  0);
    CHECK(rows3(1, 0) == -5);
    CHECK(rows3(1, 1) ==  7);
    CHECK(rows3[0]    ==  9);
    CHECK(rows3[1]    ==  0);
    CHECK(rows3[2]    == -5);
    CHECK(rows3[3]    ==  7);

    CHECK_NOTHROW(rows3(0, 1));
    CHECK_THROWS (rows3(0, 2));
    CHECK_THROWS (rows3(1, 2));
    CHECK_THROWS (rows3(2, 2));
    CHECK_THROWS (rows3(3, 2));
    CHECK_NOTHROW(rows3(1, 0));
    CHECK_THROWS (rows3(2, 0));
    CHECK_THROWS (rows3(2, 1));
    CHECK_THROWS (rows3(2, 2));
    CHECK_THROWS (rows3(2, 3));
    CHECK_NOTHROW(rows3[3]);
    CHECK_THROWS (rows3[4]);
    CHECK_THROWS (rows3[5]);
}

TEST_CASE("UnitTest_Algebra_ExprView_Cols1")
{
    const DynamicMatrix<int> mat1 = { { 5, 7, 2,-4},
                                      { 9, 3,-1, 6},
                                      { 5,-8, 2, 1},
                                      { 9, 0, 8, 4},
                                      {-5, 7, 4, 5} };
    const auto cols23 = columns(mat1, 2, 2);
    CHECK(cols23.size()     == 10);
    CHECK(cols23.rowCount() == 5);
    CHECK(cols23.colCount() == 2);
    CHECK(cols23.shape()    == MatrixShape(5, 2));
    CHECK(cols23(0, 0) ==  2);
    CHECK(cols23(0, 1) == -4);
    CHECK(cols23(1, 0) == -1);
    CHECK(cols23(1, 1) ==  6);
    CHECK(cols23(2, 0) ==  2);
    CHECK(cols23(2, 1) ==  1);
    CHECK(cols23(3, 0) ==  8);
    CHECK(cols23(3, 1) ==  4);
    CHECK(cols23(4, 0) ==  4);
    CHECK(cols23(4, 1) ==  5);
    CHECK(cols23[0]    ==  2);
    CHECK(cols23[1]    == -4);
    CHECK(cols23[2]    == -1);
    CHECK(cols23[3]    ==  6);
    CHECK(cols23[4]    ==  2);
    CHECK(cols23[5]    ==  1);
    CHECK(cols23[6]    ==  8);
    CHECK(cols23[7]    ==  4);
    CHECK(cols23[8]    ==  4);
    CHECK(cols23[9]    ==  5);

    CHECK_NOTHROW(cols23(0, 1));
    CHECK_THROWS (cols23(0, 2));
    CHECK_THROWS (cols23(1, 2));
    CHECK_THROWS (cols23(2, 2));
    CHECK_THROWS (cols23(3, 2));
    CHECK_NOTHROW(cols23(4, 0));
    CHECK_THROWS (cols23(5, 0));
    CHECK_THROWS (cols23(5, 1));
    CHECK_THROWS (cols23(5, 2));
    CHECK_THROWS (cols23(5, 3));
    CHECK_THROWS (cols23(5, 4));
    CHECK_THROWS (cols23(5, 5));
    CHECK_THROWS (cols23(5, 6));
    CHECK_NOTHROW(cols23[9]);
    CHECK_THROWS (cols23[10]);
    CHECK_THROWS (cols23[11]);

    DynamicMatrix<int> mat2 = { { 5, 7, 2,-4},
                                { 9, 3,-1, 6},
                                { 5,-8, 2, 1},
                                { 9, 0, 8, 4},
                                {-5, 7, 4, 5} };
    const auto cols11 = columns(mat2, 0, 3);
    CHECK(cols11.size()     == 15);
    CHECK(cols11.rowCount() == 5);
    CHECK(cols11.colCount() == 3);
    CHECK(cols11.shape()    == MatrixShape(5, 3));
    CHECK(cols11(0, 0) ==  5);
    CHECK(cols11(0, 1) ==  7);
    CHECK(cols11(0, 2) ==  2);
    CHECK(cols11(1, 0) ==  9);
    CHECK(cols11(1, 1) ==  3);
    CHECK(cols11(1, 2) == -1);
    CHECK(cols11(2, 0) ==  5);
    CHECK(cols11(2, 1) == -8);
    CHECK(cols11(2, 2) ==  2);
    CHECK(cols11(3, 0) ==  9);
    CHECK(cols11(3, 1) ==  0);
    CHECK(cols11(3, 2) ==  8);
    CHECK(cols11(4, 0) == -5);
    CHECK(cols11(4, 1) ==  7);
    CHECK(cols11(4, 2) ==  4);
    CHECK(cols11[0]    ==  5);
    CHECK(cols11[1]    ==  7);
    CHECK(cols11[2]    ==  2);
    CHECK(cols11[3]    ==  9);
    CHECK(cols11[4]    ==  3);
    CHECK(cols11[5]    == -1);
    CHECK(cols11[6]    ==  5);
    CHECK(cols11[7]    == -8);
    CHECK(cols11[8]    ==  2);
    CHECK(cols11[9]    ==  9);
    CHECK(cols11[10]   ==  0);
    CHECK(cols11[11]   ==  8);
    CHECK(cols11[12]   == -5);
    CHECK(cols11[13]   ==  7);
    CHECK(cols11[14]   ==  4);

    CHECK_NOTHROW(cols11(0, 2));
    CHECK_THROWS (cols11(0, 3));
    CHECK_THROWS (cols11(1, 3));
    CHECK_THROWS (cols11(2, 3));
    CHECK_THROWS (cols11(3, 3));
    CHECK_THROWS (cols11(4, 3));
    CHECK_NOTHROW(cols11(4, 0));
    CHECK_THROWS (cols11(5, 0));
    CHECK_THROWS (cols11(5, 1));
    CHECK_THROWS (cols11(5, 2));
    CHECK_THROWS (cols11(5, 3));
    CHECK_THROWS (cols11(5, 4));
    CHECK_THROWS (cols11(5, 5));
    CHECK_THROWS (cols11(5, 6));
    CHECK_NOTHROW(cols11[14]);
    CHECK_THROWS (cols11[15]);
    CHECK_THROWS (cols11[16]);
}

TEST_CASE("UnitTest_Algebra_ExprView_Cols2")
{
    const DynamicMatrix<int> mat1 = { { 5, 7, 2,-4,11},
                                      { 9, 3,-1, 6,12},
                                      {-5, 7, 4, 5,13} };
    const auto cols1 = columns(mat1, 1);
    CHECK(cols1.size()     == 12);
    CHECK(cols1.rowCount() == 3);
    CHECK(cols1.colCount() == 4);
    CHECK(cols1.shape()    == MatrixShape(3, 4));
    CHECK(cols1(0, 0) ==  7);
    CHECK(cols1(0, 1) ==  2);
    CHECK(cols1(0, 2) == -4);
    CHECK(cols1(0, 3) == 11);
    CHECK(cols1(1, 0) ==  3);
    CHECK(cols1(1, 1) == -1);
    CHECK(cols1(1, 2) ==  6);
    CHECK(cols1(1, 3) == 12);
    CHECK(cols1(2, 0) ==  7);
    CHECK(cols1(2, 1) ==  4);
    CHECK(cols1(2, 2) ==  5);
    CHECK(cols1(2, 3) == 13);
    CHECK(cols1[0]    ==  7);
    CHECK(cols1[1]    ==  2);
    CHECK(cols1[2]    == -4);
    CHECK(cols1[3]    == 11);
    CHECK(cols1[4]    ==  3);
    CHECK(cols1[5]    == -1);
    CHECK(cols1[6]    ==  6);
    CHECK(cols1[7]    == 12);
    CHECK(cols1[8]    ==  7);
    CHECK(cols1[9]    ==  4);
    CHECK(cols1[10]   ==  5);
    CHECK(cols1[11]   == 13);

    CHECK_NOTHROW(cols1(0, 3));
    CHECK_THROWS (cols1(0, 4));
    CHECK_THROWS (cols1(1, 4));
    CHECK_THROWS (cols1(2, 4));
    CHECK_THROWS (cols1(3, 4));
    CHECK_THROWS (cols1(4, 4));
    CHECK_THROWS (cols1(5, 4));
    CHECK_NOTHROW(cols1(2, 0));
    CHECK_THROWS (cols1(3, 0));
    CHECK_THROWS (cols1(3, 1));
    CHECK_THROWS (cols1(3, 2));
    CHECK_THROWS (cols1(3, 3));
    CHECK_THROWS (cols1(3, 4));
    CHECK_NOTHROW(cols1[11]);
    CHECK_THROWS (cols1[12]);
    CHECK_THROWS (cols1[13]);

    DynamicMatrix<int> mat2 = { { 5, 7, 2,-4,11},
                                { 9, 3,-1, 6,12},
                                {-5, 7, 4, 5,13} };
    auto cols3 = columns(mat2, 3);
    CHECK(cols3.size()     == 6);
    CHECK(cols3.rowCount() == 3);
    CHECK(cols3.colCount() == 2);
    CHECK(cols3.shape()    == MatrixShape(3, 2));
    CHECK(cols3(0, 0) == -4);
    CHECK(cols3(0, 1) == 11);
    CHECK(cols3(1, 0) ==  6);
    CHECK(cols3(1, 1) == 12);
    CHECK(cols3(2, 0) ==  5);
    CHECK(cols3(2, 1) == 13);
    CHECK(cols3[0]    == -4);
    CHECK(cols3[1]    == 11);
    CHECK(cols3[2]    ==  6);
    CHECK(cols3[3]    == 12);
    CHECK(cols3[4]    ==  5);
    CHECK(cols3[5]    == 13);

    CHECK_NOTHROW(cols3(0, 1));
    CHECK_THROWS (cols3(0, 2));
    CHECK_THROWS (cols3(1, 2));
    CHECK_THROWS (cols3(2, 2));
    CHECK_THROWS (cols3(3, 2));
    CHECK_NOTHROW(cols3(2, 0));
    CHECK_THROWS (cols3(3, 0));
    CHECK_THROWS (cols3(3, 1));
    CHECK_THROWS (cols3(3, 2));
    CHECK_THROWS (cols3(3, 3));
    CHECK_THROWS (cols3(3, 4));
    CHECK_NOTHROW(cols3[5]);
    CHECK_THROWS (cols3[6]);
    CHECK_THROWS (cols3[7]);
}
