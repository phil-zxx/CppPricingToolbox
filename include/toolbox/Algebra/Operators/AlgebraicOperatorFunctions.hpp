#pragma once

#include <toolbox/Algebra/Operators/Expressions/SumExprBinary.hpp>
#include <toolbox/Algebra/Operators/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Operators/Expressions/MatrixExprTrans.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorClasses.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) trans(const MT& arg)
    {
        constexpr bool SO = !matrix_storage_order_flag_v<MT>;
        return MatrixExprTrans<OperatorId<>, MT, SO>(arg);
    }

    template<class T, class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) asType(const MT& arg)
    {
        constexpr bool SO = matrix_storage_order_flag_v<MT>;
        return MatrixExprUnary<OperatorId<T>, MT, SO>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) abs(const MT& arg)
    {
        constexpr bool SO = matrix_storage_order_flag_v<MT>;
        return MatrixExprUnary<OperatorAbs, MT, SO>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) min(const MT& arg)
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
    decltype(auto) max(const MT& arg)
    {
        return -(min(-arg));
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

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    auto sum(const MT& arg)
    {
        using ElementType = ElementType_t<MT>;

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
        using ElementType = ElementType_t<MT>;

        if (arg.size() == 0)
            return ElementType(1);

        ElementType product = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            product *= arg[i];

        return product;
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) dot(const MT1& lhs, const MT2& rhs)
    {
        return SumExprBinary<OperatorMul, MT1, MT2>::evaluate(lhs, rhs);
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) innerProduct(const MT1& lhs, const MT2& rhs)
    {
        if (lhs.rowCount() != 1 || rhs.colCount() != 1 || lhs.colCount() != rhs.rowCount())
            throw("Inner-product requires LHS matrix to be a row vector (1 x M) and RHS matrix to be a column vector (M x 1)");

        return dot(lhs, rhs);
    }
}
