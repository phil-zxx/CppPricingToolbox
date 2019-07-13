#include <toolbox/Date/Date.hpp>

using namespace Toolbox;


int main()
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    static_assert(Date().isNull() == true);
    static_assert(Date().toInt() == 0);
    static_assert(Date(2029, 6, 21).toInt() == 47290);
    static_assert(Date(2029, 6, 21).isNull() == false);

    static_assert(Date(2029, 6, 21).year()  == 2029 && Date("2029-06-21").year()  == 2029);
    static_assert(Date(2029, 6, 21).month() == 6    && Date("2029-06-21").month() == 6);
    static_assert(Date(2029, 6, 21).day()   == 21   && Date("2029-06-21").day()   == 21);

    static_assert(Date(1899, 12, 30).totalDays() == Date().totalDays()  && Date().ymd()  == Date::YearMonthDay{1899, 12, 30});
    static_assert(Date(1899, 12, 30).totalDays() == Date(0).totalDays() && Date(0).ymd() == Date::YearMonthDay{1899, 12, 30});
    static_assert(Date(1899, 12, 31).totalDays() == Date(1).totalDays() && Date(1).ymd() == Date::YearMonthDay{1899, 12, 31});
    static_assert(Date(1900,  1,  1).totalDays() == Date(2).totalDays() && Date(2).ymd() == Date::YearMonthDay{1900,  1,  1});
    
    static_assert(Date(2029, 1, 1)++ == Date(2029, 1, 1));
    static_assert(Date(2029, 1, 2)-- == Date(2029, 1, 2));
    static_assert(++Date(2029, 1, 1) == Date(2029, 1, 2));
    static_assert(--Date(2029, 1, 2) == Date(2029, 1, 1));
    
    static_assert(Date(2029, 1, 1) != Date(2029, 1, 2));
    static_assert(Date(2029, 1, 2) >= Date(2029, 1, 2));
    static_assert(Date(2029, 1, 2) >= Date(2029, 1, 1));
    static_assert(Date(2029, 1, 1) <= Date(2029, 1, 2));
    static_assert(Date(2029, 1, 1) <= Date(2029, 1, 1));
    static_assert(Date(2029, 1, 2) >  Date(2029, 1, 1));
    static_assert(Date(2029, 1, 1) <  Date(2029, 1, 2));

    static_assert(Date(2024, 1, 1).dayOfWeek() == 0);
    static_assert(Date(2024, 3,12).dayOfWeek() == 1);
    static_assert(Date(2024, 5,22).dayOfWeek() == 2);
    static_assert(Date(2024, 8, 1).dayOfWeek() == 3);
    static_assert(Date(2024,10,11).dayOfWeek() == 4);
    static_assert(Date(2024,12,21).dayOfWeek() == 5);
    static_assert(Date(2025, 3, 2).dayOfWeek() == 6);
    
    constexpr Date a1("2029-06-21"); static_assert(a1.totalDays() == 47290 && a1.ymd() == Date::YearMonthDay{ 2029, 6,21 });
    constexpr Date a2("2028-08-24"); static_assert(a2.totalDays() == 46989 && a2.ymd() == Date::YearMonthDay{ 2028, 8,24 });
    constexpr Date a3("2027-10-28"); static_assert(a3.totalDays() == 46688 && a3.ymd() == Date::YearMonthDay{ 2027,10,28 });
    constexpr Date a4("2026-12-31"); static_assert(a4.totalDays() == 46387 && a4.ymd() == Date::YearMonthDay{ 2026,12,31 });
    constexpr Date a5("2026-03-05"); static_assert(a5.totalDays() == 46086 && a5.ymd() == Date::YearMonthDay{ 2026, 3, 5 });
    constexpr Date a6("2025-05-08"); static_assert(a6.totalDays() == 45785 && a6.ymd() == Date::YearMonthDay{ 2025, 5, 8 });
    
    constexpr Date b1("20290621"); static_assert(b1.totalDays() == 47290 && b1.ymd() == Date::YearMonthDay{ 2029, 6,21 });
    constexpr Date b2("20280824"); static_assert(b2.totalDays() == 46989 && b2.ymd() == Date::YearMonthDay{ 2028, 8,24 });
    constexpr Date b3("20271028"); static_assert(b3.totalDays() == 46688 && b3.ymd() == Date::YearMonthDay{ 2027,10,28 });
    constexpr Date b4("20261231"); static_assert(b4.totalDays() == 46387 && b4.ymd() == Date::YearMonthDay{ 2026,12,31 });
    constexpr Date b5("20260305"); static_assert(b5.totalDays() == 46086 && b5.ymd() == Date::YearMonthDay{ 2026, 3, 5 });
    constexpr Date b6("20250508"); static_assert(b6.totalDays() == 45785 && b6.ymd() == Date::YearMonthDay{ 2025, 5, 8 });

    static_assert(Date(2029, 6,21).totalDays() == 47290 && Date(47290).ymd() == Date::YearMonthDay{2029, 6,21});
    static_assert(Date(2028, 8,24).totalDays() == 46989 && Date(46989).ymd() == Date::YearMonthDay{2028, 8,24});
    static_assert(Date(2027,10,28).totalDays() == 46688 && Date(46688).ymd() == Date::YearMonthDay{2027,10,28});
    static_assert(Date(2026,12,31).totalDays() == 46387 && Date(46387).ymd() == Date::YearMonthDay{2026,12,31});
    static_assert(Date(2026, 3, 5).totalDays() == 46086 && Date(46086).ymd() == Date::YearMonthDay{2026, 3, 5});
    static_assert(Date(2025, 5, 8).totalDays() == 45785 && Date(45785).ymd() == Date::YearMonthDay{2025, 5, 8});
    static_assert(Date(2024, 7,11).totalDays() == 45484 && Date(45484).ymd() == Date::YearMonthDay{2024, 7,11});
    static_assert(Date(2023, 9,14).totalDays() == 45183 && Date(45183).ymd() == Date::YearMonthDay{2023, 9,14});
    static_assert(Date(2022,11,17).totalDays() == 44882 && Date(44882).ymd() == Date::YearMonthDay{2022,11,17});
    static_assert(Date(2022, 1,20).totalDays() == 44581 && Date(44581).ymd() == Date::YearMonthDay{2022, 1,20});
    static_assert(Date(2021, 3,25).totalDays() == 44280 && Date(44280).ymd() == Date::YearMonthDay{2021, 3,25});
    static_assert(Date(2020, 5,28).totalDays() == 43979 && Date(43979).ymd() == Date::YearMonthDay{2020, 5,28});
    static_assert(Date(2019, 8, 1).totalDays() == 43678 && Date(43678).ymd() == Date::YearMonthDay{2019, 8, 1});
    static_assert(Date(2018,10, 4).totalDays() == 43377 && Date(43377).ymd() == Date::YearMonthDay{2018,10, 4});
    static_assert(Date(2017,12, 7).totalDays() == 43076 && Date(43076).ymd() == Date::YearMonthDay{2017,12, 7});
    static_assert(Date(2017, 2, 9).totalDays() == 42775 && Date(42775).ymd() == Date::YearMonthDay{2017, 2, 9});
    static_assert(Date(2016, 4,14).totalDays() == 42474 && Date(42474).ymd() == Date::YearMonthDay{2016, 4,14});
    static_assert(Date(2015, 6,18).totalDays() == 42173 && Date(42173).ymd() == Date::YearMonthDay{2015, 6,18});
    static_assert(Date(2014, 8,21).totalDays() == 41872 && Date(41872).ymd() == Date::YearMonthDay{2014, 8,21});
    static_assert(Date(2013,10,24).totalDays() == 41571 && Date(41571).ymd() == Date::YearMonthDay{2013,10,24});
    static_assert(Date(2012,12,27).totalDays() == 41270 && Date(41270).ymd() == Date::YearMonthDay{2012,12,27});
    static_assert(Date(2012, 3, 1).totalDays() == 40969 && Date(40969).ymd() == Date::YearMonthDay{2012, 3, 1});
    static_assert(Date(2011, 5, 5).totalDays() == 40668 && Date(40668).ymd() == Date::YearMonthDay{2011, 5, 5});
    static_assert(Date(2010, 7, 8).totalDays() == 40367 && Date(40367).ymd() == Date::YearMonthDay{2010, 7, 8});
    static_assert(Date(2009, 9,10).totalDays() == 40066 && Date(40066).ymd() == Date::YearMonthDay{2009, 9,10});
    static_assert(Date(2008,11,13).totalDays() == 39765 && Date(39765).ymd() == Date::YearMonthDay{2008,11,13});
    static_assert(Date(2008, 1,17).totalDays() == 39464 && Date(39464).ymd() == Date::YearMonthDay{2008, 1,17});
    static_assert(Date(2007, 3,22).totalDays() == 39163 && Date(39163).ymd() == Date::YearMonthDay{2007, 3,22});
    static_assert(Date(2006, 5,25).totalDays() == 38862 && Date(38862).ymd() == Date::YearMonthDay{2006, 5,25});
    static_assert(Date(2005, 7,28).totalDays() == 38561 && Date(38561).ymd() == Date::YearMonthDay{2005, 7,28});
    static_assert(Date(2004, 9,30).totalDays() == 38260 && Date(38260).ymd() == Date::YearMonthDay{2004, 9,30});
    static_assert(Date(2003,12, 4).totalDays() == 37959 && Date(37959).ymd() == Date::YearMonthDay{2003,12, 4});
    static_assert(Date(2003, 2, 6).totalDays() == 37658 && Date(37658).ymd() == Date::YearMonthDay{2003, 2, 6});
    static_assert(Date(2002, 4,11).totalDays() == 37357 && Date(37357).ymd() == Date::YearMonthDay{2002, 4,11});
    static_assert(Date(2001, 6,14).totalDays() == 37056 && Date(37056).ymd() == Date::YearMonthDay{2001, 6,14});
    static_assert(Date(2000, 8,17).totalDays() == 36755 && Date(36755).ymd() == Date::YearMonthDay{2000, 8,17});
    static_assert(Date(1999,10,21).totalDays() == 36454 && Date(36454).ymd() == Date::YearMonthDay{1999,10,21});
    static_assert(Date(1998,12,24).totalDays() == 36153 && Date(36153).ymd() == Date::YearMonthDay{1998,12,24});
    static_assert(Date(1998, 2,26).totalDays() == 35852 && Date(35852).ymd() == Date::YearMonthDay{1998, 2,26});
    static_assert(Date(1997, 5, 1).totalDays() == 35551 && Date(35551).ymd() == Date::YearMonthDay{1997, 5, 1});
    static_assert(Date(1996, 7, 4).totalDays() == 35250 && Date(35250).ymd() == Date::YearMonthDay{1996, 7, 4});
    static_assert(Date(1995, 9, 7).totalDays() == 34949 && Date(34949).ymd() == Date::YearMonthDay{1995, 9, 7});
    static_assert(Date(1994,11,10).totalDays() == 34648 && Date(34648).ymd() == Date::YearMonthDay{1994,11,10});
    static_assert(Date(1994, 1,13).totalDays() == 34347 && Date(34347).ymd() == Date::YearMonthDay{1994, 1,13});
    static_assert(Date(1993, 3,18).totalDays() == 34046 && Date(34046).ymd() == Date::YearMonthDay{1993, 3,18});
    static_assert(Date(1992, 5,21).totalDays() == 33745 && Date(33745).ymd() == Date::YearMonthDay{1992, 5,21});
    static_assert(Date(1991, 7,25).totalDays() == 33444 && Date(33444).ymd() == Date::YearMonthDay{1991, 7,25});
    static_assert(Date(1990, 9,27).totalDays() == 33143 && Date(33143).ymd() == Date::YearMonthDay{1990, 9,27});
    static_assert(Date(1989,11,30).totalDays() == 32842 && Date(32842).ymd() == Date::YearMonthDay{1989,11,30});
    static_assert(Date(1989, 2, 2).totalDays() == 32541 && Date(32541).ymd() == Date::YearMonthDay{1989, 2, 2});
    static_assert(Date(1988, 4, 7).totalDays() == 32240 && Date(32240).ymd() == Date::YearMonthDay{1988, 4, 7});

    return 0;
}
