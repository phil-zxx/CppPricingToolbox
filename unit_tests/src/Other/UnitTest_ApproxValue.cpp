#include <doctest/doctest.h>
#include <toolbox/Core/ApproxValue.hpp>
#include <sstream>

using namespace Toolbox;


TEST_CASE("UnitTest_ApproxValue")
{
    const ApproxValue approx1(123), approx2(1.23), approx3(std::sqrt(2)), approx4(std::sqrt(2), 1.e-4);

    std::ostringstream os1; os1 << approx1;
    CHECK(approx1   == 123);
    CHECK(os1.str() == "123");

    std::ostringstream os2; os2 << approx2;
    CHECK(approx2   == 1.23);
    CHECK(os2.str() == "1.23");

    std::ostringstream os3; os3 << approx3;
    CHECK(approx3   == 1.414213562373095);
    CHECK(os3.str() == "1.414213562373095");

    std::ostringstream os4; os4 << approx4;
    CHECK(approx4   == 1.41421);
    CHECK(approx4   != 1.41432);
    CHECK(os4.str() == "1.4142");
}
