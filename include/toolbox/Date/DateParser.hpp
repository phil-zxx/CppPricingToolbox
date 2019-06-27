#pragma once

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
        constexpr static int svToInt(const std::string_view& sv);
    };

    // Inline Definitions

    inline constexpr void DateParser::fromStrToYearMonthDay(const std::string_view& str, int& year, int& month, int& day)
    {
        size_t i = findEither(str, ' ', 'T');
        if (i == std::string::npos)
            i = str.size();

        DateParser::fromDateStrToYearMonthDay(str.substr(0, i), year, month, day);
    }
    
    inline constexpr void DateParser::fromStrToYearMonthDayHourMinSec(const std::string_view& str, int& year, int& month, int& day, int& hour, int& min, int& sec)
    {
        size_t i = findEither(str, ' ', 'T');
        if (i == std::string::npos)
            i = str.size();

        DateParser::fromDateStrToYearMonthDay(str.substr(0, i), year, month, day);
    }

    inline constexpr void DateParser::fromDateStrToYearMonthDay(const std::string_view& dateStr, int& year, int& month, int& day)
    {
        if (dateStr.size() == 8)
        {
            year  = svToInt(dateStr.substr(0, 4));
            month = svToInt(dateStr.substr(4, 2));
            day   = svToInt(dateStr.substr(6, 2));
        }
        else if (dateStr.size() == 10)
        {
            year  = svToInt(dateStr.substr(0, 4));
            month = svToInt(dateStr.substr(5, 2));
            day   = svToInt(dateStr.substr(8, 2));
        }
        else
        {
            throw("Invalid input string for date; format needs to be 'yyyy-mm-dd' or 'yyyymmdd'");
        }
    }

    inline constexpr void DateParser::fromTimeStrToHourMinSec(const std::string_view& timeStr, int& hour, int& min, int& sec)
    {

    }

    inline constexpr size_t DateParser::findEither(const std::string_view& str, const char first, const char second)
    {
        if (const size_t i = str.find(first); i != std::string::npos)
            return i;
        else
            return str.find(second);
    }

    inline constexpr int DateParser::svToInt(const std::string_view& sv)
    {
        const char* c = sv.data();      // c for current
        const char* e = c + sv.size();  // e for end
        
        int sign = 1;
        if (*c == '+' || *c == '-')
        {
            sign = 44 - *c;  // Gives +1 (for '+' = 43) or -1 (for '-' = 45)
            ++c;
        }

        int num = 0;
        while (c < e)
        {
            if ('0' <= *c && *c <= '9')
            {
                num *= 10;
                num += *c - '0';
            }
            else
                break;
            ++c;
        }

        return sign * num;
    }
}
