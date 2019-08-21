#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>
#include <toolbox/Algebra/BaseTypes/Assert.hpp>


namespace Toolbox
{
    template<class VT, bool TF, class OP>
    class ExprVecMap : public Vector<ExprVecMap<VT, TF, OP>, TF>
    {
    public:
        using ElementType = typename VT::ElementType;

        constexpr explicit ExprVecMap(const Vector<VT, TF>& vector, OP operation) noexcept;
        constexpr auto operator[](size_t idx) const;

        constexpr size_t size() const noexcept;

    private:
        const VT& m_vector;
        const OP  m_operation;
    };

    // Inline Definitions

    template<class VT, bool TF, class OP>
    inline constexpr ExprVecMap<VT, TF, OP>::ExprVecMap(const Vector<VT, TF>& vector, OP operation) noexcept
        : m_vector(~vector), m_operation(operation) { }

    template<class VT, bool TF, class OP>
    inline constexpr auto ExprVecMap<VT, TF, OP>::operator[](size_t idx) const
    {
        TB_ASSERT(idx < size(), "Invalid vector access index");

        return m_operation(m_vector[idx]);
    }

    template<class VT, bool TF, class OP>
    inline constexpr size_t ExprVecMap<VT, TF, OP>::size() const noexcept
    {
        return m_vector.size();
    }
}
