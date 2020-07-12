#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Expr_Trans1")
{
    const StaticMatrix<double, 2, 3> mat1{ {3,5,2},{6,4,9} };
    const StaticMatrix<double, 3, 2> mat2{ {3,6},{5,4},{2,9} };

    CHECK(trans(mat1) == mat2);
    CHECK(mat1 == trans(mat2));
}

TEST_CASE("UnitTest_Algebra_Expr_Trans2")
{
    const DynamicVector<int> vec = { {5,9,4} };
    const auto vecT = trans(vec);

    CHECK(vec.size()      == 3);
    CHECK(vec.rowCount()  == 3);
    CHECK(vec.colCount()  == 1);
    CHECK(vec.shape()     == MatrixShape(3, 1));
    CHECK(vecT.size()     == 3);
    CHECK(vecT.rowCount() == 1);
    CHECK(vecT.colCount() == 3);
    CHECK(vecT.shape()    == MatrixShape(1, 3));

    CHECK(vec(0, 0) == vecT(0, 0));
    CHECK(vec(1, 0) == vecT(0, 1));
    CHECK(vec(2, 0) == vecT(0, 2));
}

TEST_CASE("UnitTest_Algebra_Expr_Trans3")
{
    const DynamicMatrix<int> mat = { {9,8,7,6},{5,4,3,2},{-3,-2,-4,-7} };
    const auto matT  = trans(mat);
    const auto matTT = trans(trans(mat));

    CHECK(mat == matTT);
    CHECK(mat == trans(matT));

    CHECK(mat.size()       == 12);
    CHECK(mat.rowCount()   == 3);
    CHECK(mat.colCount()   == 4);
    CHECK(mat.shape()      == MatrixShape(3, 4));
    CHECK(matT.size()      == 12);
    CHECK(matT.rowCount()  == 4);
    CHECK(matT.colCount()  == 3);
    CHECK(matT.shape()     == MatrixShape(4, 3));
    CHECK(matTT.size()     == 12);
    CHECK(matTT.rowCount() == 3);
    CHECK(matTT.colCount() == 4);
    CHECK(matTT.shape()    == MatrixShape(3, 4));

    CHECK(mat(0, 0) == matT(0, 0));
    CHECK(mat(0, 1) == matT(1, 0));
    CHECK(mat(0, 2) == matT(2, 0));
    CHECK(mat(1, 0) == matT(0, 1));
    CHECK(mat(1, 1) == matT(1, 1));
    CHECK(mat(1, 2) == matT(2, 1));

    CHECK(matTT(0, 0) == mat(0, 0));
    CHECK(matTT(0, 1) == mat(0, 1));
    CHECK(matTT(0, 2) == mat(0, 2));
    CHECK(matTT(1, 0) == mat(1, 0));
    CHECK(matTT(1, 1) == mat(1, 1));
    CHECK(matTT(1, 2) == mat(1, 2));

    CHECK(matT(0, 0) ==  9); CHECK(matTT(0, 0) ==  9);
    CHECK(matT(0, 1) ==  5); CHECK(matTT(0, 1) ==  8);
    CHECK(matT(0, 2) == -3); CHECK(matTT(0, 2) ==  7);
    CHECK(matT(1, 0) ==  8); CHECK(matTT(0, 3) ==  6);
    CHECK(matT(1, 1) ==  4); CHECK(matTT(1, 0) ==  5);
    CHECK(matT(1, 2) == -2); CHECK(matTT(1, 1) ==  4);
    CHECK(matT(2, 0) ==  7); CHECK(matTT(1, 2) ==  3);
    CHECK(matT(2, 1) ==  3); CHECK(matTT(1, 3) ==  2);
    CHECK(matT(2, 2) == -4); CHECK(matTT(2, 0) == -3);
    CHECK(matT(3, 0) ==  6); CHECK(matTT(2, 1) == -2);
    CHECK(matT(3, 1) ==  2); CHECK(matTT(2, 2) == -4);
    CHECK(matT(3, 2) == -7); CHECK(matTT(2, 3) == -7);
}
