#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Expr_Power")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matP = power(mat, 3);

    CHECK(mat.size()      == 6);
    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(mat.shape()     == MatrixShape(3, 2));
    CHECK(matP.size()     == 6);
    CHECK(matP.rowCount() == 3);
    CHECK(matP.colCount() == 2);
    CHECK(matP.shape()    == MatrixShape(3, 2));

    CHECK(mat(0, 0) ==   -1); CHECK(matP(0, 0) ==       -1);
    CHECK(mat(0, 1) ==    8); CHECK(matP(0, 1) ==      512);
    CHECK(mat(1, 0) ==   27); CHECK(matP(1, 0) ==    19683);
    CHECK(mat(1, 1) ==   -8); CHECK(matP(1, 1) ==     -512);
    CHECK(mat(2, 0) == -125); CHECK(matP(2, 0) == -1953125);
    CHECK(mat(2, 1) ==  216); CHECK(matP(2, 1) == 10077696);
}
