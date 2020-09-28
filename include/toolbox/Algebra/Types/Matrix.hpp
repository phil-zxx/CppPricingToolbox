#pragma once

#include <sstream>
#include <iomanip>
#include <cmath>


namespace TB
{
    template<class MT>
    struct Matrix
    {
        using MatrixType = MT;

        constexpr MatrixType& operator~() noexcept
        {
            return static_cast<MatrixType&>(*this);
        }

        constexpr const MatrixType& operator~() const noexcept
        {
            return static_cast<const MatrixType&>(*this);
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<MT>& rhs)
        {
            os << "[";
            for (size_t iRow = 0, rowCount = (~rhs).rowCount(); iRow < rowCount; ++iRow)
            {
                os << (iRow == 0 ? "[" : " [");
                for (size_t iCol = 0, colCount = (~rhs).colCount(); iCol < colCount; ++iCol)
                {
                    const double val = (~rhs)(iRow, iCol);
                    if (std::abs(val) < 1.e-8)
                        os << std::setw(11) << ".";
                    else
                        os << std::setw(11) << std::setprecision(6) << val;
                    os << " ";
                }
                os << "]" << (iRow + 1 < rowCount ? ",\n" : "");
            }
            return os << "]";
        }

        std::string toString() const
        {
            std::ostringstream os;
            os << *this;
            return os.str();
        }
    };
}
