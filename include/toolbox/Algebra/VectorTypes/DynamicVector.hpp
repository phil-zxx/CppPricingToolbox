#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>


namespace Toolbox
{
    /*
       Dynamic Vector Class
       
       Type = Type of the vector elements
       TF   = Transposed Flag (false = column vector, true = row vector)
    */
    template<class Type, bool TF = false>
    class DynamicVector : public Vector<DynamicVector<Type, TF>, TF>
    {
    public:
        using ElementType = Type;


        /* ========== Constructors ========== */

        DynamicVector() noexcept;
        explicit DynamicVector(size_t size) noexcept;
        DynamicVector(size_t size, const Type& initValue) noexcept;
        DynamicVector(std::initializer_list<Type> list) noexcept;

        DynamicVector(const DynamicVector& rhs) noexcept;
        DynamicVector(DynamicVector&& rhs) noexcept;

        template<size_t Size>
        explicit DynamicVector(const Type(&array)[Size]) noexcept;

        template<class VT>
        explicit DynamicVector(const Vector<VT, TF>& rhs);


        /* ========== Destructor ========== */

        ~DynamicVector();


        /* ========== Access Functions ========== */

        Type&       operator[](size_t idx) noexcept;
        const Type& operator[](size_t idx) const noexcept;
        
        Type* data()  noexcept;
        Type* begin() noexcept;
        Type* end()   noexcept;

        const Type* data()   const noexcept;
        const Type* begin()  const noexcept;
        const Type* cbegin() const noexcept;
        const Type* end()    const noexcept;
        const Type* cend()   const noexcept;


        /* ========== Operator Functions ========== */

        DynamicVector& operator=(const Type& rhs);
        DynamicVector& operator=(std::initializer_list<Type> rhs);
        
        DynamicVector& operator=(const DynamicVector& rhs);
        DynamicVector& operator=(DynamicVector&& rhs) noexcept;

        template<class VT> DynamicVector& operator= (const Vector<VT, TF>& rhs);
        template<class VT> DynamicVector& operator+=(const Vector<VT, TF>& rhs);
        template<class VT> DynamicVector& operator-=(const Vector<VT, TF>& rhs);
        template<class VT> DynamicVector& operator*=(const Vector<VT, TF>& rhs);
        template<class VT> DynamicVector& operator/=(const Vector<VT, TF>& rhs);
        
        template<class VT> bool operator==(const Vector<VT, TF>& rhs) const;
        template<class VT> bool operator!=(const Vector<VT, TF>& rhs) const;


        /* ========== Misc Functions ========== */

        size_t size() const noexcept;
        void resize(size_t newSize);
        void reserve(size_t newCapacity);

    private:
        void deallocate();

        size_t m_size, m_capacity;
        Type* m_vector;
    };

    // Inline Definitions

