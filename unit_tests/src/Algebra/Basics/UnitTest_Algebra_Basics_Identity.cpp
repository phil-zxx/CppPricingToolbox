#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Basics_Identity_Square")
{
    const auto matI = DynamicMatrix<double>::Identity(3);

    CHECK(matI.size()     == 9);
    CHECK(matI.rowCount() == 3);
    CHECK(matI.colCount() == 3);
    CHECK(matI.shape()    == MatrixShape(3, 3));

    const auto matITrue1 = DynamicMatrix<int>{ {1,0,0},{0,1,0},{0,0,1} };
    CHECK(matI == matITrue1);
    CHECK(matI == trans(matI));
    CHECK(matI == trans(trans(matI)));

    CHECK(matI[0] == 1); CHECK(matI.at(0) == 1);
    CHECK(matI[1] == 0); CHECK(matI.at(1) == 0);
    CHECK(matI[2] == 0); CHECK(matI.at(2) == 0);
    CHECK(matI[3] == 0); CHECK(matI.at(3) == 0);
    CHECK(matI[4] == 1); CHECK(matI.at(4) == 1);
    CHECK(matI[5] == 0); CHECK(matI.at(5) == 0);
    CHECK(matI[6] == 0); CHECK(matI.at(6) == 0);
    CHECK(matI[7] == 0); CHECK(matI.at(7) == 0);
    CHECK(matI[8] == 1); CHECK(matI.at(8) == 1);

    CHECK_NOTHROW(matI.at(8));
    CHECK_THROWS (matI.at(9));

    CHECK(  diagonal(matI) == 1);
    CHECK(!(diagonal(matI) != 1));

    for (size_t iRow = 0; iRow < 3; ++iRow)
        for (size_t iCol = 0; iCol < 3; ++iCol)
            CHECK(matI(iRow, iCol) == (iRow == iCol ? 1 : 0));
}

TEST_CASE("UnitTest_Algebra_Basics_Identity_NonSquare")
{
    const auto matI = DynamicMatrix<int>::Identity(4, 2);

    CHECK(matI.size()     == 8);
    CHECK(matI.rowCount() == 4);
    CHECK(matI.colCount() == 2);
    CHECK(matI.shape()    == MatrixShape(4, 2));

    const auto matITrue2 = DynamicMatrix<int>{ {1,0},{0,1},{0,0},{0,0} };
    CHECK(matI == matITrue2);
    CHECK(matI != trans(matI));
    CHECK(matI == trans(trans(matI)));

    CHECK(matI[0] == 1); CHECK(matI.at(0) == 1);
    CHECK(matI[1] == 0); CHECK(matI.at(1) == 0);
    CHECK(matI[2] == 0); CHECK(matI.at(2) == 0);
    CHECK(matI[3] == 1); CHECK(matI.at(3) == 1);
    CHECK(matI[4] == 0); CHECK(matI.at(4) == 0);
    CHECK(matI[5] == 0); CHECK(matI.at(5) == 0);
    CHECK(matI[6] == 0); CHECK(matI.at(6) == 0);
    CHECK(matI[7] == 0); CHECK(matI.at(7) == 0);

    CHECK_NOTHROW(matI.at(7));
    CHECK_THROWS (matI.at(8));

    CHECK(  diagonal(matI) == 1);
    CHECK(!(diagonal(matI) != 1));

    for (size_t iRow = 0; iRow < 4; ++iRow)
        for (size_t iCol = 0; iCol < 2; ++iCol)
            CHECK(matI(iRow, iCol) == (iRow == iCol ? 1 : 0));
}
