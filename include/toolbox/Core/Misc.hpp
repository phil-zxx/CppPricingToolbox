#pragma once

#include <string_view>


namespace Toolbox
{
    class Misc
    {
    public:
        constexpr static int svToInt(const std::string_view& sv);
    };

    // Inline Definitions

    inline constexpr int Misc::svToInt(const std::string_view& sv)
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
