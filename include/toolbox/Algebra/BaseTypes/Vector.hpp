#pragma once

#include <sstream>


namespace Toolbox
{
    /*
       Vector base class (abstraction from the actual vector type, but enables 
       a conversion back to it via the 'Curiously Recurring Template Pattern' (CRTP)

       VT = Actual Vector Type/Class
       TF = Transposed Flag (false = column vector, true = row vector)
    */
    template<class VT, bool TF>
    struct Vector
    {
        static constexpr bool transposeFlag = TF;

        constexpr VT& operator~() noexcept;
        constexpr const VT& operator~() const noexcept;

        template<class VT_, bool TF_>
        friend std::ostream& operator<<(std::ostream& os, const Vector<VT_, TF_>& rhs);

        std::string toString() const;
    };

    // Inline Definitions
        
    template<class VT, bool TF>
    inline constexpr VT& Vector<VT, TF>::operator~() noexcept
    {
        return static_cast<VT&>(*this);
    }

    template<class VT, bool TF>
    inline constexpr const VT& Vector<VT, TF>::operator~() const noexcept
    {
        return static_cast<const VT&>(*this);
    }

    template<class VT, bool TF>
    inline std::ostream& operator<<(std::ostream& os, const Vector<VT, TF>& rhs)
    {
        const auto& vector = ~rhs;

        os << "{";

        for (size_t i = 0, size = vector.size(); i < size; ++i)
            os << vector[i] << (i + 1 < size ? "," : "");

        return os << "}";
    }
    
    template<class VT, bool TF>
    inline std::string Vector<VT, TF>::toString() const
    {
        std::ostringstream os;
        os << *this;
        return os.str();
    }
}