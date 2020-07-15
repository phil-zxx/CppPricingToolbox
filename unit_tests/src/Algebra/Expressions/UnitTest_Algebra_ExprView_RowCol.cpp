#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_ExprView_Row")
{
    const DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    auto row0 = row(mat, 0);
    CHECK(row0.size()     == 3);
    CHECK(row0.rowCount() == 1);
    CHECK(row0.colCount() == 3);
    CHECK(row0.shape()    == MatrixShape(1, 3));
    CHECK(row0(0, 0) == 5);
    CHECK(row0(0, 1) == 7);
    CHECK(row0(0, 2) == 2);
    CHECK(row0[0]    == 5);
    CHECK(row0[1]    == 7);
    CHECK(row0[2]    == 2);

    const auto row1 = row(mat, 1);
    CHECK(row1.size()     == 3);
    CHECK(row1.rowCount() == 1);
    CHECK(row1.colCount() == 3);
    CHECK(row1.shape()    == MatrixShape(1, 3));
    CHECK(row1(0, 0) == 9);
    CHECK(row1(0, 1) == 3);
    CHECK(row1(0, 2) == 6);
    CHECK(row1[0]    == 9);
    CHECK(row1[1]    == 3);
    CHECK(row1[2]    == 6);
}

TEST_CASE("UnitTest_Algebra_ExprView_Col")
{
    const DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    auto col0 = column(mat, 0);
    CHECK(col0.size()     == 2);
    CHECK(col0.rowCount() == 2);
    CHECK(col0.colCount() == 1);
    CHECK(col0.shape()    == MatrixShape(2, 1));
    CHECK(col0(0, 0) == 5);
    CHECK(col0(1, 0) == 9);
    CHECK(col0[0]    == 5);
    CHECK(col0[1]    == 9);

    const auto col1 = column(mat, 1);
    CHECK(col1.size()     == 2);
    CHECK(col1.rowCount() == 2);
    CHECK(col1.colCount() == 1);
    CHECK(col1.shape()    == MatrixShape(2, 1));
    CHECK(col1(0, 0) == 7);
    CHECK(col1(1, 0) == 3);
    CHECK(col1[0]    == 7);
    CHECK(col1[1]    == 3);

    const auto col2 = column(mat, 2);
    CHECK(col2.size()     == 2);
    CHECK(col2.rowCount() == 2);
    CHECK(col2.colCount() == 1);
    CHECK(col2.shape()    == MatrixShape(2, 1));
    CHECK(col2(0, 0) == 2);
    CHECK(col2(1, 0) == 6);
    CHECK(col2[0]    == 2);
    CHECK(col2[1]    == 6);
}

TEST_CASE("UnitTest_Algebra_ExprView_RowCol")
{
    const DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    const auto rowCol = row(column(mat, 2), 1);
    CHECK(rowCol.size()     == 1);
    CHECK(rowCol.rowCount() == 1);
    CHECK(rowCol.colCount() == 1);
    CHECK(rowCol.shape()    == MatrixShape(1, 1));
    CHECK(rowCol(0, 0) == 6);
    CHECK(rowCol[0]    == 6);

    const auto colRow = column(row(mat, 1), 0);
    CHECK(colRow.size()     == 1);
    CHECK(colRow.rowCount() == 1);
    CHECK(colRow.colCount() == 1);
    CHECK(colRow.shape()    == MatrixShape(1, 1));
    CHECK(colRow(0, 0) == 9);
    CHECK(colRow[0]    == 9);
}

TEST_CASE("UnitTest_Algebra_ExprView_RowCol_Throw")
{
    const DynamicMatrix<int> mat = { {5,7,2},{9,3,6} };

    CHECK_NOTHROW(column(mat, 0));
    CHECK_NOTHROW(column(mat, 1));
    CHECK_NOTHROW(column(mat, 2));
    CHECK_THROWS (column(mat, 3));

    CHECK_NOTHROW(row(mat, 0));
    CHECK_NOTHROW(row(mat, 1));
    CHECK_THROWS (row(mat, 2));
    CHECK_THROWS (row(mat, 3));
}
