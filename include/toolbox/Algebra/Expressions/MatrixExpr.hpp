#pragma once

#include <toolbox/Algebra/Typetraits/ApplyOperator.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>
#include <toolbox/Algebra/Typetraits/OpResultType.hpp>


namespace Toolbox
{
    template <class OP, class LHS, class RHS>
    class MatrixExpr : public Matrix<MatrixExpr<OP, LHS, RHS>>, Expression
    {
    public:
        constexpr static bool is_unary_expression_v = std::is_same_v<void*, RHS>;

        using OT_LHS      = std::conditional_t<is_expression_or_scalar_v<LHS>, const LHS, const LHS&>;
        using OT_RHS      = std::conditional_t<is_expression_or_scalar_v<RHS> || is_unary_expression_v, const RHS, const RHS&>;
        using ET_LHS      = ElementType_t<LHS>;
        using ET_RHS      = ElementType_t<RHS>;
        using ElementType = OpResultType_t<OP, ET_LHS, ET_RHS>;

        constexpr explicit MatrixExpr(const LHS& arg)
            : m_lhs(arg), m_rhs(nullptr)
        {
            static_assert(is_unary_expression_v, "Operator is not unary, need to provide two inputs");
        }

        constexpr explicit MatrixExpr(const LHS& lhs, const RHS& rhs)
            : m_lhs(lhs), m_rhs(rhs)
        {
            if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            {
                if (lhs.shape() != rhs.shape())
                    throw("Matrix shapes do not match");
            }

            static_assert(!is_unary_expression_v, "Operator is not binary, need to provide one input only");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            if constexpr(is_unary_expression_v)
                return apply_unary<OP, LHS>(m_lhs, i);
            else
                return apply_binary<OP, LHS, RHS>(m_lhs, m_rhs, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (is_unary_expression_v)
                return apply_unary<OP, LHS>(m_lhs, rowIdx, colIdx);
            else
                return apply_binary<OP, LHS, RHS>(m_lhs, m_rhs, rowIdx, colIdx);
        }

        constexpr size_t size() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.size();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.size();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr const MatrixShape& shape() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.shape();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.shape();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr size_t rowCount() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.rowCount();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.rowCount();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr size_t colCount() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.colCount();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.colCount();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

    private:
        OT_LHS m_lhs;
        OT_RHS m_rhs;
    };

    template <class OP, class MT>
    using MatrixExprUnary = MatrixExpr<OP, MT, void*>;

    template <class OP, class MT1, class MT2>
    using MatrixExprBinary = MatrixExpr<OP, MT1, MT2>;
}
