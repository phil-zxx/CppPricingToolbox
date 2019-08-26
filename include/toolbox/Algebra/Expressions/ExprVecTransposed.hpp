#pragma once

#include <toolbox/Algebra/Core/Vector.hpp>
#include <toolbox/Algebra/Core/Assert.hpp>


namespace Toolbox
{
    template<class VT, bool TF>
    class ExprVecTransposed : public Vector<ExprVecTransposed<VT, TF>, TF>
    {
    public:
        using ElementType = typename VT::ElementType;

        constexpr explicit ExprVecTransposed(const Vector<VT, !TF>& vector) noexcept;
        constexpr auto operator[](size_t idx) const;

        constexpr size_t size() const noexcept;

    private:
        const VT& m_vector;
    };

    // Inline Definitions

    template<class VT, bool TF>
    inline constexpr ExprVecTransposed<VT, TF>::ExprVecTransposed(const Vector<VT, !TF>& vector) noexcept
        : m_vector(~vector) { }

    template<class VT, bool TF>
    inline constexpr auto ExprVecTransposed<VT, TF>::operator[](size_t idx) const
    {
        TB_ASSERT(idx < size(), "Invalid vector access index");

        return m_vector[idx];
    }

    template<class VT, bool TF>
    inline constexpr size_t ExprVecTransposed<VT, TF>::size() const noexcept
    {
        return m_vector.size();
    }
}
