#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;



TEST_CASE("UnitTest_Algebra_ExprView_RowColDiag_Operator")
{
    DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    auto col2 = column(mat, 2);
    col2 *= 3;
    CHECK(mat == DynamicMatrix<int>{ {5,7,6},{9,3,18} });

    auto row1 = row(mat, 1);
    row1 *= 2;
    CHECK(mat == DynamicMatrix<int>{ {5,7,6},{18,6,36} });

    auto diag = diagonal(mat);
    diag *= 4;
    CHECK(mat == DynamicMatrix<int>{ {20,7,6},{18,24,36} });

    DynamicMatrix<int> mat2 = { {5,7},{2,9},{3,6} };
    auto diag2 = diagonal(mat2);
    diag2 *= 3;
    CHECK(mat2 == DynamicMatrix<int>{ {15,7},{2,27},{3,6} });
}


TEST_CASE("UnitTest_Algebra_ExprView_Diag")
{
    const DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    auto diag = diagonal(mat);
    CHECK(diag.size()     == 2);
    CHECK(diag.rowCount() == 2);
    CHECK(diag.colCount() == 1);
    CHECK(diag.shape()    == MatrixShape(2, 1));
    CHECK(diag(0, 0) == 5);
    CHECK(diag(1, 0) == 3);
    CHECK(diag[0]    == 5);
    CHECK(diag[1]    == 3);

    const auto diagDiag = diagonal(diag);
    CHECK(diagDiag.size()     == 1);
    CHECK(diagDiag.rowCount() == 1);
    CHECK(diagDiag.colCount() == 1);
    CHECK(diagDiag.shape()    == MatrixShape(1, 1));
    CHECK(diagDiag(0, 0) == 5);
    CHECK(diagDiag[0]    == 5);

    DynamicMatrix<double> mat2 = { {9,22,3},{1,-5,9} };
    CHECK(mat2[0]    == 9);
    CHECK(mat2(0, 0) == 9);
    CHECK(mat2 == DynamicMatrix<int>{ {9, 22, 3}, { 1,-5,9 } });
    diagonal(diagonal(mat2))[0] = 4;
    CHECK(mat2[0]    == 4);
    CHECK(mat2(0, 0) == 4);
    CHECK(mat2 == DynamicMatrix<int>{ {4, 22, 3}, { 1,-5,9 } });
}
