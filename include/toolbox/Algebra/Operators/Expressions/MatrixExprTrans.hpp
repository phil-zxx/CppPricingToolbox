#pragma once

#include <toolbox/Algebra/Typetraits/ApplyOperator.hpp>
#include <toolbox/Algebra/Typetraits/ElementType.hpp>
#include <toolbox/Algebra/Typetraits/OpResultType.hpp>


namespace Toolbox
{
    template <class OP, class MT, bool SO>
    class MatrixExprTrans : public Matrix<MatrixExprTrans<OP, MT, SO>, SO>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ET_MT       = ElementType_t<MT>;
        using ElementType = OpResultType_t<OP, ET_MT>;

        constexpr MatrixExprTrans(const MT& mat)
            : m_mat(mat) { }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return apply_unary<OP, MT>(m_mat, i);
        }
        
        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            return apply_unary(m_mat, colIdx, rowIdx);  // (rowIdx, colIdx) are swapped to (colIdx, rowIdx) as this is transposed
        }

        constexpr size_t size() const
        {
            return m_mat.size();
        }

        constexpr size_t rowCount() const
        {
            return m_mat.colCount();  // rowCount() is changed to colCount() as this is transposed
        }

        constexpr size_t colCount() const
        {
            return m_mat.rowCount();  // colCount() is changed to rowCount() as this is transposed
        }

    private:
        OT_MT m_mat;
    };
}
