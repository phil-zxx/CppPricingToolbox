#include <catch2/catch_test_macros.hpp>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Vector_BaseFunctions")
{
    const StaticVector<double, 10> vecS1(3), vecS2(3, 7);
    const DynamicVector<int> vecD(3, 5);

    CHECK(vecS1.capacity() == 10);
    CHECK(vecS1.size()     == 3);
    CHECK(vecS1.capacity() == vecS2.capacity());
    CHECK(vecS1.size()     == vecS2.size());
    CHECK(vecS1[0]         == 0.);
    CHECK(vecS1[1]         == 0.);
    CHECK(vecS1[2]         == 0.);
    CHECK(vecS2[0]         == 7.);
    CHECK(vecS2[1]         == 7.);
    CHECK(vecS2[2]         == 7.);
    CHECK(vecS1.at(2)      == 0.);
    CHECK(vecS2.at(2)      == 7.);
    CHECK_THROWS(vecS1.at(3));
    CHECK_THROWS(vecS2.at(3));

    CHECK(vecD.capacity() == 3);
    CHECK(vecD.size()     == 3);
    CHECK(vecD[0]         == 5);
    CHECK(vecD[1]         == 5);
    CHECK(vecD.at(2)      == 5);
    CHECK_THROWS(vecD.at(3));
}
