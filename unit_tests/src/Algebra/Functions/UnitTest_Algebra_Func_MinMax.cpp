#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Func_MinElMaxEl")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto minS = minEl(vecS);
    const auto minD = minEl(vecD);
    const auto minE = minEl(vecS + 3 * abs(vecD));
    CHECK(minS == -9);
    CHECK(minD == -3);
    CHECK(minE ==  6);

    const auto maxS = maxEl(vecS);
    const auto maxD = maxEl(vecD);
    const auto maxE = maxEl(vecS + 3 * abs(vecD));
    CHECK(maxS ==  7);
    CHECK(maxD ==  7);
    CHECK(maxE == 28);
}

TEST_CASE("UnitTest_Algebra_Func_ArgMinArgMax")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto argMinS = argMin(vecS);
    const auto argMinD = argMin(vecD);
    const auto argMinE = argMin(vecS + 3 * abs(vecD));
    CHECK(argMinS == 2);
    CHECK(argMinD == 0);
    CHECK(argMinE == 2);

    const auto argMaxS = argMax(vecS);
    const auto argMaxD = argMax(vecD);
    const auto argMaxE = argMax(vecS + 3 * abs(vecD));
    CHECK(argMaxS == 1);
    CHECK(argMaxD == 1);
    CHECK(argMaxE == 1);
}

TEST_CASE("UnitTest_Algebra_Func_argMaxFrom")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto argMax0 = argMaxFrom(vecS + 3 * abs(vecD), 0);
    const auto argMax1 = argMaxFrom(vecS + 3 * abs(vecD), 1);
    const auto argMax2 = argMaxFrom(vecS + 3 * abs(vecD), 2);
    CHECK(argMax0 == 1);
    CHECK(argMax1 == 1);
    CHECK(argMax2 == 2);

    const auto argMax3 = argMaxFrom(vecS - 5 * abs(vecD), 0);
    const auto argMax4 = argMaxFrom(vecS - 5 * abs(vecD), 1);
    const auto argMax5 = argMaxFrom(vecS - 5 * abs(vecD), 2);
    CHECK(argMax3 == 0);
    CHECK(argMax4 == 1);
    CHECK(argMax5 == 2);
}

TEST_CASE("UnitTest_Algebra_Func_MinMax_Throw")
{
    DynamicVector<double> v1, v2(3, 99);

    CHECK_THROWS(minEl(v1));
    CHECK_THROWS(maxEl(v1));
    CHECK_THROWS(argMin(v1));
    CHECK_THROWS(argMax(v1));

    CHECK_NOTHROW(minEl(v2));
    CHECK_NOTHROW(maxEl(v2));
    CHECK_NOTHROW(argMin(v2));
    CHECK_NOTHROW(argMax(v2));
}
