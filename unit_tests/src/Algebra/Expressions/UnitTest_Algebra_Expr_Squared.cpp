#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Expr_Squared")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matS = squared(mat);

    CHECK(mat.size()      == 6);
    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(mat.shape()     == MatrixShape(3, 2));
    CHECK(matS.size()     == 6);
    CHECK(matS.rowCount() == 3);
    CHECK(matS.colCount() == 2);
    CHECK(matS.shape()    == MatrixShape(3, 2));

    CHECK(mat(0, 0) ==   -1); CHECK(matS(0, 0) ==     1);
    CHECK(mat(0, 1) ==    8); CHECK(matS(0, 1) ==    64);
    CHECK(mat(1, 0) ==   27); CHECK(matS(1, 0) ==   729);
    CHECK(mat(1, 1) ==   -8); CHECK(matS(1, 1) ==    64);
    CHECK(mat(2, 0) == -125); CHECK(matS(2, 0) == 15625);
    CHECK(mat(2, 1) ==  216); CHECK(matS(2, 1) == 46656);
}
