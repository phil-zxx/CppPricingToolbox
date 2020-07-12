#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Basics_Identity")
{
    const auto matI1 = DynamicMatrix<double>::createIdMatrix(3);
    const auto matI2 = DynamicMatrix<int>::createIdMatrix(4, 2);

    CHECK(matI1.size()     == 9);
    CHECK(matI1.rowCount() == 3);
    CHECK(matI1.colCount() == 3);
    CHECK(matI1.shape()    == MatrixShape(3, 3));
    CHECK(matI2.size()     == 8);
    CHECK(matI2.rowCount() == 4);
    CHECK(matI2.colCount() == 2);
    CHECK(matI2.shape()    == MatrixShape(4, 2));

    const auto matITrue1 = DynamicMatrix<int>{ {1,0,0},{0,1,0},{0,0,1} };
    CHECK(matI1 == matITrue1);
    CHECK(matI1 == trans(matI1));
    CHECK(matI1 == trans(trans(matI1)));

    const auto matITrue2 = DynamicMatrix<int>{ {1,0},{0,1},{0,0},{0,0} };
    CHECK(matI2 == matITrue2);
    CHECK(matI2 != trans(matI2));
    CHECK(matI2 == trans(trans(matI2)));

    CHECK(  diagonal(matI1) == 1);
    CHECK(  diagonal(matI2) == 1);
    CHECK(!(diagonal(matI1) != 1));
    CHECK(!(diagonal(matI2) != 1));

    for (size_t iRow = 0; iRow < 3; ++iRow)
        for (size_t iCol = 0; iCol < 3; ++iCol)
            CHECK(matI1(iRow, iCol) == (iRow == iCol ? 1 : 0));

    for (size_t iRow = 0; iRow < 4; ++iRow)
        for (size_t iCol = 0; iCol < 2; ++iCol)
            CHECK(matI2(iRow, iCol) == (iRow == iCol ? 1 : 0));
}
