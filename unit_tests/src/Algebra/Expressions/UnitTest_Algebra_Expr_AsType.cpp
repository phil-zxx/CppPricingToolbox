#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Expr_AsType")
{
    const DynamicMatrix<double> mat = { {1.1, 2.2, 3.3},{4.4, 5.5, 6.6} };
    const auto matI = asType<int>(mat);

    CHECK(mat.size()      == 6);
    CHECK(mat.rowCount()  == 2);
    CHECK(mat.colCount()  == 3);
    CHECK(mat.shape()     == MatrixShape(2, 3));
    CHECK(matI.size()     == 6);
    CHECK(matI.rowCount() == 2);
    CHECK(matI.colCount() == 3);
    CHECK(matI.shape()    == MatrixShape(2, 3));

    CHECK(matI(0, 0) == 1);
    CHECK(matI(0, 1) == 2);
    CHECK(matI(0, 2) == 3);
    CHECK(matI(1, 0) == 4);
    CHECK(matI(1, 1) == 5);
    CHECK(matI(1, 2) == 6);
}
