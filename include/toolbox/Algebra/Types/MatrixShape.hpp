#pragma once


namespace Toolbox
{
    class MatrixShape
    {
    public:
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

        size_t rows, cols;
    };
}
