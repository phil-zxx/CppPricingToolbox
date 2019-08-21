#include <catch.hpp>
#include <iostream>

#include <toolbox/Algebra/Vectors.hpp>

using namespace Toolbox;



TEST_CASE("UnitTest_StaticVector", "[UnitTest_StaticVector]")
{
    using VectorType = StaticVector<double, 5>;

    const VectorType vec1{ { 5, 3, 2, 6, 9 } };
    const VectorType vec2{ { 7, 2, 9, 5, 1 } };

    CHECK(vec1[0] == 5);
    CHECK(vec1[1] == 3);
    CHECK(vec1[2] == 2);
    CHECK(vec1[3] == 6);
    CHECK(vec1[4] == 9);

    const VectorType expr1(vec1 + vec2);
    const VectorType vecTrue1{ {12, 5, 11, 11, 10} };
    CHECK(expr1.size() == 5);
    CHECK(expr1 == vecTrue1);

    const VectorType expr2(4 * ((-vec1 + vec2 / 8.) * 10 - vec1));
    const VectorType vecTrue2{ { -185, -122, -43, -239, -391 } };
    CHECK(expr2.size() == 5);
    CHECK(expr2 == vecTrue2);

    const VectorType expr3((-vec1 * vec2 / 2. + (vec1 - 5.) / vec2 - vec1) * 30 + 600);
    const VectorType vecTrue3{ { -75,   390, 260,  -24,  315 } };
    CHECK(expr3.size() == 5);
    CHECK(expr3 == vecTrue3);
}
