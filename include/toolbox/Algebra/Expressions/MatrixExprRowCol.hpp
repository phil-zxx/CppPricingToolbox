#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>


namespace Toolbox
{
    template <class MT, bool IS_ROW>
    class MatrixExprView : public Matrix<MatrixExprView<MT, IS_ROW>, false>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = ElementType_t<MT>;

        constexpr MatrixExprView(MT& mat, const size_t& idx)
            : m_mat(mat), m_idx(idx)
        {
            if constexpr (IS_ROW)
            {
                TB_ENSURE(idx < m_mat.rowCount(), "Row index (" << idx << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else
            {
                TB_ENSURE(idx < m_mat.colCount(), "Column index (" << idx << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            if constexpr (IS_ROW)
                return m_mat(m_idx, i);
            else
                return m_mat(i, m_idx);
        }
        
        constexpr decltype(auto) operator[](size_t i)
        {
            if constexpr (IS_ROW)
                return m_mat(m_idx, i);
            else
                return m_mat(i, m_idx);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (IS_ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(m_idx, colIdx);
            }
            else
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, m_idx);
            }
        }
        
        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (IS_ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(m_idx, colIdx);
            }
            else
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, m_idx);
            }
        }

        template<class = std::enable_if_t<is_mutable_matrix_v<MT>>>
        void operator*=(const ElementType& rhs)
        {
            if constexpr (IS_ROW)
            {
                for (size_t i = 0, size = m_mat.colCount(); i < size; ++i)
                    m_mat(m_idx, i) *= rhs;
            }
            else
            {
                for (size_t i = 0, size = m_mat.rowCount(); i < size; ++i)
                    m_mat(i, m_idx) *= rhs;
            }
        }

        constexpr size_t size() const
        {
            if constexpr (IS_ROW)
                return m_mat.colCount();
            else
                return m_mat.rowCount();
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (IS_ROW)
                return MatrixShape(1, m_mat.colCount());
            else
                return MatrixShape(m_mat.rowCount(), 1);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (IS_ROW)
                return 1;
            else
                return m_mat.rowCount();
        }

        constexpr size_t colCount() const
        {
            if constexpr (IS_ROW)
                return m_mat.colCount();
            else
                return 1;
        }

    private:
        OT_MT m_mat;
        const size_t m_idx;
    };

    template <class MT> using MatrixExprRow = MatrixExprView<MT, true>;
    template <class MT> using MatrixExprCol = MatrixExprView<MT, false>;
}
