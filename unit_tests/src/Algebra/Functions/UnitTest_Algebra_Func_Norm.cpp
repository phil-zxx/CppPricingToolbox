#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Core/ApproxValue.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Func_Norm1")
{
    const StaticVector<int, 10> vec = { 9, -6, 1, 8, -4, 5, -1, 1 };

    CHECK(dot(vec, vec) == 225);
    CHECK(norm2(vec)    == 15);
    CHECK(norm(vec, 2)  == 15);

    CHECK(norm(vec, TB_INF_NEG)  == 1);
    CHECK(norm(vec, TB_INF_POS)  == 9);

    CHECK(ApproxValue(norm(vec, 3)) == 11.81426981871293);
    CHECK(ApproxValue(norm(vec, 4)) == 10.6442700752965);
}

TEST_CASE("UnitTest_Algebra_Func_Norm2")
{
    const StaticVector<int, 10> vec = { 11, -8, -95, 53, 42, -12 };

    CHECK(dot(vec, vec) == 13927);
    CHECK(norm2(vec)    == 118.0127111797708);
    CHECK(norm(vec, 2)  == 118.0127111797708);

    CHECK(norm(vec, TB_INF_NEG)  ==  8);
    CHECK(norm(vec, TB_INF_POS)  == 95);

    CHECK(ApproxValue(norm(vec, -100)) ==   8.0);
    CHECK(ApproxValue(norm(vec,  -10)) ==   7.9544672133026);
    CHECK(ApproxValue(norm(vec,   -5)) ==   7.5502658758220);
    CHECK(ApproxValue(norm(vec,   -1)) ==   2.8373125685530);
    CHECK(ApproxValue(norm(vec,    1)) == 221.0);
    CHECK(ApproxValue(norm(vec,    5)) ==  96.3121154535357);
    CHECK(ApproxValue(norm(vec,   10)) ==  95.0304151571379);
    CHECK(ApproxValue(norm(vec,  100)) ==  95.0);
}
