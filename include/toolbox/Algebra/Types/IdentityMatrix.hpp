#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>
#include <toolbox/Algebra/Types/MatrixShape.hpp>
#include <toolbox/Core/Error.hpp>


namespace TB
{
    template<class Type>
    class IdentityMatrix : public Matrix<IdentityMatrix<Type>>
    {
    public:
        using ElementType = Type;

        constexpr explicit IdentityMatrix(size_t size) noexcept
            : m_shape(size, size) { }

        constexpr explicit IdentityMatrix(size_t rowCount, size_t colCount) noexcept
            : m_shape(rowCount, colCount) { }

        constexpr explicit IdentityMatrix(const MatrixShape& shape) noexcept
            : m_shape(shape) { }

        constexpr ElementType operator[](size_t idx) const
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return idx / m_shape.cols == idx % m_shape.cols ? 1 : 0;
        }

        constexpr ElementType at(size_t idx) const
        {
            TB_ENSURE(idx < size(), "Index (" << idx << ") is out of bounds (size is only " << size() << ")");
            return idx / m_shape.cols == idx % m_shape.cols ? 1 : 0;
        }

        constexpr ElementType operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return rowIdx == colIdx ? 1 : 0;
        }

        constexpr const MatrixShape& shape() const
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

        constexpr size_t size() const
        {
            return m_shape.rows * m_shape.cols;
        }

    private:
        MatrixShape m_shape;
    };
}
