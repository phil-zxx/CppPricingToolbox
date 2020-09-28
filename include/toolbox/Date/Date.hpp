#pragma once

#include <toolbox/Date/DateParser.hpp>

#include <string_view>
#include <sstream>
#include <iomanip>


namespace TB
{
    class Date
    {
    public:
        /* ===== Helper Struct ===== */

        struct YearMonthDay
        {
            int year, month, day;
            constexpr bool operator==(const YearMonthDay& ymd) const;
        };


        /* ===== Constructors ===== */

        constexpr Date() noexcept;
        constexpr Date(int totalDays) noexcept;
        constexpr Date(int year, int month, int day) noexcept;
        constexpr explicit Date(const std::string_view& str);


        /* ===== Access Functions ===== */

        constexpr int year() const;
        constexpr int month() const;
        constexpr int day() const;
        constexpr int totalDays() const;
        constexpr const YearMonthDay& ymd() const;


        /* ===== Operator Functions ===== */

        constexpr bool operator==(const Date& rhs) const;
        constexpr bool operator!=(const Date& rhs) const;
        constexpr bool operator>=(const Date& rhs) const;
        constexpr bool operator<=(const Date& rhs) const;
        constexpr bool operator> (const Date& rhs) const;
        constexpr bool operator< (const Date& rhs) const;

        constexpr Date& operator+=(int x);
        constexpr Date& operator-=(int x);

        constexpr Date& operator++();     // Pre Increment
        constexpr Date& operator--();     // Pre Decrement
        constexpr Date  operator++(int);  // Post Increment
        constexpr Date  operator--(int);  // Post Decrement


        /* ===== Misc Functions ===== */

        // Returns true of total number of days is 0, false otherwise
        constexpr bool isNull() const;

        // Returns the day of the week, where 0=Monday, ..., 5=Satursday, 6=Sunday
        constexpr int dayOfWeek() const;

        // Returns true of the input year is a leap year, false otherwise
        static constexpr bool isLeapYear(unsigned int year) noexcept;

        // Returns the total number of days (28-31) for a given month
        static constexpr int daysInMonth(unsigned int year, unsigned int month) noexcept;

        constexpr int toInt() const;
        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Date& rhs);

    protected:
        int          m_totalDays;  // Total number of days since epoch (which is 1899-12-30)
        YearMonthDay m_ymd;        // Explicit year-month-day representation of the date

