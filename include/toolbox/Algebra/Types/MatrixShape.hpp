#pragma once

#include <toolbox/Core/Error.hpp>


namespace Toolbox
{
    struct MatrixShape
    {
        constexpr explicit MatrixShape(const MatrixShape& shape) noexcept
            : rows(shape.rows), cols(shape.cols) { }

        constexpr explicit MatrixShape(size_t rows, size_t cols) noexcept
            : rows(rows), cols(cols) { }

        constexpr bool operator==(const MatrixShape& rhs) const
        {
            return this->rows == rhs.rows && this->cols == rhs.cols;
        }

        constexpr bool operator!=(const MatrixShape& rhs) const
        {
            return this->rows != rhs.rows || this->cols != rhs.cols;
        }

        MatrixShape transposed() const
        {
            return MatrixShape(cols, rows);
        }

        friend ErrorOS& operator<<(ErrorOS& os, const MatrixShape& msg)
        {
            return os << msg.rows << "x" << msg.cols;
        }

        size_t rows, cols;
    };
}
