#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>
#include <toolbox/Algebra/BaseTypes/Assert.hpp>


namespace Toolbox
{
    template<class VT1, class VT2, bool TF, class OP>
    class ExprVecVecMap : public Vector<ExprVecVecMap<VT1, VT2, TF, OP>, TF>
    {
    public:
        using ElementType = typename VT1::ElementType;

        constexpr ExprVecVecMap(const Vector<VT1, TF>& lhsVector, const Vector<VT2, TF>& rhsVector, OP operation) noexcept;
        constexpr auto operator[](size_t idx) const;

        constexpr size_t size() const noexcept;

    private:
        const VT1& m_lhsVector;
        const VT2& m_rhsVector;
        const OP   m_operation;
    };

    // Inline Definitions

    template<class VT1, class VT2, bool TF, class OP>
    inline constexpr ExprVecVecMap<VT1, VT2, TF, OP>::ExprVecVecMap(const Vector<VT1, TF>& lhsVector, const Vector<VT2, TF>& rhsVector, OP operation) noexcept
        : m_lhsVector(~lhsVector), m_rhsVector(~rhsVector), m_operation(operation) { }

    template<class VT1, class VT2, bool TF, class OP>
    inline constexpr auto ExprVecVecMap<VT1, VT2, TF, OP>::operator[](size_t idx) const
    {
        TB_ASSERT(idx < size(), "Invalid vector access index");

        return m_operation(m_lhsVector[idx], m_rhsVector[idx]);
    }

    template<class VT1, class VT2, bool TF, class OP>
    inline constexpr size_t ExprVecVecMap<VT1, VT2, TF, OP>::size() const noexcept
    {
        return m_lhsVector.size();
    }
}
