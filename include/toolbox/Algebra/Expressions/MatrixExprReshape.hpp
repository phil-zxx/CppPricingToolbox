#pragma once

#include <toolbox/Core/Error.hpp>


namespace TB
{
    template <class MT>
    class MatrixExprReshape : public Matrix<MatrixExprReshape<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprReshape(const MT& mat, const size_t& rowCount, const size_t& colCount)
            : m_mat(mat), m_rowCount(rowCount), m_colCount(colCount)
        {
            TB_ENSURE(mat.size() == rowCount * colCount, "Need matrix size (" << mat.size() << ") to be equal to product of row & col count (" << rowCount << " * " << colCount << ")");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return m_mat[i];
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            return m_mat[rowIdx * m_colCount + colIdx];
        }

        constexpr size_t size() const
        {
            return m_mat.size();
        }

        constexpr MatrixShape shape() const
        {
            return MatrixShape(m_rowCount, m_colCount);
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
