#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>
#include <toolbox/Algebra/BaseTypes/Assert.hpp>


namespace Toolbox
{
    /*
       Static Vector Class

       Type = Type of the vector elements
       Size = Fixed size/length of the vector
       TF   = Transposed Flag (false = column vector, true = row vector)
    */
    template<class Type, size_t Size, bool TF = false>
    class StaticVector : public Vector<StaticVector<Type, Size, TF>, TF>
    {
    public:
        using ElementType = Type;


        /* ========== Constructors ========== */

        constexpr StaticVector() noexcept;
        constexpr explicit StaticVector(const Type& initValue) noexcept;
        constexpr explicit StaticVector(const Type(&array)[Size]) noexcept;
        constexpr explicit StaticVector(std::initializer_list<Type> list) noexcept;

        constexpr StaticVector(const StaticVector& rhs) noexcept;
        
        template<class Type2>
        constexpr explicit StaticVector(const StaticVector<Type2, Size, TF>& rhs) noexcept;

        template<class VT>
        constexpr explicit StaticVector(const Vector<VT, TF>& rhs);


        /* ========== Destructor ========== */

        ~StaticVector() = default;


        /* ========== Access Functions ========== */

        constexpr Type& operator[](size_t idx) noexcept;
        constexpr const Type& operator[](size_t idx) const noexcept;


        /* ========== Operator Functions ========== */

        StaticVector& operator=(const Type& rhs);
        StaticVector& operator=(std::initializer_list<Type> rhs);

        StaticVector& operator=(const StaticVector& rhs);

        template<class VT> StaticVector& operator= (const Vector<VT, TF>& rhs);
        template<class VT> StaticVector& operator+=(const Vector<VT, TF>& rhs);
        template<class VT> StaticVector& operator-=(const Vector<VT, TF>& rhs);
        template<class VT> StaticVector& operator*=(const Vector<VT, TF>& rhs);
        template<class VT> StaticVector& operator/=(const Vector<VT, TF>& rhs);

        template<class VT> bool operator==(const Vector<VT, TF>& rhs) const;
        template<class VT> bool operator!=(const Vector<VT, TF>& rhs) const;

        /* ========== Misc Functions ========== */

        constexpr size_t size() const noexcept;

    private:
        Type m_vector[Size > 0 ? Size : 1];
    };

    // Inline Definition

    template<class Type, size_t Size, bool TF>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector() noexcept
        : m_vector() { }

    template<class Type, size_t Size, bool TF>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(const Type& initValue) noexcept
        : m_vector()
    {
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = initValue;
    }

    template<class Type, size_t Size, bool TF>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(const Type(&array)[Size]) noexcept
        : m_vector()
    {
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = array[i];
    }

    template<class Type, size_t Size, bool TF>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(std::initializer_list<Type> list) noexcept
        : m_vector()
    {
        //TB_ASSERT(list.size() <= Size, "Input vector is too large");

        size_t i = 0;
        for (const auto& element : list)
        {
            m_vector[i] = element;
            ++i;
        }
    }

    template<class Type, size_t Size, bool TF>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(const StaticVector& rhs) noexcept = default;

    template<class Type, size_t Size, bool TF>
    template<class Type2>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(const StaticVector<Type2, Size, TF>& rhs)  noexcept
        : m_vector()
    {
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = rhs[i];
    }

    template<class Type, size_t Size, bool TF>
    template<class VT>
    inline constexpr StaticVector<Type, Size, TF>::StaticVector(const Vector<VT, TF>& rhs)
        : m_vector()
    {
        TB_ASSERT((~rhs).size() == Size, "Input vector is of a different size");
        
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = (~rhs)[i];
    }


    /* ========== Access Functions ========== */

    template<class Type, size_t Size, bool TF>
    inline constexpr Type& StaticVector<Type, Size, TF>::operator[](size_t idx) noexcept
    {
        return m_vector[idx];
    }

    template<class Type, size_t Size, bool TF>
    inline constexpr const Type& StaticVector<Type, Size, TF>::operator[](size_t idx) const noexcept
    {
        return m_vector[idx];
    }


    /* ========== Operator Functions ========== */

    template<class Type, size_t Size, bool TF>
    StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator=(const Type& rhs)
    {
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = rhs;

        return *this;
    }

    template<class Type, size_t Size, bool TF>
    StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator=(std::initializer_list<Type> rhs)
    {
        TB_ASSERT(rhs.size() == Size, "Input vector has the wrong size");

        std::copy(rhs.begin(), rhs.end(), m_vector);

        return *this;
    }

    template<class Type, size_t Size, bool TF>
    StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator=(const StaticVector& rhs)
    {
        m_vector = rhs.m_vector;

        return *this;
    }

    template<class Type, size_t Size, bool TF>
    template<class VT> StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator=(const Vector<VT, TF>& rhs)
    {
        TB_ASSERT((~rhs).size() == N, "Input vector has the wrong size");

        const auto& rhsVec = ~rhs;
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] = rhsVec[i];

        return *this;
    }
    
    template<class Type, size_t Size, bool TF>
    template<class VT> StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator+=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;
        TB_ASSERT(rhsVec.size() == N, "Input vector has the wrong size");
        
        for (size_t i = 0; i < Size; ++i)
            m_vector[i] += rhsVec[i];

        return *this;
    }
    
    template<class Type, size_t Size, bool TF>
    template<class VT> StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator-=(const Vector<VT, TF>& rhs)
    {

        const auto& rhsVec = ~rhs;
        TB_ASSERT(rhsVec.size() == N, "Input vector has the wrong size");

        for (size_t i = 0; i < Size; ++i)
            m_vector[i] -= rhsVec[i];

        return *this;
    }
    
    template<class Type, size_t Size, bool TF>
    template<class VT> StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator*=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;
        TB_ASSERT(rhsVec.size() == N, "Input vector has the wrong size");

        for (size_t i = 0; i < Size; ++i)
            m_vector[i] *= rhsVec[i];

        return *this;
    }
    
    template<class Type, size_t Size, bool TF>
    template<class VT> StaticVector<Type, Size, TF>& StaticVector<Type, Size, TF>::operator/=(const Vector<VT, TF>& rhs)
    {
        const auto& rhsVec = ~rhs;
        TB_ASSERT(rhsVec.size() == N, "Input vector has the wrong size");

        for (size_t i = 0; i < Size; ++i)
            m_vector[i] /= rhsVec[i];

        return *this;
    }

    template<class Type, size_t Size, bool TF>
    template<class VT>
    inline bool StaticVector<Type, Size, TF>::operator==(const Vector<VT, TF>& rhs) const
    {
        const auto& rhsVec = ~rhs;

        if (rhsVec.size() != size())
            return false;

        for (size_t i = 0; i < Size; ++i)
        {
            if (m_vector[i] != rhsVec[i])
                return false;
        }

        return true;
    }

    template<class Type, size_t Size, bool TF>
    template<class VT>
    inline bool StaticVector<Type, Size, TF>::operator!=(const Vector<VT, TF>& rhs) const
    {
        return !(*this == rhs);
    }


    /* ========== Misc Functions ========== */

    template<class Type, size_t Size, bool TF>
    inline constexpr size_t StaticVector<Type, Size, TF>::size() const noexcept
    {
        return Size;
    }
}
