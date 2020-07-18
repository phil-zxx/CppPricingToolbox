#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>


namespace Toolbox
{
    template <class MT>
    class MatrixExprSubmatrixView : public Matrix<MatrixExprSubmatrixView<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = ElementType_t<MT>;

        constexpr explicit MatrixExprSubmatrixView(MT& mat, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
            : m_mat(mat), m_rowIdx(rowIdx), m_colIdx(colIdx), m_rowSize(rowSize), m_colSize(colSize)
        {
            TB_ENSURE(rowIdx + rowSize <= m_mat.rowCount(), "Row index + size ("    << rowIdx + rowSize << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            TB_ENSURE(colIdx + colSize <= m_mat.colCount(), "Column index + size (" << colIdx + colSize << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            return m_mat(m_rowIdx + i / m_colSize, m_colIdx + i % m_colSize);
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            return m_mat(m_rowIdx + i / m_colSize, m_colIdx + i % m_colSize);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_rowSize, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_rowSize << " rows)");
            TB_ENSURE(colIdx < m_colSize, "Column index (" << colIdx << ") is out of bounds (only have " << m_colSize << " columns)");

            return m_mat(m_rowIdx + rowIdx, m_colIdx + colIdx);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            TB_ENSURE(rowIdx < m_rowSize, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_rowSize << " rows)");
            TB_ENSURE(colIdx < m_colSize, "Column index (" << colIdx << ") is out of bounds (only have " << m_colSize << " columns)");

            return m_mat(m_rowIdx + rowIdx, m_colIdx + colIdx);
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable");

            for (size_t rowIdx = m_rowIdx, rowCount = m_rowIdx + m_rowSize; rowIdx < rowCount; ++rowIdx)
                for (size_t colIdx = m_colIdx, colCount = m_colIdx + m_colSize; colIdx < colCount; ++colIdx)
                    m_mat(rowIdx, colIdx) *= rhs;
        }

        constexpr size_t size() const
        {
            return m_rowSize * m_colSize;
        }

        constexpr MatrixShape shape() const
        {
            return MatrixShape(m_rowSize, m_colSize);
        }

        constexpr size_t rowCount() const
        {
            return m_rowSize;
        }

        constexpr size_t colCount() const
        {
            return m_colSize;
        }

    private:
        OT_MT m_mat;
        size_t m_rowIdx, m_colIdx, m_rowSize, m_colSize;
    };
}
