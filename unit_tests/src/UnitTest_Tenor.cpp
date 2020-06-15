#include <catch2/catch_test_macros.hpp>
#include <toolbox/Date/Tenor.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Tenor")
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    static_assert(TenorElement(3, 'D').count() == 3 && TenorElement(3, 'D').unit() == TenorUnit::D);
    static_assert(TenorElement(6, 'M').count() == 6 && TenorElement(6, 'M').unit() == TenorUnit::M);
    static_assert(TenorElement("3D").count()   == 3 && TenorElement("3D").unit()   == TenorUnit::D);
    static_assert(TenorElement("6M").count()   == 6 && TenorElement("6M").unit()   == TenorUnit::M);
}
