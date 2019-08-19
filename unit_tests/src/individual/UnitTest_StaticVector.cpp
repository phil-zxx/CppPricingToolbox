#include <catch.hpp>

#include <toolbox/Algebra/Vectors.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_StaticVector", "[UnitTest_StaticVector]")
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    using StaticVectorInt = StaticVector<int, 5>;

    constexpr int vec[5] = { 5, 3, 2, 6, 9 };
    constexpr const StaticVectorInt v1(vec);
    constexpr const StaticVectorInt v2(vec);

    static_assert(v1.size() == 5);
    static_assert(v1[0] == vec[0]);
    static_assert(v1[1] == vec[1]);
    static_assert(v1[2] == vec[2]);
    static_assert(v1[3] == vec[3]);
    static_assert(v1[4] == vec[4]);

    auto expr = -v1;

    StaticVectorInt v3(expr);

    //constexpr static auto expr = v1 + v2;
    //constexpr static auto ss = expr.size();

    //constexpr auto aa = expr[0];
    //static_assert(expr[0] == 10);

    //constexpr StaticVectorInt v2(expr);

    //static_assert(expr[0] == 10);
}
