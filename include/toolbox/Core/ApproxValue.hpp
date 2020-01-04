#pragma once

#include <cmath>


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

    private:
        const m_value, m_eps;
    };
}
