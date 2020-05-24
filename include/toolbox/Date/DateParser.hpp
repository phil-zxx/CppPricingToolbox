#pragma once

#include <toolbox/Core/Misc.hpp>

#include <string_view>


namespace Toolbox
{
    class DateParser
    {
    public:
        constexpr static void fromStrToYearMonthDay(const std::string_view& str, int& year, int& month, int& day);
        constexpr static void fromStrToYearMonthDayHourMinSec(const std::string_view& str, int& year, int& month, int& day, int& hour, int& min, int& sec);

    private:
        constexpr static void fromDateStrToYearMonthDay(const std::string_view& dateStr, int& year, int& month, int& day);
        constexpr static void fromTimeStrToHourMinSec(const std::string_view& timeStr, int& hour, int& min, int& sec);

        constexpr static size_t findEither(const std::string_view& str, const char first, const char second);
    };

    // Inline Definitions

    inline constexpr void DateParser::fromStrToYearMonthDay(const std::string_view& str, int& year, int& month, int& day)
    {
        size_t i = findEither(str, ' ', 'T');
        if (i == std::string_view::npos)
            i = str.size();

        DateParser::fromDateStrToYearMonthDay(str.substr(0, i), year, month, day);
    }

    inline constexpr void DateParser::fromStrToYearMonthDayHourMinSec(const std::string_view& str, int& year, int& month, int& day, int& hour, int& min, int& sec)
    {
        // Find index which divides date & time part, should it exist
        size_t i = findEither(str, ' ', 'T');
        if (i == std::string_view::npos)
            i = str.size();

        // Parse date part of the input string
        DateParser::fromDateStrToYearMonthDay(str.substr(0, i), year, month, day);

        // Parse time part of the input string, if one was provided
        if(i != str.size())
            DateParser::fromTimeStrToHourMinSec(str.substr(i + 1), hour, min, sec);
    }

    inline constexpr void DateParser::fromDateStrToYearMonthDay(const std::string_view& dateStr, int& year, int& month, int& day)
    {
        if (dateStr.size() == 8)
        {
            year  = Misc::svToInt(dateStr.substr(0, 4));
            month = Misc::svToInt(dateStr.substr(4, 2));
            day   = Misc::svToInt(dateStr.substr(6, 2));
        }
        else if (dateStr.size() == 10)
        {
            year  = Misc::svToInt(dateStr.substr(0, 4));
            month = Misc::svToInt(dateStr.substr(5, 2));
            day   = Misc::svToInt(dateStr.substr(8, 2));
        }
        else
        {
            throw("Invalid input string for date; format needs to be 'yyyy-mm-dd' or 'yyyymmdd'");
        }
    }

    inline constexpr void DateParser::fromTimeStrToHourMinSec(const std::string_view& timeStr, int& hour, int& min, int& sec)
    {
        if (timeStr.size() == 5)
        {
            hour = Misc::svToInt(timeStr.substr(0, 2));
            min  = Misc::svToInt(timeStr.substr(3, 2));
            sec  = 0;
        }
        else if (timeStr.size() == 8)
        {
            hour = Misc::svToInt(timeStr.substr(0, 2));
            min  = Misc::svToInt(timeStr.substr(3, 2));
            sec  = Misc::svToInt(timeStr.substr(6, 2));
        }
        else
        {
            throw("Invalid input string for date; format needs to be 'hh:mm' or 'hh:mm:ss'");
        }
    }

    inline constexpr size_t DateParser::findEither(const std::string_view& str, const char first, const char second)
    {
        if (const size_t i = str.find(first); i != std::string_view::npos)
            return i;
        else
            return str.find(second);
    }
}
