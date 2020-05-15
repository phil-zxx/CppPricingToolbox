#pragma once

#include <toolbox/Algebra/Operators/Expressions/SumExprBinary.hpp>
#include <toolbox/Algebra/Operators/Expressions/MatrixExpr.hpp>
#include <toolbox/Algebra/Operators/BasicOperatorClasses.hpp>


namespace Toolbox
{
    template<class VMT, class = std::enable_if_t<is_unary_op_valid_v<VMT>>>
    constexpr decltype(auto) trans(const VMT& arg)
    {
        if constexpr (is_vector_v<VMT>)
        {
            constexpr bool TF = !vector_transpose_flag_v<VMT>;
            return VectorExprUnary<OperatorId<>, VMT, TF>(arg);
        }
        else if constexpr (is_matrix_v<VMT>)
        {
            constexpr bool SO = !matrix_storage_order_flag_v<VMT>;
            return MatrixExprUnary<OperatorId<>, VMT, SO>(arg);
        }
    }

    template<class T, class VT, class = std::enable_if_t<is_vector_v<VT>>>
    decltype(auto) asType(const VT& arg)
    {
        constexpr bool TF = vector_transpose_flag_v<VT>;
        return VectorExprUnary<OperatorId<T>, VT, TF>(arg);
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    decltype(auto) abs(const VT& arg)
    {
        constexpr bool TF = vector_transpose_flag_v<VT>;
        return VectorExprUnary<OperatorAbs, VT, TF>(arg);
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    decltype(auto) min(const VT& arg)
    {
        if (arg.size() == 0)
            throw("Cannot use min function on an empty vector");

        auto min = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < min)
                min = arg[i];
        }

        return min;
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    decltype(auto) max(const VT& arg)
    {
        return -(min(-arg));
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    size_t argMin(const VT& arg)
    {
        if (arg.size() == 0)
            throw("Cannot use min function on an empty vector");

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

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    size_t argMax(const VT& arg)
    {
        return argMin(-arg);
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    auto sum(const VT& arg)
    {
        using ElementType = ElementType_t<VT>;

        if (arg.size() == 0)
            return ElementType(0);

        ElementType sum = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            sum += arg[i];

        return sum;
    }

    template<class VT, class = std::enable_if_t<is_vector_v<VT>>>
    auto prod(const VT& arg)
    {
        using ElementType = ElementType_t<VT>;

        if (arg.size() == 0)
            return ElementType(1);

        ElementType product = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            product *= arg[i];

        return product;
    }

    template<class VT1, class VT2, class = std::enable_if_t<is_vector_v<VT1> && is_vector_v<VT2>>>
    decltype(auto) dot(const VT1& lhs, const VT2& rhs)
    {
        return SumExprBinary<OperatorMul, VT1, VT2>::evaluate(lhs, rhs);
    }

    template<class VT1, class VT2, class = std::enable_if_t<is_vector_v<VT1> && is_vector_v<VT2>>>
    decltype(auto) innerProduct(const VT1& lhs, const VT2& rhs)
    {
        constexpr bool TF1 = vector_transpose_flag_v<VT1>;
        constexpr bool TF2 = vector_transpose_flag_v<VT2>;
        static_assert(TF1 == true,  "Inner-product requires LHS vector to be transposed (= row vector)");
        static_assert(TF2 == false, "Inner-product requires RHS vector to not be transposed (= column vector)");

        return dot(lhs, rhs);
    }
}
