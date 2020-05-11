#include <catch2/catch.hpp>
#include <iostream>

#include <toolbox/Core/Decimal.hpp>
#include <toolbox/Core/decimal.h>

using namespace Toolbox;


TEST_CASE("UnitTest_Decimal")
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    constexpr Decimal<3> d1(1234.567);
    constexpr Decimal<3> d2(6789.345);

    static_assert(d1 + d2 ==    8023.912);
    static_assert(d1 - d2 ==   -5554.778);
    static_assert(d1 * d2 == 8381901.289);
    static_assert(d1 / d2 ==       0.182);
    
    static_assert(!(d1 + d2 !=    8023.912));
    static_assert(!(d1 - d2 !=   -5554.778));
    static_assert(!(d1 * d2 != 8381901.289));
    static_assert(!(d1 / d2 !=       0.182));

    static_assert(d1 + d2 !=    8023.912 + 0.1);
    static_assert(d1 - d2 !=   -5554.778 + 0.1);
    static_assert(d1 * d2 != 8381901.289 + 0.1);
    static_assert(d1 / d2 !=       0.182 + 0.1);

    static_assert(!(d1 + d2 ==    8023.912 + 0.1));
    static_assert(!(d1 - d2 ==   -5554.778 + 0.1));
    static_assert(!(d1 * d2 == 8381901.289 + 0.1));
    static_assert(!(d1 / d2 ==       0.182 + 0.1));

    constexpr Decimal<8> d3(99.12345678);
    static_assert(d3.toDouble() == 99.12345678);

    static_assert(d1 < d2);
    static_assert(d1 <= d2);
    static_assert(!(d1 > d2));
    static_assert(!(d1 >= d2));
    static_assert(d1 <= d1);
    static_assert(d1 >= d1);

    static_assert(d1 *  2 == 2469.134     );
    static_assert(d3 / 10 ==    9.91234568);
}
