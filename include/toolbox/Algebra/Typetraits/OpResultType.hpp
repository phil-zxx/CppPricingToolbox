#pragma once

#include <toolbox/Algebra/Typetraits/ElementType.hpp>


namespace Toolbox
{
    /* ========== OpResultType ========== */
    template<class OP, class LHS, class RHS>
    struct OpResultType
    {
        using type = decltype(OP{}(std::declval<ElementType_t<LHS>>(), std::declval<ElementType_t<RHS>>()));
    };

    template<class OP, class ARG>
    struct OpResultType<OP, ARG, void*>
    {
        using type = decltype(OP{}(std::declval<ElementType_t<ARG>>()));
    };

    template<class OP, class LHS, class RHS = void*>
    using OpResultType_t = typename OpResultType<OP, LHS, RHS>::type;
}
