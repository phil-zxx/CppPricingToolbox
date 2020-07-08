#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>


namespace Toolbox
{
    template <class MT>
    class MatrixExprDiag : public Matrix<MatrixExprDiag<MT>, false>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ElementType = ElementType_t<MT>;

        constexpr MatrixExprDiag(const MT& mat)
            : m_mat(mat), m_size(0)
        {
            const size_t m_rowCount = m_mat.rowCount();
            const size_t m_colCount = m_mat.colCount();
            m_size = m_rowCount < m_colCount ? m_rowCount : m_colCount;
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return m_mat(i, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
            return m_mat(rowIdx, rowIdx);
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr MatrixShape shape() const
        {
            return MatrixShape(m_size, 1);
        }

        constexpr size_t rowCount() const
        {
            return m_size;
        }

        constexpr size_t colCount() const
        {
            return 1;
        }

    private:
        OT_MT m_mat;
        size_t m_size;
    };
}
