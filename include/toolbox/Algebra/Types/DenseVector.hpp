#pragma once

#include <toolbox/Algebra/Types/DenseMatrix.hpp>
#include <toolbox/Core/Error.hpp>

#include <vector>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF>
    class DenseVector : public DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>>
    {
        using BaseType = DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>>;

    public:
        constexpr explicit DenseVector() noexcept
            : BaseType() { }

        constexpr explicit DenseVector(size_t size)
            : BaseType(TF ? 1 : size, TF ? size : 1) { }

        constexpr explicit DenseVector(size_t size, Type init)
            : BaseType(TF ? 1 : size, TF ? size : 1, init) { }

        DenseVector(const std::vector<Type>& vec)
            : BaseType(TF ? 1 : vec.size(), TF ? vec.size() : 1)
        {
            std::copy(vec.begin(), vec.end(), this->data());
        }

        DenseVector(std::initializer_list<Type> list)
            : BaseType(TF ? 1 : list.size(), TF ? list.size() : 1)
        {
            std::copy(list.begin(), list.end(), this->data());
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        constexpr DenseVector(const MT& rhs)
            : BaseType(rhs.rowCount(), rhs.colCount())
        {
            TB_ENSURE(rhs.rowCount() == 1 || rhs.colCount() == 1, "DenseVector constructor can only take matrix objects which have vector shape (rows=1 or cols=1)");

            this->copyFrom(rhs);
        }

        operator std::vector<Type>() const
        {
            return std::vector<Type>(this->begin(), this->end());
        }
    };
}
