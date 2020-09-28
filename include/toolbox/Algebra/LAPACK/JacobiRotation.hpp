#pragma once

#include <toolbox/Algebra/VectorMatrix.hpp>


namespace TB
{
    class JacobiRotation
    {
    public:
        double c, s;

        explicit JacobiRotation() noexcept;
        explicit JacobiRotation(const double& c, const double& s) noexcept;

        template<class MT>
        explicit JacobiRotation(const size_t& p, const size_t& q, const MT& mat);

        template<class MT>
        void rotateMatrixFromLeft(const size_t& p, const size_t& q, MT& mat) const;

        template<class MT>
        void rotateMatrixFromRight(const size_t& p, const size_t& q, MT& mat) const;

        JacobiRotation transposed() const;
        JacobiRotation mult(const JacobiRotation& rhs);
    };

    // Inline Definitions

    inline JacobiRotation::JacobiRotation() noexcept
        : c(0), s(0) { }

    inline JacobiRotation::JacobiRotation(const double& c, const double& s) noexcept
        : c(c), s(s) { }

    template<class MT>
    inline JacobiRotation::JacobiRotation(const size_t& p, const size_t& q, const MT& mat)
    {
        const double x    = mat(p, p), y = mat(p, q), z = mat(q, q);
        const double deno = 2. * std::abs(y);

        if (deno < std::numeric_limits<double>::min())
        {
            c = 1.;
            s = 0.;
        }
        else
        {
            const double tau    = (x - z) / deno;
            const double w      = std::sqrt(tau * tau + 1.0);
            const double t      = 1. / (tau > 0. ? tau + w : tau - w);
            const double sign_t = t > 0. ? 1. : -1.;
            const double n      = 1. / std::sqrt(t * t + 1.);
            s = -sign_t * (y / std::abs(y)) * std::abs(t) * n;
            c = n;
        }
    }

    template<class MT>
    inline void JacobiRotation::rotateMatrixFromLeft(const size_t& p, const size_t& q, MT& mat) const
    {
        for (size_t ci = 0, size = mat.colCount(); ci < size; ++ci)
        {
            const double temp = c * mat(q, ci) - s * mat(p, ci);
            mat(p, ci)        = s * mat(q, ci) + c * mat(p, ci);
            mat(q, ci)        = temp;
        }
    }

    template<class MT>
    inline void JacobiRotation::rotateMatrixFromRight(const size_t& p, const size_t& q, MT& mat) const
    {
        for (size_t ri = 0, size = mat.rowCount(); ri < size; ++ri)
        {
            const double temp = s * mat(ri, p) + c * mat(ri, q);
            mat(ri, p)        = c * mat(ri, p) - s * mat(ri, q);
            mat(ri, q)        = temp;
        }
    }

    inline JacobiRotation JacobiRotation::transposed() const
    {
        return JacobiRotation(c, -s);
    }

    inline JacobiRotation JacobiRotation::mult(const JacobiRotation& rhs)
    {
        return JacobiRotation(c * rhs.c - s * rhs.s, s * rhs.c + c * rhs.s);
    }
}
