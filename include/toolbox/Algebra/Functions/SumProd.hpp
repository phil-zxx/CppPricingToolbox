#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    auto sum(const MT& arg)
    {
        using ElementType = typename MT::ElementType;

        if (arg.size() == 0)
            return ElementType(0);

        ElementType sum = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            sum += arg[i];

        return sum;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    auto prod(const MT& arg)
    {
        using ElementType = typename MT::ElementType;

        if (arg.size() == 0)
            return ElementType(1);

        ElementType product = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            product *= arg[i];

        return product;
    }
}
