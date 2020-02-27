#pragma once

#include <toolbox/Algebra/Types/Base/Matrix.hpp>
#include <toolbox/Algebra/Storage/DenseStorage.hpp>


namespace Toolbox
{
    template<class Type, size_t R, size_t C, bool SO>
    class DenseMatrix : public Matrix<DenseMatrix<Type, R, C, SO>, SO>
    {
    private:
        static constexpr size_t MatrixSize = std::conditional_t<R != DynamicSize && C != DynamicSize,
                                                std::integral_constant<size_t, R * C>,
                                                std::integral_constant<size_t, DynamicSize>>::value;

    public:
        using ElementType = typename Type;
        using StorageType = typename DenseStorage<Type, MatrixSize>;

        constexpr explicit DenseMatrix() noexcept
            : m_storage() { }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount)
            : m_storage(rowCount, rowCount) { }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount, Type init)
            : m_storage(rowCount, rowCount, init) { }

        DenseMatrix(std::initializer_list<std::initializer_list<Type>> matrix)
            : m_storage(matrix) {} 
        
        template<class MT>
        constexpr DenseMatrix(const Matrix<MT, SO>& rhs)
            : m_storage((~rhs).rowCount(), (~rhs).colCount())
        {
            *this = ~rhs;
        }

        size_t size() const
        {
            return m_storage.size();
        }

        size_t capacity() const
        {
            return m_storage.capacity();
        }

        constexpr size_t rowCount() const
        {
            return m_storage.rowCount();
        }

        constexpr size_t colCount() const
        {
            return m_storage.colCount();
        }

        const StorageType& storage() const
        {
            return m_storage;
        }

        StorageType& storage()
        {
            return m_storage;
        }

        const Type* begin() const
        {
            return m_storage.data();
        }

        const Type* end() const
        {
            return m_storage.data() + m_storage.size();
        }

        Type* begin()
        {
            return m_storage.data();
        }

        Type* end()
        {
            return m_storage.data() + m_storage.size();
        }

        ElementType& operator[](size_t idx)
        {
            return m_storage[idx];
        }

        const ElementType& operator[](size_t idx) const
        {
            return m_storage[idx];
        }

        ElementType& at(size_t idx)
        {
            return m_storage.at(idx);
        }

        const ElementType& at(size_t idx) const
        {
            return m_storage.at(idx);
        }

        const ElementType& operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (SO == false)
            {
                return m_storage[rowIdx * m_storage.colCount() + colIdx];
            }
            else
            {
                return m_storage[rowIdx * m_storage.rowCount() + colIdx];
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const DenseMatrix& rhs)
        {
            return os << rhs.m_storage;
        }

        template<class MT>
        DenseMatrix& operator=(const Matrix<MT, SO>& rhs)
        {
            if constexpr (has_storage_v<MT>)
            {
                m_storage.copyFrom((~rhs).storage());
            }
            else
            {
                m_storage.copyFrom(~rhs);
            }
            return *this;
        }

    protected:
        StorageType m_storage;
    };
}
