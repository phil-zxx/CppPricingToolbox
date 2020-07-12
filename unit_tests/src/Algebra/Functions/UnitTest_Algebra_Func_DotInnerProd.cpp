#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Func_Dot")
{
    const StaticVector<int, 5> v1{ { 5, 4, 10, 6, -3 } };
    const DynamicVector<int>   v2{ { 2, 6, -4, 3, 12 } };

    const auto dotProduct = dot(v1, v2);
    CHECK(dotProduct == -24);

    const DynamicVector<int> v3{ { 2, 6, -4, 3 } };
    CHECK_NOTHROW(dot(v1, v2));
    CHECK_THROWS (dot(v1, v3));
    CHECK_THROWS (dot(v2, v3));

    const StaticVector<int, 5> v4;
    const DynamicVector<int>   v5;
    CHECK(dot(v4, v5) == 0);
}

TEST_CASE("UnitTest_Algebra_Func_DotInnerProd")
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

    CHECK(typeid(dotProductDbl)   == typeid(double));
    CHECK(typeid(dotProductInt)   == typeid(int));
    CHECK(typeid(innerProductDbl) == typeid(double));
    CHECK(typeid(innerProductInt) == typeid(int));

    CHECK_NOTHROW(innerProduct(trans(vecS), vecD));
    CHECK_THROWS (innerProduct(vecS, vecD));
}
