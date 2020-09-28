#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <iostream>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Func_SwapRows")
{
    DynamicMatrix<double> M{ {4,5},{9,2},{7,6} };

    swapRows(M, 0, 0);
    CHECK(M == DynamicMatrix<double>{ {4,5},{9,2},{7,6} });

    swapRows(M, 2, 1);
    CHECK(M == DynamicMatrix<double>{ {4,5},{7,6},{9,2} });

    swapRows(M, 0, 1);
    CHECK(M == DynamicMatrix<double>{ {7,6},{4,5},{9,2} });

    swapRows(M, 1, 2);
    CHECK(M == DynamicMatrix<double>{ {7,6},{9,2},{4,5} });

    swapRows(M, 0, 2);
    CHECK(M == DynamicMatrix<double>{ {4,5},{9,2},{7,6} });

    CHECK_NOTHROW(swapRows(M, 0, 0));
    CHECK_NOTHROW(swapRows(M, 0, 1));
    CHECK_NOTHROW(swapRows(M, 0, 2));
    CHECK_NOTHROW(swapRows(M, 1, 0));
    CHECK_NOTHROW(swapRows(M, 1, 1));
    CHECK_NOTHROW(swapRows(M, 1, 2));
    CHECK_NOTHROW(swapRows(M, 2, 0));
    CHECK_NOTHROW(swapRows(M, 2, 1));
    CHECK_NOTHROW(swapRows(M, 2, 2));

    CHECK_THROWS(swapRows(M, 0, 3));
    CHECK_THROWS(swapRows(M, 1, 3));
    CHECK_THROWS(swapRows(M, 2, 3));
    CHECK_THROWS(swapRows(M, 3, 0));
    CHECK_THROWS(swapRows(M, 3, 1));
    CHECK_THROWS(swapRows(M, 3, 2));
    CHECK_THROWS(swapRows(M, 3, 3));
    CHECK_THROWS(swapRows(M, 4, 0));
}


TEST_CASE("UnitTest_Algebra_Func_SwapCols")
{
    DynamicMatrix<double> M{ {4,5,-2,45},{9,-5,2,6},{7,6,88,-2} };

    swapColumns(M, 1, 1);
    CHECK(M == DynamicMatrix<double>{ {4,5,-2,45},{9,-5,2,6},{7,6,88,-2} });

    swapColumns(M, 0, 1);
    CHECK(M == DynamicMatrix<double>{ {5,4,-2,45},{-5,9,2,6},{6,7,88,-2} });

    swapColumns(M, 2, 0);
    CHECK(M == DynamicMatrix<double>{ {-2,4,5,45},{2,9,-5,6},{88,7,6,-2} });

    swapColumns(M, 1, 3);
    CHECK(M == DynamicMatrix<double>{ {-2,45,5,4},{2,6,-5,9},{88,-2,6,7} });

    CHECK_NOTHROW(swapColumns(M, 0, 0));
    CHECK_NOTHROW(swapColumns(M, 0, 1));
    CHECK_NOTHROW(swapColumns(M, 0, 2));
    CHECK_NOTHROW(swapColumns(M, 0, 3));
    CHECK_NOTHROW(swapColumns(M, 1, 0));
    CHECK_NOTHROW(swapColumns(M, 1, 1));
    CHECK_NOTHROW(swapColumns(M, 1, 2));
    CHECK_NOTHROW(swapColumns(M, 1, 3));
    CHECK_NOTHROW(swapColumns(M, 2, 0));
    CHECK_NOTHROW(swapColumns(M, 2, 1));
    CHECK_NOTHROW(swapColumns(M, 2, 2));
    CHECK_NOTHROW(swapColumns(M, 2, 3));
    CHECK_NOTHROW(swapColumns(M, 3, 0));
    CHECK_NOTHROW(swapColumns(M, 3, 1));
    CHECK_NOTHROW(swapColumns(M, 3, 2));
    CHECK_NOTHROW(swapColumns(M, 3, 3));

    CHECK_THROWS(swapColumns(M, 0, 4));
    CHECK_THROWS(swapColumns(M, 1, 4));
    CHECK_THROWS(swapColumns(M, 2, 4));
    CHECK_THROWS(swapColumns(M, 3, 4));
    CHECK_THROWS(swapColumns(M, 4, 0));
    CHECK_THROWS(swapColumns(M, 4, 1));
    CHECK_THROWS(swapColumns(M, 4, 2));
    CHECK_THROWS(swapColumns(M, 4, 3));
    CHECK_THROWS(swapColumns(M, 4, 4));
    CHECK_THROWS(swapColumns(M, 5, 0));
}
