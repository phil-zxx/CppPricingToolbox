#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Misc/Maths.hpp>


namespace Toolbox
{
    template <class MT, bool TF>
    class MatrixExprRowColView : public Matrix<MatrixExprRowColView<MT, TF>>, Expression
    {
        enum TypeFlag : bool { ROW = false, COLUMN = true };

    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprRowColView(MT& mat, const size_t& idx)
            : m_mat(mat), m_idx(idx), m_size(1)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(idx < m_mat.rowCount(), "Row index (" << idx << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(idx < m_mat.colCount(), "Column index (" << idx << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr explicit MatrixExprRowColView(MT& mat, const size_t& idx, const size_t& size)
            : m_mat(mat), m_idx(idx), m_size(size)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(idx + size <= m_mat.rowCount(), "Row index + size (" << idx + size << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(idx + size <= m_mat.colCount(), "Column index + size (" << idx + size << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            if constexpr (TF == ROW)
            {
                const size_t colCount = m_mat.colCount();
                return m_mat(m_idx + i / colCount, i % colCount);
            }
            else if constexpr (TF == COLUMN)
            {
                return m_mat(i / m_size, m_idx + i % m_size);
            }
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            if constexpr (TF == ROW)
            {
                const size_t colCount = m_mat.colCount();
                return m_mat(m_idx + i / colCount, i % colCount);
            }
            else if constexpr (TF == COLUMN)
            {
                return m_mat(i / m_size, m_idx + i % m_size);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx < m_size, "Row index (" << rowIdx << ") is out of bounds (only have " << m_size << " rows)");
                return m_mat(m_idx + rowIdx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx < m_size, "Column index (" << colIdx << ") is out of bounds (only have " << m_size << " columns)");
                return m_mat(rowIdx, m_idx + colIdx);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx < m_size, "Row index (" << rowIdx << ") is out of bounds (only have " << m_size << " rows)");
                return m_mat(m_idx + rowIdx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx < m_size, "Column index (" << colIdx << ") is out of bounds (only have " << m_size << " columns)");
                return m_mat(rowIdx, m_idx + colIdx);
            }
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable in order to apply operator*=");

            if constexpr (TF == ROW)
            {
                for (size_t rowIdx = m_idx, rowCount = m_idx + m_size; rowIdx < rowCount; ++rowIdx)
                    for (size_t colIdx = 0, colCount = m_mat.colCount(); colIdx < colCount; ++colIdx)
                        m_mat(rowIdx, colIdx) *= rhs;
            }
            else if constexpr (TF == COLUMN)
            {
                for (size_t colIdx = m_idx, colCount = m_idx + m_size; colIdx < colCount; ++colIdx)
                    for (size_t rowIdx = 0, rowCount = m_mat.rowCount(); rowIdx < rowCount; ++rowIdx)
                        m_mat(rowIdx, colIdx) *= rhs;
            }
        }

        template<class MT2, class = std::enable_if_t<is_matrix_v<MT2>>>
        void operator-=(const MT2& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable in order to apply operator-=");

            TB_ENSURE(this->shape() == rhs.shape(), "Shapes of lhs (" << m_mat.shape() << ") and rhs (" << rhs.shape() << ") do not match");

            if constexpr (TF == ROW)
            {
                for (size_t rowIdx = m_idx, rowCount = m_idx + m_size; rowIdx < rowCount; ++rowIdx)
                    for (size_t colIdx = 0, colCount = m_mat.colCount(); colIdx < colCount; ++colIdx)
                        m_mat(rowIdx, colIdx) -= rhs(rowIdx - m_idx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                for (size_t colIdx = m_idx, colCount = m_idx + m_size; colIdx < colCount; ++colIdx)
                    for (size_t rowIdx = 0, rowCount = m_mat.rowCount(); rowIdx < rowCount; ++rowIdx)
                        m_mat(rowIdx, colIdx) -= rhs(rowIdx, colIdx - m_idx);
            }
        }

        constexpr size_t size() const
        {
            if constexpr (TF == ROW)
                return m_mat.colCount() * m_size;
            else if constexpr (TF == COLUMN)
                return m_mat.rowCount() * m_size;
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (TF == ROW)
                return MatrixShape(m_size, m_mat.colCount());
            else if constexpr (TF == COLUMN)
                return MatrixShape(m_mat.rowCount(), m_size);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (TF == ROW)
                return m_size;
            else if constexpr (TF == COLUMN)
                return m_mat.rowCount();
        }

        constexpr size_t colCount() const
        {
            if constexpr (TF == ROW)
                return m_mat.colCount();
            else if constexpr (TF == COLUMN)
                return m_size;
        }

    private:
        OT_MT m_mat;
        size_t m_idx, m_size;
    };

    template <class MT> using MatrixExprRowView = MatrixExprRowColView<MT, false>;
    template <class MT> using MatrixExprColView = MatrixExprRowColView<MT, true>;
}
