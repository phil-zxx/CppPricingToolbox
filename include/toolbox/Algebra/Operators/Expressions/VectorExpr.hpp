#pragma once

#include <toolbox/Algebra/Typetraits/ApplyOperator.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>
#include <toolbox/Algebra/Typetraits/OpResultType.hpp>


namespace Toolbox
{
    template <class OP, class LHS, class RHS, bool TF>
    class VectorExpr : public Vector<VectorExpr<OP, LHS, RHS, TF>, TF>, Expression
    {
    public:
        using OT_LHS = std::conditional_t<is_expression_v<LHS>, const LHS, const LHS&>;
        using OT_RHS = std::conditional_t<is_expression_v<RHS>, const RHS, const RHS&>;
        using ET_LHS = ElementType_t<LHS>;
        using ET_RHS = ElementType_t<RHS>;
        using ElementType = typename OpResultType_t<OP, ET_LHS, ET_RHS>;

        constexpr static bool is_unary_expression_v = std::is_same_v<void*, RHS>;

        constexpr VectorExpr(const LHS& arg)
            : m_lhs(arg), m_rhs{}
        {
            static_assert(is_unary_expression_v, "Operator is not unary, need to provide two inputs");
        }

        constexpr VectorExpr(const LHS& lhs, const RHS& rhs)
            : m_lhs(lhs), m_rhs(rhs) 
        {
            if constexpr (is_vector_v<LHS> && is_vector_v<RHS>)
            {
                if (lhs.size() != rhs.size())
                    throw("Vector sizes do not match");
            }

            static_assert(!is_unary_expression_v, "Operator is not binary, need to provide one input only");
        }

        constexpr auto operator[](size_t i) const
        {
            if constexpr(VectorExpr::is_unary_expression_v)
                return apply_unary<OP, LHS>(m_lhs, i);
            else
            {
                return apply_binary<OP, LHS, RHS>(m_lhs, m_rhs, i);
            }
        }

        constexpr size_t size() const
        {
            if constexpr (is_vector_v<LHS>)
                return m_lhs.size();
            else if constexpr (is_vector_v<RHS>)
                return m_rhs.size();
            else
                static_assert(false, "At least one input must be a vector");
        }

    private:
        OT_LHS m_lhs;
        OT_RHS m_rhs;
    };

    template <class OP, class VT, bool TF>
    using VectorExprUnary = VectorExpr<OP, VT, void*, TF>;

    template <class OP, class VT1, class VT2, bool TF>
    using VectorExprBinary = VectorExpr<OP, VT1, VT2, TF>;
}
