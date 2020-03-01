#pragma once


namespace Toolbox
{
    class StorageShape
    {
    public:
        constexpr explicit StorageShape() noexcept
            : m_rows(0), m_cols(0) { }

        constexpr explicit StorageShape(size_t rows, size_t cols) noexcept
            : m_rows(rows), m_cols(cols) { }

        constexpr size_t rowCount() const
        {
            return m_rows;
        }

        constexpr size_t colCount() const
        {
            return m_cols;
        }

    protected:
        size_t m_rows, m_cols;
    };
}
