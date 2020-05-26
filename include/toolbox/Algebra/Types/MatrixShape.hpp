#pragma once


namespace Toolbox
{
    class MatrixShape
    {
    public:
        constexpr explicit MatrixShape(size_t rows, size_t cols) noexcept
            : rows(rows), cols(cols) { }

        constexpr bool operator==(const MatrixShape& rhs)
        {
            return this->rows == rhs.rows && this->cols == rhs.cols;
        }

        constexpr bool operator!=(const MatrixShape& rhs)
        {
            return this->rows != rhs.rows || this->cols != rhs.cols;
        }

        size_t rows, cols;
    };
}
