#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) minEl(const MT& arg)
    {
        if (arg.size() == 0)
            throw("Cannot use min function on an empty matrix");

        auto min = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < min)
                min = arg[i];
        }

        return min;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) maxEl(const MT& arg)
    {
        return -(minEl(-arg));
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMin(const MT& arg)
    {
        if (arg.size() == 0)
            throw("Cannot use argMin function on an empty matrix");

        auto min   = arg[0];
        size_t idx = 0;

        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < min)
            {
                min = arg[i];
                idx = i;
            }
        }

        return idx;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMax(const MT& arg)
    {
        return argMin(-arg);
    }
}
