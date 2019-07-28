#pragma once

#include <toolbox/Core/Misc.hpp>
#include <string_view>


namespace Toolbox
{
    class Tenor
    {
    public:
        constexpr Tenor(int count, char unit);
        constexpr Tenor(const std::string_view& tenorStr);

        constexpr int count() const;
        constexpr char unit() const;

        constexpr Tenor& reduce();

    private:
        int m_count;
        char m_unit;
    };

    // Inline Definitions

    inline constexpr Tenor::Tenor(int count, char unit)
        : m_count(count), m_unit(unit) 
    {
        if (m_unit != 'B' && m_unit != 'D' && m_unit != 'W' && m_unit != 'M' && m_unit != 'Y')
            throw("Need unit to be B, D, W, M or Y");
    }

    inline constexpr Tenor::Tenor(const std::string_view& tenorStr)
        : Tenor(tenorStr.size() == 0 ? 0   : Misc::svToInt(tenorStr.substr(0, tenorStr.size() - 1)), 
                tenorStr.size() == 0 ? 'D' : tenorStr.back())
    {
        if (tenorStr.size() == 1)
            throw("Tenor string cannot be of size 1; need it to be either empty or larger than 1");
    }
    
    inline constexpr Tenor& Tenor::reduce()
    {
        if (m_count != 0)
        {
            if (m_unit == 'D' && m_count % 7 == 0)
            {
                m_count /= 7;
                m_unit = 'W';
            }
            else if (m_unit == 'M' && m_count % 12 == 0)
            {
                m_count /= 12;
                m_unit = 'Y';
            }
        }
        
        return *this;
    }

    inline constexpr int Tenor::count() const
    {
        return m_count;
    }

    inline constexpr char Tenor::unit() const
    {
        return m_unit;
    }
}
