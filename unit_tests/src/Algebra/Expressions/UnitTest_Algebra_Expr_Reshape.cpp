#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Expr_Reshape1")
{
    const DynamicVector<int> vec = { {5,9,4} };
    const auto vecR = reshape(vec, 1, 3);

    CHECK(vec == reshape(reshape(vec, 1, 3), 3, 1));
    CHECK(vec != reshape(vec, 1, 3));

    CHECK(vec.size()      == 3);
    CHECK(vec.rowCount()  == 3);
    CHECK(vec.colCount()  == 1);
    CHECK(vec.shape()     == MatrixShape(3, 1));
    CHECK(vecR.size()     == 3);
    CHECK(vecR.rowCount() == 1);
    CHECK(vecR.colCount() == 3);
    CHECK(vecR.shape()    == MatrixShape(1, 3));

    CHECK(vec(0, 0) == vecR(0, 0));
    CHECK(vec(1, 0) == vecR(0, 1));
    CHECK(vec(2, 0) == vecR(0, 2));

    CHECK(vecR(0, 0) == 5);
    CHECK(vecR(0, 1) == 9);
    CHECK(vecR(0, 2) == 4);

    CHECK(vecR[0] == 5);
    CHECK(vecR[1] == 9);
    CHECK(vecR[2] == 4);

    CHECK_NOTHROW(reshape(vec, 1, 3));
    CHECK_NOTHROW(reshape(vec, 3, 1));
    CHECK_THROWS (reshape(vec, 2, 3));
    CHECK_THROWS (reshape(vec, 3, 2));
}

TEST_CASE("UnitTest_Algebra_Expr_Reshape2")
{
    const DynamicVector<int> vec = { {5,9,4,3,7,8} };
    const auto vecR = reshape(vec, 3, 2);

    CHECK(vec        == reshape(reshape(vec, 3, 2), 6, 1));
    CHECK(trans(vec) == reshape(reshape(vec, 2, 3), 1, 6));
    CHECK(vec        == trans(reshape(reshape(vec, 2, 3), 1, 6)));
    CHECK(vec        != reshape(vec, 1, 6));

    CHECK(vec.size()      == 6);
    CHECK(vec.rowCount()  == 6);
    CHECK(vec.colCount()  == 1);
    CHECK(vec.shape()     == MatrixShape(6, 1));
    CHECK(vecR.size()     == 6);
    CHECK(vecR.rowCount() == 3);
    CHECK(vecR.colCount() == 2);
    CHECK(vecR.shape()    == MatrixShape(3, 2));

    CHECK(vec(0, 0) == vecR(0, 0));
    CHECK(vec(1, 0) == vecR(0, 1));
    CHECK(vec(2, 0) == vecR(1, 0));
    CHECK(vec(3, 0) == vecR(1, 1));
    CHECK(vec(4, 0) == vecR(2, 0));
    CHECK(vec(5, 0) == vecR(2, 1));

    CHECK(vecR(0, 0) == 5);
    CHECK(vecR(0, 1) == 9);
    CHECK(vecR(1, 0) == 4);
    CHECK(vecR(1, 1) == 3);
    CHECK(vecR(2, 0) == 7);
    CHECK(vecR(2, 1) == 8);

    CHECK(vecR[0] == 5);
    CHECK(vecR[1] == 9);
    CHECK(vecR[2] == 4);
    CHECK(vecR[3] == 3);
    CHECK(vecR[4] == 7);
    CHECK(vecR[5] == 8);

    CHECK_NOTHROW(reshape(vec, 1, 6));
    CHECK_NOTHROW(reshape(vec, 2, 3));
    CHECK_NOTHROW(reshape(vec, 3, 2));
    CHECK_NOTHROW(reshape(vec, 6, 1));
    CHECK_THROWS (reshape(vec, 2, 2));
    CHECK_THROWS (reshape(vec, 1, 5));
}

TEST_CASE("UnitTest_Algebra_Expr_Reshape3")
{
    const DynamicMatrix<int> mat = { {9,8,7,6},{5,4,3,2},{-3,-2,-4,-7} };
    const auto matR = reshape(mat, 2, 6);

    CHECK(mat == reshape(reshape(reshape(mat, 2, 6), 12, 1), 3, 4));
    CHECK(mat != reshape(reshape(reshape(mat, 2, 6), 12, 1), 4, 3));

    CHECK(mat.size()       == 12);
    CHECK(mat.rowCount()   == 3);
    CHECK(mat.colCount()   == 4);
    CHECK(mat.shape()      == MatrixShape(3, 4));
    CHECK(matR.size()      == 12);
    CHECK(matR.rowCount()  == 2);
    CHECK(matR.colCount()  == 6);
    CHECK(matR.shape()     == MatrixShape(2, 6));

    CHECK(mat(0, 0) == matR(0, 0));
    CHECK(mat(0, 1) == matR(0, 1));
    CHECK(mat(0, 2) == matR(0, 2));
    CHECK(mat(0, 3) == matR(0, 3));
    CHECK(mat(1, 0) == matR(0, 4));
    CHECK(mat(1, 1) == matR(0, 5));
    CHECK(mat(1, 2) == matR(1, 0));
    CHECK(mat(1, 3) == matR(1, 1));
    CHECK(mat(2, 0) == matR(1, 2));
    CHECK(mat(2, 1) == matR(1, 3));
    CHECK(mat(2, 2) == matR(1, 4));
    CHECK(mat(2, 3) == matR(1, 5));

    CHECK(matR(0, 0) ==  9);
    CHECK(matR(0, 1) ==  8);
    CHECK(matR(0, 2) ==  7);
    CHECK(matR(0, 3) ==  6);
    CHECK(matR(0, 4) ==  5);
    CHECK(matR(0, 5) ==  4);
    CHECK(matR(1, 0) ==  3);
    CHECK(matR(1, 1) ==  2);
    CHECK(matR(1, 2) == -3);
    CHECK(matR(1, 3) == -2);
    CHECK(matR(1, 4) == -4);
    CHECK(matR(1, 5) == -7);

    CHECK(matR[ 0] ==  9);
    CHECK(matR[ 1] ==  8);
    CHECK(matR[ 2] ==  7);
    CHECK(matR[ 3] ==  6);
    CHECK(matR[ 4] ==  5);
    CHECK(matR[ 5] ==  4);
    CHECK(matR[ 6] ==  3);
    CHECK(matR[ 7] ==  2);
    CHECK(matR[ 8] == -3);
    CHECK(matR[ 9] == -2);
    CHECK(matR[10] == -4);
    CHECK(matR[11] == -7);

    CHECK_NOTHROW(reshape(mat,  1, 12));
    CHECK_NOTHROW(reshape(mat,  2,  6));
    CHECK_NOTHROW(reshape(mat,  3,  4));
    CHECK_NOTHROW(reshape(mat,  4,  3));
    CHECK_NOTHROW(reshape(mat,  6,  2));
    CHECK_NOTHROW(reshape(mat, 12,  1));
    CHECK_THROWS (reshape(mat, 3, 1));
    CHECK_THROWS (reshape(mat, 1, 13));
    CHECK_THROWS (reshape(mat, 5, 8));
}
