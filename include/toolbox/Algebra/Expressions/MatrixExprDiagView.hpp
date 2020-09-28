#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Misc/Maths.hpp>


namespace TB
{
    template <class MT, bool TF>
    class MatrixExprDiagView : public Matrix<MatrixExprDiagView<MT, TF>>, Expression
    {
        enum TypeFlag : bool { ROW = false, COLUMN = true };

    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprDiagView(MT& mat)
            : m_mat(mat), m_size(TB_min(m_mat.rowCount(), m_mat.colCount())) { }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < m_size, "Index (" << i << ") is out if bounds");
            return m_mat(i, i);
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < m_size, "Index (" << i << ") is out if bounds");
            return m_mat(i, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
            else if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(colIdx, colIdx);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
            else if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(colIdx, colIdx);
            }
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable");

            for (size_t i = 0, size = m_size; i < size; ++i)
                m_mat(i, i) *= rhs;
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (TF == COLUMN)
                return MatrixShape(m_size, 1);
            else if constexpr (TF == ROW)
                return MatrixShape(1, m_size);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (TF == COLUMN)
                return m_size;
            else if constexpr (TF == ROW)
                return 1;
        }

        constexpr size_t colCount() const
        {
            if constexpr (TF == COLUMN)
                return 1;
            else if constexpr (TF == ROW)
                return m_size;
        }

    private:
        OT_MT m_mat;
        size_t m_size;
    };
}
