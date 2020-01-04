#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    constexpr size_t DynamicSize = static_cast<size_t>(-1);

    template<class Type, size_t Size = DynamicSize>
    class DenseStorage
    {
    private:
        constexpr static bool hasDynamicSize = (Size == DynamicSize);

    public:
        using ElementType = Type;
        using DataType    = typename std::conditional_t<hasDynamicSize, Type*, Type[hasDynamicSize ? 1 : Size]>;

        constexpr explicit DenseStorage() noexcept
            : m_size(0), m_capacity(0), m_data()
        {
            if constexpr (!hasDynamicSize)
            {
                m_capacity = Size;
            }
        }

        constexpr explicit DenseStorage(size_t size)
            : DenseStorage()
        {
            this->allocate(size);
        }

        constexpr explicit DenseStorage(size_t size, Type init)
            : DenseStorage(size)
        {
            for (size_t i = 0; i < size; ++i)
                m_data[i] = init;
        }

        DenseStorage(std::initializer_list<Type> list)
            : DenseStorage(list.size())
        {
            size_t i = 0;
            for (const auto& element : list)
            {
                m_data[i] = element;
                ++i;
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
            return this->m_data[idx];
        }

        constexpr ElementType& operator[](size_t idx)
        {
            return this->m_data[idx];
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr size_t capacity() const
        {
            return m_capacity;
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
            this->allocate(rhs.size());

            std::copy(rhs.data(), rhs.data() + rhs.size(), this->m_data);
        }

        template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
        constexpr void copyFrom(const VT& rhs)
        {
            this->allocate(rhs.size());

            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                m_data[i] = rhs[i];
        }

        constexpr void moveFrom(DenseStorage&& rhs)
        {
            this->allocate(rhs.size());

            if constexpr (hasDynamicSize)
            {
                this->m_data = rhs.data();
                rhs.m_data = nullptr;
            }
            else
            {
                std::move(rhs.data(), rhs.data() + rhs.size(), this->m_data);
            }

            rhs.m_size = 0;
            rhs.m_capacity = 0;
        }

    protected:
        size_t m_size, m_capacity;
        DataType m_data;
    
    private:
        constexpr void allocate(size_t size)
        {
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
                if (size > m_capacity)
                    throw("Input size for static-sized vector cannot be larger than static size");
            }
            
            m_size = size;
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
