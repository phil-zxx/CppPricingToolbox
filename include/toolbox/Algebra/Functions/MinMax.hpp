#pragma once

#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) minEl(const MT& arg)
    {
        if (arg.size() == 0)
            throw("Cannot use min function on an empty matrix");

        auto minElTemp = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < minElTemp)
                minElTemp = arg[i];
        }

        return minElTemp;
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

        auto minElTemp = arg[0];
        size_t minIdx  = 0;

        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < minElTemp)
            {
                minElTemp = arg[i];
                minIdx    = i;
            }
        }

        return minIdx;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMax(const MT& arg)
    {
        return argMin(-arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMaxFrom(const MT& arg, const size_t& offset)
    {
        if (arg.size() <= offset)
            throw("Cannot use argMaxFrom function on an empty matrix");

        auto maxElTemp = arg[offset];
        size_t maxIdx  = offset;

        for (size_t i = 1 + offset, size = arg.size(); i < size; ++i)
        {
            if (arg[i] > maxElTemp)
            {
                maxElTemp = arg[i];
                maxIdx    = i;
            }
        }

        return maxIdx;
    }
}
