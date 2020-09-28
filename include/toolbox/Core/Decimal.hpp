#pragma once

#include <toolbox/Core/Misc.hpp>

#include <cstdint>
#include <sstream>
#include <sstream>


namespace TB
{
    template<size_t n> constexpr int64_t pow10    = 10 * pow10<n - 1>;
    template<>         constexpr int64_t pow10<0> =  1;

    template<size_t DP>  // DP = Decimal Places
    class Decimal
    {
        static constexpr int64_t pow10DP = pow10<DP>;

        constexpr int64_t round(double x)
        {
            return x >= 0. ? int64_t(x + 0.5) : int64_t(x - 0.5);
        }

    public:
        constexpr Decimal() noexcept
            : m_value(0) { }

        constexpr explicit Decimal(int64_t value) noexcept
            : m_value(value * pow10DP) { }

        constexpr Decimal(double value) noexcept
            : m_value(static_cast<int64_t>(round(value * pow10DP))) { }

        constexpr Decimal operator+(const Decimal& rhs) const
        {
            return Decimal::fromValue(this->m_value + rhs.m_value);
        }

        constexpr Decimal operator-(const Decimal& rhs) const
        {
            return Decimal::fromValue(this->m_value - rhs.m_value);
        }

        constexpr Decimal operator*(const Decimal& rhs) const
        {
            return Decimal(this->toDouble() * rhs.toDouble());
        }

        constexpr Decimal operator/(const Decimal& rhs) const
        {
            return Decimal(this->m_value / static_cast<double>(rhs.m_value));
        }

        constexpr bool operator==(const Decimal& rhs) const
        {
            return this->m_value == rhs.m_value;
        }
        constexpr bool operator!=(const Decimal& rhs) const
        {
            return !(*this == rhs);
        }

        constexpr bool operator<(const Decimal& rhs) const
        {
            return this->m_value < rhs.m_value;
        }

        constexpr bool operator<=(const Decimal& rhs) const
        {
            return this->m_value <= rhs.m_value;
        }

        constexpr bool operator>(const Decimal& rhs) const
        {
            return this->m_value > rhs.m_value;
        }

        constexpr bool operator>=(const Decimal& rhs) const
        {
            return this->m_value >= rhs.m_value;
        }

        friend std::ostream& operator<<(std::ostream& os, const Decimal& rhs)
        {
            const int64_t intValue = rhs.m_value / pow10DP;
            os << intValue;

            if constexpr (DP > 0)
            {
                const int64_t resValue = std::abs(rhs.m_value - intValue * pow10DP);
                os << "." << resValue;
            }

            return os;
        }

        std::string toString() const
        {
            std::ostringstream os;
            os << *this;

            return os.str();
        }

        constexpr double toDouble() const
        {
            return this->m_value / static_cast<double>(pow10DP);
        }

    private:
        static constexpr Decimal fromValue(int64_t value)
        {
            Decimal d;
            d.m_value = value;
            return d;
        }

        int64_t m_value;
    };
}
