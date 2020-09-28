#pragma once

#include <toolbox/Date/Date.hpp>

#include <cstdint>


namespace TB
{
    class DateTime : public Date
    {
    public:
        /* ===== Constructors =========================================================================================== */

        using Date::Date;

        constexpr DateTime(int totalDays, int64_t totalNanos) noexcept;
        constexpr DateTime(int year, int month, int day, int hour, int minute, int second) noexcept;
        constexpr explicit DateTime(const std::string_view& str);


        /* ===== Access Functions =========================================================================================== */

        constexpr int hour() const;
        constexpr int minute() const;
        constexpr int second() const;
        constexpr int64_t nano() const;
        constexpr int64_t totalNanos() const;
        constexpr int64_t totalSeconds() const;


        /* ===== Operator Functions =========================================================================================== */

        constexpr bool operator==(const DateTime& rhs) const;
        constexpr bool operator!=(const DateTime& rhs) const;
        constexpr bool operator>=(const DateTime& rhs) const;
        constexpr bool operator<=(const DateTime& rhs) const;
        constexpr bool operator> (const DateTime& rhs) const;
        constexpr bool operator< (const DateTime& rhs) const;

        constexpr DateTime& operator=(const DateTime& rhs);


        /* ===== Misc Functions =========================================================================================== */

        // Returns true of total number of days is 0, false otherwise
        constexpr bool isNull() const;

        // Returns true of total number of days is 0, false otherwise
        constexpr bool hasTime() const;

        // Returns true of total number of days is 0, false otherwise
        constexpr Date timeless() const;

        constexpr double toDouble() const;
        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& os, const DateTime& rhs);

    private:
        int64_t m_totalNanos = -1;  // Total number of seconds since midnight

        constexpr static int64_t nanosPerDay = 24 * 3600 * 1'000'000'000LL;

        static constexpr int64_t fromHhMmSsNnToTotalNanos(int hour, int minute, int second, int64_t nano) noexcept;
    };

    // Inline Definitions

    /* ===== Constructors =========================================================================================== */

    inline constexpr DateTime::DateTime(int totalDays, int64_t totalNanos) noexcept
        : Date(totalDays), m_totalNanos(totalNanos) { }

    inline constexpr DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) noexcept
        : Date(year, month, day), m_totalNanos(fromHhMmSsNnToTotalNanos(hour, minute, second, 0)) { }

    inline constexpr DateTime::DateTime(const std::string_view& str)
        : Date(), m_totalNanos(0)
    {
        int hour = 0, minute = 0, second = 0;
        DateParser::fromStrToYearMonthDayHourMinSec(str, m_ymd.year, m_ymd.month, m_ymd.day, hour, minute, second);
        m_totalDays  = Date::fromYearMonthDayToTotalDays(m_ymd.year, m_ymd.month, m_ymd.day);
        m_totalNanos = DateTime::fromHhMmSsNnToTotalNanos(hour, minute, second, 0);
    }


    /* ===== Access Functions =========================================================================================== */

    inline constexpr int DateTime::hour() const
    {
        return hasTime() ? static_cast<int>(totalNanos() / 3'600'000'000'000LL) : 0;
    }

    inline constexpr int DateTime::minute() const
    {
        return hasTime() ? static_cast<int>((totalNanos() % 3'600'000'000'000LL) / 60'000'000'000LL) : 0;
    }

    inline constexpr int DateTime::second() const
    {
        return hasTime() ? static_cast<int>((totalNanos() % 60'000'000'000LL) / 1'000'000'000LL) : 0;
    }

    inline constexpr int64_t DateTime::nano() const
    {
        return hasTime() ? totalNanos() % 1'000'000'000LL : 0;
    }

    inline constexpr int64_t DateTime::totalNanos() const
    {
        return m_totalNanos;
    }

    inline constexpr int64_t DateTime::totalSeconds() const
    {
        return m_totalNanos / 1'000'000'000LL;
    }



    /* ===== Operator Functions =========================================================================================== */

    inline constexpr bool DateTime::operator==(const DateTime& rhs) const { return this->totalDays() == rhs.totalDays() /* fill in rest for time*/; }
    inline constexpr bool DateTime::operator!=(const DateTime& rhs) const { return this->totalDays() != rhs.totalDays(); }
    inline constexpr bool DateTime::operator>=(const DateTime& rhs) const { return this->totalDays() >= rhs.totalDays(); }
    inline constexpr bool DateTime::operator<=(const DateTime& rhs) const { return this->totalDays() <= rhs.totalDays(); }
    inline constexpr bool DateTime::operator> (const DateTime& rhs) const { return this->totalDays() > rhs.totalDays(); }
    inline constexpr bool DateTime::operator< (const DateTime& rhs) const { return this->totalDays() < rhs.totalDays(); }

    inline constexpr DateTime& DateTime::operator=(const DateTime& rhs)
    {
        this->m_totalDays  = rhs.m_totalDays;
        this->m_ymd        = rhs.m_ymd;
        this->m_totalNanos = rhs.m_totalNanos;
        return *this;
    }


    /* ===== Misc Functions =========================================================================================== */

    inline constexpr bool DateTime::isNull() const
    {
        return Date::isNull();
    }

    inline constexpr bool DateTime::hasTime() const
    {
        return m_totalNanos != -1;
    }

    inline constexpr Date DateTime::timeless() const
    {
        return Date(totalDays());
    }

    inline constexpr double DateTime::toDouble() const
    {
        return static_cast<double>(toInt()) + static_cast<double>(m_totalNanos) / nanosPerDay;
    }

    inline std::string DateTime::toString() const
    {
        std::ostringstream os;
        os << *this;
        return os.str();
    }

    inline std::ostream& operator<<(std::ostream& os, const DateTime& rhs)
    {
        os << std::right << std::setfill('0') << rhs.year() << '-' << std::setw(2) << rhs.month() << '-' << std::setw(2) << rhs.day();

        if (rhs.hasTime())
        {
            /* print time*/
        }

        return os;
    }


    /* ===== Private Functions =========================================================================================== */

    inline constexpr int64_t DateTime::fromHhMmSsNnToTotalNanos(int hour, int minute, int second, int64_t nano) noexcept
    {
        return nano + 1'000'000'000LL * (second + 60 * (minute + 60 * hour));
    }
}
