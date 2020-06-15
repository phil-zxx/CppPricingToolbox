#include <catch2/catch_test_macros.hpp>
#include <toolbox/Date/DateTime.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_DateTime")
{
    static_assert(DateTime().toInt() == 0);
    static_assert(DateTime(2029, 6, 21).toInt() == 47290);
    static_assert(DateTime(2029, 6, 21).hasTime() == false);

    constexpr DateTime d1(2029, 11, 30, 12, 30, 59);
    static_assert(d1.hasTime());
    static_assert(d1.ymd() == Date::YearMonthDay{ 2029,11,30 });
    static_assert(d1.hour() == 12 && d1.minute() == 30 && d1.second() == 59 && d1.nano() == 0);
    static_assert(d1.totalSeconds() == (12*3600 + 30*60 + 59));
    static_assert(d1.totalNanos()   == (12*3600 + 30*60 + 59) * 1'000'000'000LL);

    static_assert(d1.isNull() == false);
    static_assert(d1.toDouble() == Date(2029,11,30).toInt() + (12 * 3600 + 30 * 60 + 59) / (24 * 3600.));

    constexpr DateTime d2("2029-11-30 12:30:59");
    static_assert(d2.hasTime());
    static_assert(d2.ymd() == Date::YearMonthDay{ 2029,11,30 });
    static_assert(d2.hour() == 12 && d2.minute() == 30 && d2.second() == 59 && d2.nano() == 0);
    static_assert(d2.totalSeconds() == (12*3600 + 30*60 + 59));
    static_assert(d2.totalNanos()   == (12*3600 + 30*60 + 59) * 1'000'000'000LL);

    static_assert(d2.isNull() == false);
    static_assert(d2.toDouble() == Date(2029,11,30).toInt() + (12 * 3600 + 30 * 60 + 59) / (24 * 3600.));
}