    /* ========== Constructors ========== */

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector() noexcept
        : m_size(0), m_capacity(0), m_vector(nullptr) { }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector(size_t size) noexcept
        : m_size(size), m_capacity(size), m_vector(nullptr)
    {
        if (size > 0)
            m_vector = new Type[size];
    }
    
    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector(size_t size, const Type& initValue) noexcept
        : DynamicVector(size)
    {
        for (size_t i = 0; i < size; ++i)
            m_vector[i] = initValue;
    }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector(std::initializer_list<Type> list) noexcept
        : DynamicVector(list.size())
    {
        std::fill(std::copy(list.begin(), list.end(), begin()), end(), Type());
    }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector(const DynamicVector& rhs) noexcept
        : DynamicVector(rhs.m_size)
    {
        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] = rhs.m_vector[i];
    }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::DynamicVector(DynamicVector&& rhs) noexcept
        : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_vector(rhs.m_vector)
    {
        rhs.size_     = 0;
        rhs.capacity_ = 0;
        rhs.v_        = nullptr;
    }

    template<class Type, bool TF>
    template<size_t Size>
    inline DynamicVector<Type, TF>::DynamicVector(const Type(&array)[Size]) noexcept
        : DynamicVector(Size)
    {
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = array[i];
    }

    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>::DynamicVector(const Vector<VT, TF>& rhs)
    {
        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] = rhs[i];
    }


    /* ========== Destructor ========== */

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>::~DynamicVector()
    {
        this->deallocate();
    }


    /* ========== Access Functions ========== */

    template<class Type, bool TF>
    inline Type& DynamicVector<Type, TF>::operator[](size_t idx) noexcept
    {
        return m_vector[idx];
    }
    
    template<class Type, bool TF>
    inline const Type& DynamicVector<Type, TF>::operator[](size_t idx) const noexcept
    {
        return m_vector[idx];
    }

    template<class Type, bool TF>
    inline Type* DynamicVector<Type, TF>::data() noexcept
    {
        return m_vector;
    }
    
    template<class Type, bool TF>
    inline Type* DynamicVector<Type, TF>::begin() noexcept
    {
        return m_vector;
    }
    
    template<class Type, bool TF>
    inline Type* DynamicVector<Type, TF>::end() noexcept
    {
        return m_vector + m_size;
    }

    template<class Type, bool TF>
    inline const Type* DynamicVector<Type, TF>::data() const noexcept
    {
        return m_vector;
    }

    template<class Type, bool TF>
    inline const Type* DynamicVector<Type, TF>::begin() const noexcept
    {
        return m_vector;
    }

    template<class Type, bool TF>
    inline const Type* DynamicVector<Type, TF>::cbegin() const noexcept
    {
        return m_vector;
    }

    template<class Type, bool TF>
    inline const Type* DynamicVector<Type, TF>::end() const noexcept
    {
        return m_vector + m_size;
    }

    template<class Type, bool TF>
    inline const Type* DynamicVector<Type, TF>::cend() const noexcept
    {
        return m_vector;
    }


    /* ========== Operator Functions ========== */

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator=(const Type& rhs)
    {
        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] = rhs;

        return *this;
    }
    
    template<class Type, bool TF>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator=(std::initializer_list<Type> rhs)
    {
        this->resize(rhs.size());
        std::copy(rhs.begin(), rhs.end(), m_vector);

        return *this;
    }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator=(const DynamicVector& rhs)
    {
        if (&rhs == this) 
            return *this;

        this->resize(rhs.m_size);
        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] = rhs[i];

        return *this;
    }

    template<class Type, bool TF>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator=(DynamicVector&& rhs) noexcept
    {
        this->deallocate();

        m_size     = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_vector   = rhs.m_vector;

        rhs.m_size     = 0;
        rhs.m_capacity = 0;
        rhs.m_vector   = nullptr;

        return *this;
    }

    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;
        this->resize(rhsVec.size());

        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] = rhsVec[i];

        return *this;
    }
    
    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator+=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != m_size)
            throw std::invalid_argument("Vectors are of different sizes");

        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] += rhsVec[i];

        return *this;
    }
    
    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator-=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != m_size)
            throw std::invalid_argument("Vectors are of different sizes");

        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] -= rhsVec[i];

        return *this;
    }
    
    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator*=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != m_size)
            throw std::invalid_argument("Vectors are of different sizes");

        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] *= rhsVec[i];

        return *this;
    }
    
    template<class Type, bool TF>
    template<class VT>
    inline DynamicVector<Type, TF>& DynamicVector<Type, TF>::operator/=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != m_size)
            throw std::invalid_argument("Vectors are of different sizes");

        for (size_t i = 0; i < m_size; ++i)
            m_vector[i] /= rhsVec[i];

        return *this;
    }

    template<class Type, bool TF>
    template<class VT>
    inline bool DynamicVector<Type, TF>::operator==(const Vector<VT, TF>& rhs) const
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != size())
            return false;

        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_vector[i] != rhsVec[i])
                return false;
        }

        return true;
    }

    template<class Type, bool TF>
    template<class VT>
    inline bool DynamicVector<Type, TF>::operator!=(const Vector<VT, TF>& rhs) const
    {
        return !(*this == rhs);
    }


    /* ========== Misc Functions ========== */

    template<class Type, bool TF>
    inline size_t DynamicVector<Type, TF>::size() const noexcept
    {
        return m_size;
    }

    template<class Type, bool TF>
    inline void DynamicVector<Type, TF>::resize(size_t newSize)
    {
        if (newSize > m_capacity)
        {
            this->deallocate();

            m_vector   = new Type[newSize];
            m_capacity = newSize;
        }

        m_size = newSize;
    }

    template<class Type, bool TF>
    inline void DynamicVector<Type, TF>::reserve(size_t newCapacity)
    {
        if (newCapacity > m_capacity)
        {
            this->deallocate();

            m_vector = new Type[newSize];
        }

        m_capacity = newCapacity;
    }
    
    template<class Type, bool TF>
    inline void DynamicVector<Type, TF>::deallocate()
    {
        if (m_vector != nullptr)
            delete[] m_vector;
    }
}
