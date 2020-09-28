#pragma once

#include <toolbox/Algebra/Types/Matrix.hpp>


namespace TB
{
    template <class MT>
    class MatrixExprTrans : public Matrix<MatrixExprTrans<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprTrans(const MT& mat)
            : m_mat(mat), m_rowCount(m_mat.colCount()), m_colCount(m_mat.rowCount()) { }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return m_mat[(i % m_colCount) * m_rowCount + (i / m_colCount)];
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            return m_mat(colIdx, rowIdx);  // (rowIdx, colIdx) are swapped to (colIdx, rowIdx) as this is transposed
        }

        constexpr size_t size() const
        {
            return m_mat.size();
        }

        constexpr MatrixShape shape() const
        {
            return m_mat.shape().transposed();
        }

        constexpr size_t rowCount() const
        {
            return m_rowCount;
        }

        constexpr size_t colCount() const
        {
            return m_colCount;
        }

    private:
        OT_MT m_mat;
        const size_t m_rowCount, m_colCount;
    };
}
