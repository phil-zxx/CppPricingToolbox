#pragma once

#include <sstream>


namespace Toolbox
{
    class MatrixShape
    {
    public:
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

        friend std::ostream& operator<<(std::ostream& os, const MatrixShape& rhs)
        {
            return os << rhs.rows << "x" << rhs.cols;
        }

        size_t rows, cols;
    };
}
