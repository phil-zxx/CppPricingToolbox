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
    };
}
