#pragma once

#include <sstream>


namespace Toolbox
{
    template<class VT, bool TF>
    struct Vector
    {
        using VectorType = VT;

        static constexpr bool transposeFlag = TF;

        constexpr VectorType& operator~() noexcept
        {
            return static_cast<VectorType&>(*this);
        }
        
        constexpr const VectorType& operator~() const noexcept
        {
            return static_cast<const VectorType&>(*this);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector<VT, TF>& rhs)
        {
            os << "{";
        
            const auto& vector = ~rhs;
            for (size_t i = 0, size = vector.size(); i < size; ++i)
                os << vector[i] << (i + 1 < size ? "," : "");
        
            return os << "}";
        }

        std::string toString() const
        {
            std::ostringstream os;
            os << *this;
            return os.str();
        }
    };
}
