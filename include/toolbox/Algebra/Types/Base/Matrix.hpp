#pragma once


namespace Toolbox
{
    template<typename MT, bool SO>
    struct Matrix
    {
        using MatrixType = MT;

        static constexpr bool storageOrder = SO;

        constexpr MatrixType& operator~() noexcept
        {
            return *static_cast<MatrixType*>(this);
        }
        
        constexpr const MatrixType& operator~() const noexcept
        {
            return *static_cast<const MatrixType*>(this);
        }
    };
}
