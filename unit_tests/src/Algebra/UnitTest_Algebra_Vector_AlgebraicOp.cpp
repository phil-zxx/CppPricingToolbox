#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Vector_AlgebraicOp_MinMax")
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

TEST_CASE("UnitTest_Vector_AlgebraicOp_SumProd")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto sumResult1  = sum(DynamicVector<int>());
    const auto sumResult2  = sum(vecD);
    const auto prodResult1 = prod(StaticVector<int, 10>());
    const auto prodResult2 = prod(vecS);

    CHECK(sumResult1  == 0);
    CHECK(sumResult2  == 9);
    CHECK(prodResult1 == 1);
    CHECK(prodResult2 == -315);
}

TEST_CASE("UnitTest_Vector_AlgebraicOp_Dot")
{
    const StaticVector<int, 5> v1{ { 5, 4, 10, 6, -3 } };
    const DynamicVector<int>   v2{ { 2, 6, -4, 3, 12 } };

    const auto dotProduct = dot(v1, v2);
    CHECK(dotProduct == -24);

    const DynamicVector<int> v3{ { 2, 6, -4, 3 } };
    CHECK_NOTHROW(dot(v1, v2));
    CHECK_THROWS (dot(v1, v3));
    CHECK_THROWS (dot(v2, v3));
}

TEST_CASE("UnitTest_Vector_AlgebraicOp_DotInnerProd")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto dotProductDbl   = dot(vecS, vecD);
    const auto dotProductInt   = dot(vecS, asType<int>(vecD));
    const auto innerProductDbl = innerProduct(trans(vecS), vecD);
    const auto innerProductInt = innerProduct(trans(vecS), asType<int>(vecD));

    CHECK(dotProductDbl   == -11);
    CHECK(dotProductInt   == -11);
    CHECK(innerProductDbl == -11);
    CHECK(innerProductInt == -11);

    CHECK(std::string(typeid(dotProductDbl).name())   == "double");
    CHECK(std::string(typeid(dotProductInt).name())   == "int");
    CHECK(std::string(typeid(innerProductDbl).name()) == "double");
    CHECK(std::string(typeid(innerProductInt).name()) == "int");
}