        static constexpr YearMonthDay fromTotalDaysToYearMonthDay(int totalDays) noexcept;
        static constexpr int          fromYearMonthDayToTotalDays(int year, int month, int day) noexcept;
    };

    // Inline Definitions

    /* ===== Helper Struct ===== */

    inline constexpr bool Date::YearMonthDay::operator==(const Date::YearMonthDay& ymd) const
    {
        return year == ymd.year && month == ymd.month && day == ymd.day;
    }


    /* ===== Constructors ===== */

    inline constexpr Date::Date() noexcept
        : m_totalDays(0), m_ymd{1899, 12, 30} { }

    inline constexpr Date::Date(int totalDays) noexcept
        : m_totalDays(totalDays), m_ymd(Date::fromTotalDaysToYearMonthDay(totalDays)) { }

    inline constexpr Date::Date(int year, int month, int day) noexcept
        : m_totalDays(Date::fromYearMonthDayToTotalDays(year, month, day)), m_ymd{year, month, day} { }

    inline constexpr Date::Date(const std::string_view& str)
        : m_totalDays(0), m_ymd{1899, 12, 30}
    {
        DateParser::fromStrToYearMonthDay(str, m_ymd.year, m_ymd.month, m_ymd.day);
        m_totalDays = Date::fromYearMonthDayToTotalDays(m_ymd.year, m_ymd.month, m_ymd.day);
    }


    /* ===== Access Functions ===== */

    inline constexpr int Date::year() const
    {
        return m_ymd.year;
    }

    inline constexpr int Date::month() const
    {
        return m_ymd.month;
    }

    inline constexpr int Date::day() const
    {
        return m_ymd.day;
    }

    inline constexpr int Date::totalDays() const
    {
        return m_totalDays;
    }

    inline constexpr const Date::YearMonthDay& Date::ymd() const
    {
        return m_ymd;
    }

    /* ===== Operator Functions ===== */

    inline constexpr bool Date::operator==(const Date& rhs) const { return this->m_totalDays == rhs.totalDays(); }
    inline constexpr bool Date::operator!=(const Date& rhs) const { return this->m_totalDays != rhs.totalDays(); }
    inline constexpr bool Date::operator>=(const Date& rhs) const { return this->m_totalDays >= rhs.totalDays(); }
    inline constexpr bool Date::operator<=(const Date& rhs) const { return this->m_totalDays <= rhs.totalDays(); }
    inline constexpr bool Date::operator> (const Date& rhs) const { return this->m_totalDays >  rhs.totalDays(); }
    inline constexpr bool Date::operator< (const Date& rhs) const { return this->m_totalDays <  rhs.totalDays(); }

    inline constexpr Date& Date::operator+=(int x)
    {
        return *this = Date(totalDays() + x);
    }

    inline constexpr Date& Date::operator-=(int x)
    {
        return *this = Date(totalDays() - x);
    }

    inline constexpr Date& Date::operator++()
    {
        return *this += 1;
    }

    inline constexpr Date& Date::operator--()
    {
        return *this -= 1;
    }

    inline constexpr Date Date::operator++(int)
    {
        Date old(*this);
        ++(*this);
        return old;
    }

    inline constexpr Date Date::operator--(int)
    {
        Date old(*this);
        --(*this);
        return old;
    }

    /* ===== Misc Functions ===== */

    inline constexpr bool Date::isNull() const
    {
        return m_totalDays == 0;
    }

    inline constexpr int Date::dayOfWeek() const
    {
        return (m_totalDays - 2) % 7;
    }

    inline constexpr bool Date::isLeapYear(unsigned int year) noexcept
    {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }

    inline constexpr int Date::daysInMonth(unsigned int year, unsigned int month) noexcept
    {
        constexpr unsigned char a[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return month != 2 || !isLeapYear(year) ? a[month - 1] : 29;
    }

    inline constexpr int Date::toInt() const
    {
        return m_totalDays;
    }

    inline std::string Date::toString() const
    {
        std::ostringstream os;
        os << *this;
        return os.str();
    }

    inline std::ostream& operator<<(std::ostream& os, const Date& rhs)
    {
        return os << std::right << std::setfill('0') << rhs.m_ymd.year << '-' << std::setw(2) << rhs.m_ymd.month << '-' << std::setw(2) << rhs.m_ymd.day;
    }

    /* ===== Private Functions ===== */

    inline constexpr Date::YearMonthDay Date::fromTotalDaysToYearMonthDay(int totalDays) noexcept
    {
        YearMonthDay ymd{0, 0, 0};

        // Modified Julian to DMY calculation with an addition of 2415019
        int l     = totalDays + 68'569 + 2'415'019;
        int n     = int((4 * l) / 146'097);
        l         = l - int((146'097 * n + 3) / 4);
        int i     = int((4000 * (l + 1)) / 1'461'001);
        l         = l - int((1461 * i) / 4) + 31;
        int j     = int((80 * l) / 2447);
        ymd.day   = l - int((2447 * j) / 80);
        l         = int(j / 11);
        ymd.month = j + 2 - (12 * l);
        ymd.year  = 100 * (n - 49) + i + l;

        return ymd;
    }

    // Returns year/month/day triple in civil calendar
    // Preconditions:  z is number of days since 1970-01-01 and is in the range:
    //                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
    constexpr Date::YearMonthDay civil_from_days(int totalDays) noexcept
    {
        Date::YearMonthDay ymd{0, 0, 0};

        totalDays += 719468 - 25569;
        const int era = (totalDays >= 0 ? totalDays : totalDays - 146096) / 146097;
        const int doe = totalDays - era * 146097;                                    // [0, 146096]
        const int yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;       // [0, 399]
        const int y   = yoe + era * 400;
        const int doy = doe - (365 * yoe + yoe / 4 - yoe / 100);                     // [0, 365]
        const int mp  = (5 * doy + 2) / 153;                                         // [0, 11]
        ymd.day   = doy - (153 * mp + 2) / 5 + 1;                                    // [1, 31]
        ymd.month = mp + (mp < 10 ? 3 : -9);                                         // [1, 12]
        ymd.year  = y + (ymd.month <= 2);
        return ymd;
    }

    inline constexpr int Date::fromYearMonthDayToTotalDays(int year, int month, int day) noexcept
    {
        // DMY to Modified Julian calculated with an extra subtraction of 2415019

        return int((1461 * (year + 4800 + int((month - 14) / 12))) / 4) + int((367 * (month - 2 - 12 * ((month - 14) / 12))) / 12) -
            int((3 * (int((year + 4900 + int((month - 14) / 12)) / 100))) / 4) + day - 2415019 - 32075;
    }

    // Returns number of days since civil 1970-01-01. Negative values indicate
    //    days prior to 1970-01-01.
    // Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
    //                 m is in [1, 12]
    //                 d is in [1, last_day_of_month(y, m)]
    //                 y is "approximately" in
    //                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
    //                 Exact range of validity is:
    //                 [civil_from_days(numeric_limits<Int>::min()),
    //                  civil_from_days(numeric_limits<Int>::max()-719468)]
    constexpr int days_from_civil(int year, int month, int day) noexcept
    {
        year -= month <= 2;
        const int era = (year >= 0 ? year : year - 399) / 400;
        const int yoe = year - era * 400;                                          // [0, 399]
        const int doy = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;  // [0, 365]
        const int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;                     // [0, 146096]
        return era * 146097 + doe - (719468 - 25569);
    }
}
