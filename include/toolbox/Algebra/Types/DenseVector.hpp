#pragma once

#include <toolbox/Algebra/Types/DenseMatrix.hpp>


namespace Toolbox
{
    template<class Type, size_t Size, bool TF>
    class DenseVector : public DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>, TF>
    {
        using BaseType = DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>, TF>;

    public:
        constexpr explicit DenseVector() noexcept
            : BaseType() { }

        constexpr explicit DenseVector(size_t size)
            : BaseType(TF ? 1 : size, TF ? size : 1) { }

        constexpr explicit DenseVector(size_t size, Type init)
            : BaseType(TF ? 1 : size, TF ? size : 1, init) { }

        DenseVector(std::initializer_list<Type> list)
            : BaseType(TF ? 1 : list.size(), TF ? list.size() : 1)
        {
            std::copy(list.begin(), list.end(), this->m_data);
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        constexpr DenseVector(const MT& rhs)
            : BaseType(rhs.rowCount(), rhs.colCount())
        {
            if (rhs.rowCount() != 1 && rhs.colCount() != 1)
                throw("DenseVector constructor can only take matrix objects which have vector shape (rows=1 or cols=1)");

            this->copyFrom(rhs);
        }
    };
}
