#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>
#include <toolbox/Algebra/Types/MatrixShape.hpp>
#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    template<class Type>
    class CustomMatrix : public Matrix<CustomMatrix<Type>>
    {
    public:
        using ElementType = Type;

        explicit CustomMatrix(size_t rowCount, size_t colCount, Type* externalPtr)
            : m_shape(rowCount, colCount), m_size(rowCount * colCount), m_capacity(rowCount* colCount), m_data(externalPtr) { }

        constexpr const ElementType& operator[](size_t idx) const
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr ElementType& operator[](size_t idx)
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr const ElementType& at(size_t idx) const
        {
            TB_ENSURE(idx < size(), "Index (" << idx << ") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr ElementType& at(size_t idx)
        {
            TB_ENSURE(idx < size(), "Index (" << idx <<") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr const ElementType& operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        constexpr ElementType& operator()(size_t rowIdx, size_t colIdx)
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator+=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs[i];
        }

        void operator+=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator-=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply -= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs[i];
        }

        void operator-=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator*=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply *= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs[i];
        }

        void operator*=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator/=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply /= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs[i];
        }

        void operator/=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs;
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
            return m_size;
        }

        constexpr size_t capacity() const
        {
            return m_capacity;
        }

        const Type* data() const
        {
            return m_data;
        }

        Type* data()
        {
            return m_data;
        }

        const Type* begin() const
        {
            return m_data;
        }

        const Type* end() const
        {
            return m_data + size();
        }

        Type* begin()
        {
            return m_data;
        }

        Type* end()
        {
            return m_data + size();
        }

    private:
        MatrixShape m_shape;
        size_t m_size, m_capacity;
        Type* m_data;
    };
}
