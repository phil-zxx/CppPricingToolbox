#pragma once

#include <toolbox/Core/Misc.hpp>
#include <string_view>
#include <vector>


namespace Toolbox
{
    enum class TenorUnit { __UNDEFINED__, D, B, W, M, Y };

    struct Enum
    {
        template<class T>
        static constexpr T fromChar(char c)
        {
            switch (c)
            {
            case 'D': return TenorUnit::D;
            case 'B': return TenorUnit::B;
            case 'W': return TenorUnit::W;
            case 'M': return TenorUnit::M;
            case 'Y': return TenorUnit::Y;
            default:
                throw("Unknown char input cannot be converted to TenorUnit");
            }
        }
    };

    class TenorElement
    {
    public:
        constexpr TenorElement(int count, char unit);
        constexpr TenorElement(int count, TenorUnit unit);
        constexpr TenorElement(const std::string_view& tenorStr);

        constexpr int       count() const { return m_count; }
        constexpr TenorUnit unit()  const { return m_unit; }

        constexpr TenorElement& reduce();

    private:
        int       m_count;
        TenorUnit m_unit;
    };

    class Tenor : public std::vector<TenorElement>
    {
    public:
        Tenor(int count, TenorUnit unit)
            : std::vector<TenorElement>(1, TenorElement(count, unit)) { }

        Tenor(const std::string_view& tenorStr)
            : std::vector<TenorElement>()
        {
            size_t i0 = 0, i1;
            const size_t size = tenorStr.size();

            for (i1 = 1; i1 < size; ++i1)
            {
                if (tenorStr[i1] == '+' || tenorStr[i1] == '-')
                {
                    this->emplace_back(tenorStr.substr(i0, i1 - i0));
                    i0 = i1;
                }
            }

            if (i0 < size - 2)
            {
                this->emplace_back(tenorStr.substr(i0, i1 - i0));
            }
        }
    };

    // Inline Definitions

    inline constexpr TenorElement::TenorElement(int count, char unit)
        : m_count(count), m_unit(Enum::fromChar<TenorUnit>(unit))
    {
        if (m_unit == TenorUnit::__UNDEFINED__)
            throw("Need unit to be B, D, W, M or Y");
    }

    inline constexpr TenorElement::TenorElement(int count, TenorUnit unit)
        : m_count(count), m_unit(unit)
    {
        if (m_unit == TenorUnit::__UNDEFINED__)
            throw("Need unit to be B, D, W, M or Y");
    }

    inline constexpr TenorElement::TenorElement(const std::string_view& tenorStr)
        : m_count(0), m_unit(TenorUnit::__UNDEFINED__)
    {
        if (tenorStr.size() == 1)
            throw("Tenor string cannot be of size 1; need it to be either empty or larger than 1");

        m_count = Misc::svToInt(tenorStr.substr(0, tenorStr.size() - 1));
        m_unit  = Enum::fromChar<TenorUnit>(tenorStr.back());
    }
    
    inline constexpr TenorElement& TenorElement::reduce()
    {
        if (m_count != 0)
        {
            if (m_unit == TenorUnit::D && m_count % 7 == 0)
            {
                m_count /= 7;
                m_unit = TenorUnit::W;
            }
            else if (m_unit == TenorUnit::M && m_count % 12 == 0)
            {
                m_count /= 12;
                m_unit = TenorUnit::Y;
            }
        }
        
        return *this;
    }
}
