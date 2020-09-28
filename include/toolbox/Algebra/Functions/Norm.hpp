#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Functions/Expr/Algebraic.hpp>
#include <toolbox/Algebra/Functions/DotInnerProduct.hpp>
#include <toolbox/Algebra/Functions/MinMax.hpp>
#include <toolbox/Algebra/Misc/Maths.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    double norm2(const MT& arg)
    {
        return std::sqrt(dot(arg, arg));
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    double norm(const MT& arg, const double& order)
    {
        if (order == TB_INF_NEG)
        {
            return minEl(abs(arg));
        }
        else if (order == TB_INF_POS)
        {
            return maxEl(abs(arg));
        }
        else if (order == 2.0)
        {
            return norm2(arg);
        }
        else
        {
            double absSum = 0;
            for (size_t i = 0, size = arg.size(); i < size; ++i)
                absSum += std::pow(std::abs(arg[i]), order);

            return std::pow(absSum, 1. / order);
        }
    }
}
