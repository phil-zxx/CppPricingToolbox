#pragma once

#include <type_traits>


namespace Toolbox
{
    /* ========== OpResultType ========== */
    template<class OP, class LHS, class RHS>
    struct OpResultType
    {
        using type = decltype(OP{}(std::declval<LHS>(), std::declval<RHS>()));
    };

    template<class OP, class ARG>
    struct OpResultType<OP, ARG, void*>
    {
        using type = decltype(OP{}(std::declval<ARG>()));
    };

    template<class OP, class LHS, class RHS>
    using OpResultType_t = typename OpResultType<OP, LHS, RHS>::type;
}
