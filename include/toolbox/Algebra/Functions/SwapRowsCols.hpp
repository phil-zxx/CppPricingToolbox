#pragma once

#include <toolbox/Core/Error.hpp>
#include <toolbox/Algebra/Typetraits/IsHasFunctions.hpp>


namespace Toolbox
{
    template<class MT, class = std::enable_if_t<is_mutable_matrix_v<MT>>>
    void swapRows(MT& arg, const size_t& rowIdx1, const size_t& rowIdx2)
    {
        TB_ENSURE(rowIdx1 < arg.rowCount() && rowIdx2 < arg.rowCount(), "Need row indices (" << rowIdx1 << ", " << rowIdx2 << ") to be swapped to be less than the total row count (" << arg.rowCount() << ")");

        if (rowIdx1 == rowIdx2)
            return;

        for (size_t ci = 0, size = arg.colCount(); ci < size; ++ci)
        {
            const auto temp  = arg(rowIdx1, ci);
            arg(rowIdx1, ci) = arg(rowIdx2, ci);
            arg(rowIdx2, ci) = temp;
        }
    }

    template<class MT, class = std::enable_if_t<is_mutable_matrix_v<MT>>>
    void swapColumns(MT& arg, const size_t& colIdx1, const size_t& colIdx2)
    {
        TB_ENSURE(colIdx1 < arg.colCount() && colIdx2 < arg.colCount(), "Need column indices (" << colIdx1 << ", " << colIdx2 << ") to be swapped to be less than the total column count (" << arg.colCount() << ")");

        if (colIdx1 == colIdx2)
            return;

        for (size_t ri = 0, size = arg.rowCount(); ri < size; ++ri)
        {
            const auto temp  = arg(ri, colIdx1);
            arg(ri, colIdx1) = arg(ri, colIdx2);
            arg(ri, colIdx2) = temp;
        }
    }
}
