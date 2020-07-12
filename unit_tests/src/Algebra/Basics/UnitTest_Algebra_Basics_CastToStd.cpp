#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Basics_CastToStd")
{
    const StaticVector<int, 3> vecAlg1 = { 9,5,2 };
    CHECK(vecAlg1.colCount() == 1);
    CHECK(vecAlg1.rowCount() == 3);
    CHECK(vecAlg1.size() == 3);
    CHECK(vecAlg1[0]     == 9);
    CHECK(vecAlg1[1]     == 5);
    CHECK(vecAlg1[2]     == 2);
    CHECK(vecAlg1.at(0)  == 9);
    CHECK(vecAlg1.at(1)  == 5);
    CHECK(vecAlg1.at(2)  == 2);
    CHECK_THROWS(vecAlg1.at(3) == 0);

    const std::vector<int> vecStd = vecAlg1;
    CHECK(vecStd.size() == 3);
    CHECK(vecStd[0]     == 9);
    CHECK(vecStd[1]     == 5);
    CHECK(vecStd[2]     == 2);
    CHECK(vecStd.at(0)  == 9);
    CHECK(vecStd.at(1)  == 5);
    CHECK(vecStd.at(2)  == 2);
    CHECK_THROWS(vecStd.at(3) == 0);

    StaticVector<int, 3> vecAlg2 = vecStd;
    CHECK(vecAlg2.colCount() == 1);
    CHECK(vecAlg2.rowCount() == 3);
    CHECK(vecAlg2.size() == 3);
    CHECK(vecAlg2[0]     == 9);
    CHECK(vecAlg2[1]     == 5);
    CHECK(vecAlg2[2]     == 2);
    CHECK(vecAlg2.at(0)  == 9);
    CHECK(vecAlg2.at(1)  == 5);
    CHECK(vecAlg2.at(2)  == 2);
    CHECK_THROWS(vecAlg2.at(3) == 0);
}
