#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) minEl(const MT& arg)
    {
        TB_ENSURE(arg.size() > 0, "Cannot use min function on an empty matrix");

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
        TB_ENSURE(arg.size() > 0, "Cannot use argMin function on an empty matrix");

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
        TB_ENSURE(arg.size() > offset, "Need matrix size (" << arg.size() << ") to be larger than the offset (" << offset << ") in argMaxFrom function");

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
