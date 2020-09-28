#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Op_Assignment")
{
    DynamicMatrix<double> mat = { {1,2},{3,4} };
    mat += mat;
    mat += -3;

    CHECK(mat(0, 0) == -1);
    CHECK(mat(0, 1) ==  1);
    CHECK(mat(1, 0) ==  3);
    CHECK(mat(1, 1) ==  5);
    CHECK(mat == DynamicMatrix<int>{ {-1,1},{3,5} });

    const auto expr = trans(4 * (mat * mat) - 50);
    CHECK(expr(0, 0) == -46);
    CHECK(expr(0, 1) == -14);
    CHECK(expr(1, 0) == -46);
    CHECK(expr(1, 1) ==  50);
    CHECK(expr == DynamicMatrix<int>{ {-46,-14},{-46,50} });

    mat *= expr;
    mat *= 5;
    CHECK(mat(0, 0) ==  230);
    CHECK(mat(0, 1) ==  -70);
    CHECK(mat(1, 0) == -690);
    CHECK(mat(1, 1) == 1250);
    CHECK(mat == DynamicMatrix<int>{ {230,-70},{-690,1250} });

    mat -= (2 * mat - 500);
    mat -= 120;
    CHECK(mat(0, 0) ==  150);
    CHECK(mat(0, 1) ==  450);
    CHECK(mat(1, 0) == 1070);
    CHECK(mat(1, 1) == -870);
    CHECK(mat == DynamicMatrix<int>{ {150,450},{1070,-870} });

    mat /= { {3,25},{107,15} };
    mat /= 2;
    CHECK(mat(0, 0) ==  25);
    CHECK(mat(0, 1) ==   9);
    CHECK(mat(1, 0) ==   5);
    CHECK(mat(1, 1) == -29);
    CHECK(mat == DynamicMatrix<int>{ {25,9},{5,-29} });
}
