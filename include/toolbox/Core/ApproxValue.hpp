#pragma once

#include <cmath>
#include <ostream>
#include <iomanip>


namespace Toolbox
{
    struct ApproxValue
    {
        constexpr ApproxValue(double value, double eps = 1.e-15)
            : m_value(value), m_eps(eps) { }

        bool operator==(const double& other) const
        {
            return std::abs(this->m_value - other) < m_eps;
        }

        bool operator!=(const double& other) const
        {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const ApproxValue& rhs)
        {
            return os << std::setprecision(static_cast<int>(2 + std::log10(1. / rhs.m_eps))) << rhs.m_value;
        }

    private:
        const double m_value, m_eps;
    };
}
