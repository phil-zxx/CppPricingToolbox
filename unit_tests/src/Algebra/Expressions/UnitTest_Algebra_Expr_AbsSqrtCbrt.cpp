#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Core/ApproxValue.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Expr_Abs")
{
    const DynamicMatrix<int> mat = { {-1, 2},{3, -4},{-5,6},{-7,8} };
    const auto matA = abs(mat);

    CHECK(mat.size()      == 8);
    CHECK(mat.rowCount()  == 4);
    CHECK(mat.colCount()  == 2);
    CHECK(mat.shape()     == MatrixShape(4, 2));
    CHECK(matA.size()     == 8);
    CHECK(matA.rowCount() == 4);
    CHECK(matA.colCount() == 2);
    CHECK(matA.shape()    == MatrixShape(4, 2));

    CHECK(mat(0, 0) == -1); CHECK(matA(0, 0) == 1);
    CHECK(mat(0, 1) ==  2); CHECK(matA(0, 1) == 2);
    CHECK(mat(1, 0) ==  3); CHECK(matA(1, 0) == 3);
    CHECK(mat(1, 1) == -4); CHECK(matA(1, 1) == 4);
    CHECK(mat(2, 0) == -5); CHECK(matA(2, 0) == 5);
    CHECK(mat(2, 1) ==  6); CHECK(matA(2, 1) == 6);
    CHECK(mat(3, 0) == -7); CHECK(matA(3, 0) == 7);
    CHECK(mat(3, 1) ==  8); CHECK(matA(3, 1) == 8);
}

TEST_CASE("UnitTest_Algebra_Expr_Sqrt")
{
    const DynamicMatrix<int> mat = { {-1,4},{9,-4},{-5,36} };
    const auto matS = sqrt(mat);

    CHECK(mat.size()      == 6);
    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(mat.shape()     == MatrixShape(3, 2));
    CHECK(matS.size()     == 6);
    CHECK(matS.rowCount() == 3);
    CHECK(matS.colCount() == 2);
    CHECK(matS.shape()    == MatrixShape(3, 2));

    CHECK(mat(0, 0) == -1); CHECK(std::isnan(matS(0, 0)));
    CHECK(mat(0, 1) ==  4); CHECK(matS(0, 1) == 2);
    CHECK(mat(1, 0) ==  9); CHECK(matS(1, 0) == 3);
    CHECK(mat(1, 1) == -4); CHECK(std::isnan(matS(1, 1)));
    CHECK(mat(2, 0) == -5); CHECK(std::isnan(matS(2, 0)));
    CHECK(mat(2, 1) == 36); CHECK(matS(2, 1) == 6);
}

TEST_CASE("UnitTest_Algebra_Expr_Cbrt")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matC = cbrt(mat);

    CHECK(mat.size()      == 6);
    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(mat.shape()     == MatrixShape(3, 2));
    CHECK(matC.size()     == 6);
    CHECK(matC.rowCount() == 3);
    CHECK(matC.colCount() == 2);
    CHECK(matC.shape()    == MatrixShape(3, 2));

    CHECK(mat(0, 0) ==   -1); CHECK(ApproxValue(matC(0, 0)) == -1);
    CHECK(mat(0, 1) ==    8); CHECK(ApproxValue(matC(0, 1)) ==  2);
    CHECK(mat(1, 0) ==   27); CHECK(ApproxValue(matC(1, 0)) ==  3);
    CHECK(mat(1, 1) ==   -8); CHECK(ApproxValue(matC(1, 1)) == -2);
    CHECK(mat(2, 0) == -125); CHECK(ApproxValue(matC(2, 0)) == -5);
    CHECK(mat(2, 1) ==  216); CHECK(ApproxValue(matC(2, 1)) ==  6);
}
