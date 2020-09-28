#pragma once

#include <toolbox/Algebra/Typetraits/OpResultType.hpp>


namespace TB
{
    template <class OP, class LHS, class RHS>
    class MatrixExpr : public Matrix<MatrixExpr<OP, LHS, RHS>>, Expression
    {
    public:
        constexpr static bool is_unary_expression_v = std::is_same_v<void*, RHS>;

        using OT_LHS      = std::conditional_t<is_expression_or_scalar_v<LHS>, const LHS, const LHS&>;
        using OT_RHS      = std::conditional_t<is_expression_or_scalar_v<RHS> || is_unary_expression_v, const RHS, const RHS&>;
        using ElementType = OpResultType_t<OP, LHS, RHS>;

        constexpr explicit MatrixExpr(const LHS& arg)
            : m_lhs(arg), m_rhs(nullptr), m_alignment(0), m_shape(arg.shape())
        {
            static_assert(is_unary_expression_v, "Operator is not unary, need to provide two inputs");
        }

        constexpr explicit MatrixExpr(const LHS& lhs, const RHS& rhs)
            : m_lhs(lhs), m_rhs(rhs), m_alignment(0), m_shape(0, 0)
        {
            if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            {
                if (lhs.shape() == rhs.shape())
                {
                    m_alignment = 'S';
                    m_shape     = lhs.shape();
                }
                else if (lhs.rowCount() == rhs.rowCount() && lhs.colCount() == 1)
                {
                    m_alignment = 'r';
                    m_shape     = rhs.shape();
                }
                else if (lhs.rowCount() == rhs.rowCount() && rhs.colCount() == 1)
                {
                    m_alignment = 'R';
                    m_shape     = lhs.shape();
                }
                else if (lhs.colCount() == rhs.colCount() && lhs.rowCount() == 1)
                {
                    m_alignment = 'c';
                    m_shape     = rhs.shape();
                }
                else if (lhs.colCount() == rhs.colCount() && rhs.rowCount() == 1)
                {
                    m_alignment = 'C';
                    m_shape     = lhs.shape();
                }
                TB_ENSURE(m_alignment != 0, "Matrix shapes do not match (" << lhs.shape() << " and " << rhs.shape() << ")");
            }
            else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
                m_shape = lhs.shape();
            else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
                m_shape = rhs.shape();

            static_assert(!is_unary_expression_v, "Operator is not binary, need to provide one input only");
            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr decltype(auto) operator[](size_t idx) const
        {
            if constexpr (is_unary_expression_v)
                return m_op(m_lhs[idx]);
            else
            {
                if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
                    return m_op(m_lhs, m_rhs[idx]);
                else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
                    return m_op(m_lhs[idx], m_rhs);
                else if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
                {
                    switch (m_alignment)
                    {
                    case 'S': return m_op(m_lhs[idx],                m_rhs[idx]);
                    case 'r': return m_op(m_lhs[idx / m_shape.cols], m_rhs[idx]);
                    case 'R': return m_op(m_lhs[idx],                m_rhs[idx / m_shape.cols]);
                    case 'c': return m_op(m_lhs[idx % m_shape.cols], m_rhs[idx]);
                    case 'C': return m_op(m_lhs[idx],                m_rhs[idx % m_shape.cols]);
                    default: TB_THROW("Should never end up here");
                    }
                }
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (is_unary_expression_v)
                return m_op(m_lhs(rowIdx, colIdx));
            else
            {
                if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
                    return m_op(m_lhs, m_rhs(rowIdx, colIdx));
                else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
                    return m_op(m_lhs(rowIdx, colIdx), m_rhs);
                else if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
                {
                    switch (m_alignment)
                    {
                    case 'S': return m_op(m_lhs(rowIdx, colIdx), m_rhs(rowIdx, colIdx));
                    case 'r': return m_op(m_lhs(rowIdx,      0), m_rhs(rowIdx, colIdx));
                    case 'R': return m_op(m_lhs(rowIdx, colIdx), m_rhs(rowIdx,      0));
                    case 'c': return m_op(m_lhs(0,      colIdx), m_rhs(rowIdx, colIdx));
                    case 'C': return m_op(m_lhs(rowIdx, colIdx), m_rhs(0,      colIdx));
                    default: TB_THROW("Should never end up here");
                    }
                }

            }
        }

        constexpr size_t size() const
        {
            return m_shape.rows * m_shape.cols;
        }

        constexpr MatrixShape shape() const
        {
            return m_shape;
        }

        constexpr size_t rowCount() const
        {
            return m_shape.rows;
        }

        constexpr size_t colCount() const
        {
            return m_shape.cols;
        }

    private:
        OT_LHS m_lhs;
        OT_RHS m_rhs;
        char m_alignment;
        MatrixShape m_shape;
        static constexpr OP m_op = {};
    };

    template <class OP, class MT>
    using MatrixExprUnary = MatrixExpr<OP, MT, void*>;

    template <class OP, class MT1, class MT2>
    using MatrixExprBinary = MatrixExpr<OP, MT1, MT2>;
}
