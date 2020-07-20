#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>
#include <toolbox/Algebra/Types/MatrixShape.hpp>
#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    constexpr size_t DynamicSize = static_cast<size_t>(-1);

    template<class Type, size_t R, size_t C>
    class DenseMatrix : public Matrix<DenseMatrix<Type, R, C>>
    {
        static_assert(!((R == DynamicSize) ^ (C == DynamicSize)), "Matrix Dimensions R & C must be either fully dynamic or fully static");
        static_assert(R > 0 && C > 0, "Matrix Dimensions R & C must be greater than 0");
        constexpr static size_t internalSize = std::conditional_t<R != DynamicSize && C != DynamicSize, std::integral_constant<size_t, R * C>, std::integral_constant<size_t, DynamicSize>>::value;

    public:
        constexpr static bool hasDynamicSize = (internalSize == DynamicSize);

        using ElementType = Type;
        using DataType    = typename std::conditional_t<hasDynamicSize, Type*, Type[hasDynamicSize ? 1 : internalSize]>;

        constexpr explicit DenseMatrix() noexcept
            : m_shape(0, 0), m_size(0), m_capacity(0), m_data()
        {
            if constexpr (!hasDynamicSize)
                m_capacity = internalSize;
        }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount)
            : DenseMatrix(rowCount, colCount, 0) { }

        constexpr explicit DenseMatrix(const MatrixShape& shape)
            : DenseMatrix(shape.rows, shape.cols, 0) { }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount, Type init)
            : DenseMatrix()
        {
            this->allocate(rowCount, colCount);
            for (size_t i = 0; i < size(); ++i)
                m_data[i] = init;
        }

        constexpr DenseMatrix(std::initializer_list<std::initializer_list<Type>> matrix)
            : DenseMatrix()
        {
            this->allocate(matrix.size(), matrix.size() > 0 ? matrix.begin()->size() : 0);

            size_t i = 0;
            for (const auto& row : matrix)
            {
                TB_ENSURE(row.size() == m_shape.cols, "Input matrix has rows of varying sizes (found " << row.size() << " and " << m_shape.cols << ")");

                for (const auto& element : row)
                {
                    m_data[i] = element;
                    ++i;
                }
            }
        }

        template<class MT>
        constexpr DenseMatrix(const Matrix<MT>& rhs)
            : DenseMatrix((~rhs).rowCount(), (~rhs).colCount())
        {
            this->copyFrom(~rhs);
        }

        DenseMatrix(const DenseMatrix& rhs) noexcept
            : DenseMatrix()
        {
            this->copyFrom(rhs);
        }

        DenseMatrix(DenseMatrix&& rhs) noexcept
            : DenseMatrix()
        {
            this->moveFrom(std::move(rhs));
        }

        void operator=(const DenseMatrix& rhs) noexcept
        {
            this->copyFrom(rhs);
        }

        template<class Type2, size_t R2, size_t C2>
        void operator=(const DenseMatrix<Type2, R2, C2>& rhs) noexcept
        {
            this->copyFrom(rhs);
        }

        void operator=(DenseMatrix&& rhs) noexcept
        {
            this->moveFrom(std::move(rhs));
        }

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

        void operator+=(const DenseMatrix& rhs)
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

        void operator-=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs[i];
        }

        void operator-=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs;
        }

        void operator*=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs[i];
        }

        void operator*=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs;
        }

        void operator/=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

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

        ~DenseMatrix()
        {
            deallocate();
        }

        template<class Type2, size_t R2, size_t C2>
        constexpr void copyFrom(const DenseMatrix<Type2, R2, C2>& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            std::copy(rhs.data(), rhs.data() + rhs.size(), this->m_data);
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        constexpr void copyFrom(const MT& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                m_data[i] = rhs[i];
        }

        constexpr void moveFrom(DenseMatrix&& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            if constexpr (hasDynamicSize)
            {
                this->m_data = rhs.data();
                rhs.m_data   = nullptr;
            }
            else
            {
                std::move(rhs.data(), rhs.data() + rhs.size(), this->m_data);
            }

            rhs.m_size       = 0;
            rhs.m_shape.rows = 0;
            rhs.m_shape.cols = 0;
            rhs.m_capacity   = 0;
        }

        static constexpr DenseMatrix Identity(const size_t& size)
        {
            return DenseMatrix::Identity(size, size);
        }

        static constexpr DenseMatrix Identity(const size_t& rowSize, const size_t& colSize)
        {
            DenseMatrix result(rowSize, colSize, 0);
            for (size_t i = 0, size = rowSize < colSize ? rowSize : colSize; i < size; ++i)
                result(i, i) = 1;
            return result;
        }

    private:
        constexpr void allocate(size_t size)
        {
            this->allocate(size, 1);
        }

        constexpr void allocate(size_t rowCount, size_t colCount)
        {
            m_size       = rowCount * colCount;
            m_shape.rows = rowCount;
            m_shape.cols = colCount;

            if constexpr (hasDynamicSize)
            {
                if (m_size > m_capacity)
                {
                    deallocate();
                    m_capacity = m_size;
                    m_data     = new Type[m_capacity];
                }
            }
            else
            {
                TB_ENSURE(m_size       <= m_capacity, "Input size ("        << m_size << " = " << m_shape.rows << "x" << m_shape.cols << ") for static-sized storage cannot be larger than its static capacity (" << m_capacity << ")");
                TB_ENSURE(m_shape.rows <= R,          "Input row count ("   << m_shape.rows << ") for static-sized storage cannot be larger than its static row count (" << R << ")");
                TB_ENSURE(m_shape.cols <= C,          "Input column count(" << m_shape.cols << ") for static-sized storage cannot be larger than its static column count (" << C << ")");
            }
        }

        constexpr void deallocate()
        {
            if constexpr (hasDynamicSize)
            {
                if (m_data != nullptr)
                    delete[] m_data;
            }
        }

        MatrixShape m_shape;
        size_t m_size, m_capacity;
        DataType m_data;
    };
}
