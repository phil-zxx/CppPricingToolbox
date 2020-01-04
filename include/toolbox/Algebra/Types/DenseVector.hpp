#pragma once

#include <toolbox/Algebra/Types/Base/Vector.hpp>
#include <toolbox/Algebra/Storage/DenseStorage.hpp>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF>
    class DenseVector : public Vector<DenseVector<Type, Size, TF>, TF>
    {
    public:
        using ElementType = typename Type;
        using StorageType = typename DenseStorage<Type, Size>;

        constexpr explicit DenseVector() noexcept
            : m_storage() { }

        constexpr explicit DenseVector(size_t size)
            : m_storage(size) { }

        constexpr explicit DenseVector(size_t size, Type init)
            : m_storage(size, init) { }

        DenseVector(std::initializer_list<Type> list)
            : m_storage(list) { }

        template<class VT>
        constexpr DenseVector(const Vector<VT, TF>& rhs)
            : m_storage((~rhs).size())
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

        const StorageType& storage() const
        {
            return m_storage;
        }

        StorageType& storage()
        {
            return m_storage;
        }

        ElementType operator[](size_t idx)
        {
            return m_storage[idx];
        }

        const ElementType& operator[](size_t idx) const
        {
            return m_storage[idx];
        }

        friend std::ostream& operator<<(std::ostream& os, const DenseVector& rhs)
        {
            return os << rhs.m_storage;
        }

        template<class VT>
        DenseVector& operator=(const Vector<VT, TF>& rhs)
        {
            if constexpr (has_storage_v<VT>)
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
