#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>


namespace Toolbox
{
    template <class MT, int FLAG>
    class MatrixExprView : public Matrix<MatrixExprView<MT, FLAG>>, Expression
    {
        enum Flag { ROW = 0, COLUMN = 1, DIAGONAL = 2 };

    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = ElementType_t<MT>;

        constexpr explicit MatrixExprView(MT& mat)
            : m_mat(mat), m_idx(0)
        {
            static_assert(FLAG == DIAGONAL, "Constructor for Diagonal View was incorrectly called");

            const size_t m_rowCount = m_mat.rowCount();
            const size_t m_colCount = m_mat.colCount();
            m_idx = m_rowCount < m_colCount ? m_rowCount : m_colCount;
        }

        constexpr MatrixExprView(MT& mat, const size_t& idx)
            : m_mat(mat), m_idx(idx)
        {
            static_assert(FLAG == ROW || FLAG == COLUMN, "Constructor for Row/Column View was incorrectly called");

            if constexpr (FLAG == ROW)
            {
                TB_ENSURE(idx < m_mat.rowCount(), "Row index (" << idx << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else if constexpr (FLAG == COLUMN)
            {
                TB_ENSURE(idx < m_mat.colCount(), "Column index (" << idx << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            if constexpr (FLAG == ROW)
                return m_mat(m_idx, i);
            else if constexpr (FLAG == COLUMN)
                return m_mat(i, m_idx);
            else if constexpr (FLAG == DIAGONAL)
                return m_mat(i, i);
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            if constexpr (FLAG == ROW)
                return m_mat(m_idx, i);
            else if constexpr (FLAG == COLUMN)
                return m_mat(i, m_idx);
            else if constexpr (FLAG == DIAGONAL)
                return m_mat(i, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (FLAG == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(m_idx, colIdx);
            }
            else if constexpr (FLAG == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, m_idx);
            }
            else if constexpr (FLAG == DIAGONAL)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (FLAG == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(m_idx, colIdx);
            }
            else if constexpr (FLAG == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, m_idx);
            }
            else if constexpr (FLAG == DIAGONAL)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable");

            if constexpr (FLAG == ROW)
            {
                for (size_t i = 0, size = m_mat.colCount(); i < size; ++i)
                    m_mat(m_idx, i) *= rhs;
            }
            else if constexpr (FLAG == COLUMN)
            {
                for (size_t i = 0, size = m_mat.rowCount(); i < size; ++i)
                    m_mat(i, m_idx) *= rhs;
            }
            else if constexpr (FLAG == DIAGONAL)
            {
                for (size_t i = 0, size = m_mat.rowCount(); i < size; ++i)
                    m_mat(i, i) *= rhs;
            }
        }

        constexpr size_t size() const
        {
            if constexpr (FLAG == ROW)
                return m_mat.colCount();
            else if constexpr (FLAG == COLUMN)
                return m_mat.rowCount();
            else if constexpr (FLAG == DIAGONAL)
                return m_idx;
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (FLAG == ROW)
                return MatrixShape(1, m_mat.colCount());
            else if constexpr (FLAG == COLUMN)
                return MatrixShape(m_mat.rowCount(), 1);
            else if constexpr (FLAG == DIAGONAL)
                return MatrixShape(m_idx, 1);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (FLAG == ROW)
                return 1;
            else if constexpr (FLAG == COLUMN)
                return m_mat.rowCount();
            else if constexpr (FLAG == DIAGONAL)
                return m_idx;
        }

        constexpr size_t colCount() const
        {
            if constexpr (FLAG == ROW)
                return m_mat.colCount();
            else if constexpr (FLAG == COLUMN)
                return 1;
            else if constexpr (FLAG == DIAGONAL)
                return 1;
        }

    private:
        OT_MT m_mat;
        size_t m_idx;
    };

    template <class MT> using MatrixExprRow  = MatrixExprView<MT, 0>;
    template <class MT> using MatrixExprCol  = MatrixExprView<MT, 1>;
    template <class MT> using MatrixExprDiag = MatrixExprView<MT, 2>;
}
