#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace TB
{
    /*
        ElementType_t<T> will recursively unravel T::ElementType::...::ElementType
        in order to get to the root ElementType. In other words:

        If type T has a sub-typename ElementType
            use ElementType_t<T::ElementType>
        else
            use T itself (in which case T should be a scalar type)
    */

    /* ========== ElementType ========== */
    template<class T, class = void>
    struct ElementTypeImpl
    {
        using type = T;
        static_assert(is_scalar_v<T> || std::is_same_v<T, void*>, "Need the root operator input type to be a scalar (or void*)");
    };

    template<class T>
    struct ElementTypeImpl<T, std::void_t<typename T::ElementType>>
    {
        using type = typename ElementTypeImpl<typename T::ElementType>::type;
    };

    template<class T>
    using ElementType_t = typename ElementTypeImpl<T>::type;
}
