#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>
#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    constexpr size_t DynamicSize = static_cast<size_t>(-1);

    template<class Type, size_t Size>
    class DenseStorage
    {
    private:
        constexpr static bool hasDynamicSize = (Size == DynamicSize);

    public:
        using ElementType = Type;
        using DataType    = typename std::conditional_t<hasDynamicSize, Type*, Type[hasDynamicSize ? 1 : Size]>;

        constexpr explicit DenseStorage() noexcept
            : m_rows(0), m_cols(0), m_capacity(0), m_data()
        {
            if constexpr (!hasDynamicSize)
            {
                m_capacity = Size;
            }
        }
        
        constexpr explicit DenseStorage(size_t rowCount, size_t colCount)
            : DenseStorage()
        {
            this->allocate(rowCount, colCount);
        }

        constexpr explicit DenseStorage(size_t rowCount, size_t colCount, Type init)
            : DenseStorage(rowCount, colCount)
        {
            for (size_t i = 0; i < size(); ++i)
                m_data[i] = init;
        }

        constexpr explicit DenseStorage(size_t size)
            : DenseStorage(size, 1) { }

        DenseStorage(std::initializer_list<Type> list)
            : DenseStorage(list.size(), 1)
        {
            size_t i = 0;
            for (const auto& element : list)
            {
                m_data[i] = element;
                ++i;
            }
        }
        
        DenseStorage(std::initializer_list<std::initializer_list<Type>> matrix)
            : DenseStorage(matrix.size(), (matrix.size() > 0 ? matrix.begin()->size() : 0))
        {
            size_t i = 0;
            for (const auto& row : matrix)
            {
                for (const auto& element : row)
                {
                    m_data[i] = element;
                    ++i;
                }
            }
        }

        DenseStorage(const DenseStorage& rhs) noexcept
            : DenseStorage()
        {
            this->copyFrom(rhs);
        }
        
        DenseStorage(DenseStorage&& rhs) noexcept
            : DenseStorage()
        {
            this->moveFrom(std::move(rhs));
        }
        
        DenseStorage& operator=(const DenseStorage& rhs) noexcept
        {
            this->copyFrom(rhs);
            return *this;
        }
        
        template<class Type2, size_t Size2>
        DenseStorage& operator=(const DenseStorage<Type2, Size2>& rhs) noexcept
        {
            this->copyFrom(rhs);
            return *this;
        }

        DenseStorage& operator=(DenseStorage&& rhs) noexcept
        {
            this->moveFrom(std::move(rhs));
            return *this;
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

        constexpr size_t size() const
        {
            return m_rows * m_cols;
        }

        constexpr size_t capacity() const
        {
            return m_capacity;
        }

        constexpr size_t rowCount() const
        {
            return m_rows;
        }

        constexpr size_t colCount() const
        {
            return m_cols;
        }

        friend std::ostream& operator<<(std::ostream& os, const DenseStorage& rhs)
        {
            os << "[ ";
            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                os << rhs[i] << " ";
            return os << "]";
        }

        const Type* data() const
        {
            return m_data;
        }

        Type* data()
        {
            return m_data;
        }
        
        ~DenseStorage()
        {
            deallocate();
        }

        template<class Type2, size_t Size2>
        constexpr void copyFrom(const DenseStorage<Type2, Size2>& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            std::copy(rhs.data(), rhs.data() + rhs.size(), this->m_data);
        }

        template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
        constexpr void copyFrom(const VT& rhs)
        {
            this->allocate(rhs.size(), 1);

            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                m_data[i] = rhs[i];
        }

        constexpr void moveFrom(DenseStorage&& rhs)
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

            rhs.m_rows     = 0;
            rhs.m_cols     = 0;
            rhs.m_capacity = 0;
        }

    protected:
        size_t m_rows, m_cols, m_capacity;
        DataType m_data;
    
    private:
        constexpr void allocate(size_t rowCount, size_t colCount)
        {
            const size_t size = rowCount * colCount;

            if constexpr (hasDynamicSize)
            {
                if (size > m_capacity)
                {
                    deallocate();
                    m_data     = new Type[size];
                    m_capacity = size;
                }
            }
            else
            {
                TB_ENSURE(size <= m_capacity, "Input size (" << size << ") for static-sized vector cannot be larger than its static size (" << m_capacity << ")");
            }

            m_rows = rowCount;
            m_cols = colCount;
        }

        constexpr void deallocate()
        {
            if constexpr (hasDynamicSize)
            {
                if (m_data != nullptr)
                    delete[] m_data;
            }
        }
    };
}
