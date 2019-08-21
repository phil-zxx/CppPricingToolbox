#pragma once

#include <toolbox/Algebra/BaseTypes/Vector.hpp>
#include <toolbox/Algebra/BaseTypes/IsIfTemplates.hpp>
#include <toolbox/Algebra/Expressions/ExprVecMap.hpp>
#include <toolbox/Algebra/Operations/OperationClassesUnary.hpp>
#include <toolbox/Algebra/Operations/OperationClassesBinary.hpp>


namespace Toolbox
{
    /* ========== Vector-Scalar Operations ==========*/

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator+(const Vector<VT, TF>& vector, ST scalar);
    
    template<class ST, class VT, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator+(ST scalar, const Vector<VT, TF>& vector);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator-(const Vector<VT, TF>& vector, ST scalar);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator-(ST scalar, const Vector<VT, TF> & vector);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator*(const Vector<VT, TF>& vector, ST scalar);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator*(ST scalar, const Vector<VT, TF>& vector);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator/(const Vector<VT, TF>& vector, ST scalar);
    
    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>* = nullptr>
    constexpr decltype(auto) operator/(ST scalar, const Vector<VT, TF> & vector);
    
    
    /* ========== Vector-Vector Operations ==========*/

    template<class VT1, class VT2, bool TF>
    constexpr decltype(auto) operator+(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs);

    template<class VT1, class VT2, bool TF>
    constexpr decltype(auto) operator-(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs);

    template<class VT1, class VT2, bool TF>
    constexpr decltype(auto) operator*(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs);

    template<class VT1, class VT2, bool TF>
    constexpr decltype(auto) operator/(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs);

    
    /* ========== Single Vector Operations ==========*/

    template<class VT, bool TF>
    constexpr decltype(auto) operator-(const Vector<VT, TF>& vector);


    // Inline Definitions

    /* ========== Vec-Scalar Operations ==========*/

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator+(const Vector<VT, TF>& vector, ST scalar)
    {
        return ExprVecMap(vector, OperationUnaryAdd(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator+(ST scalar, const Vector<VT, TF>& vector)
    {
        return ExprVecMap(vector, OperationUnaryAdd(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator-(const Vector<VT, TF>& vector, ST scalar)
    {
        return ExprVecMap(vector, OperationUnarySubLhs(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator-(ST scalar, const Vector<VT, TF>& vector)
    {
        return ExprVecMap(vector, OperationUnarySubRhs(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator*(const Vector<VT, TF>& vector, ST scalar)
    {
        return ExprVecMap(vector, OperationUnaryMul(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator*(ST scalar, const Vector<VT, TF>& vector)
    {
        return ExprVecMap(vector, OperationUnaryMul(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator/(const Vector<VT, TF>& vector, ST scalar)
    {
        return ExprVecMap(vector, OperationUnaryDivLhs(scalar));
    }

    template<class VT, class ST, bool TF, EnableIf_t<IsNumeric_v<ST>>*>
    inline constexpr decltype(auto) operator/(ST scalar, const Vector<VT, TF>& vector)
    {
        return ExprVecMap(vector, OperationUnaryDivRhs(scalar));
    }


    /* ========== Vector-Vector Operations ==========*/

    template<class VT1, class VT2, bool TF>
    inline constexpr decltype(auto) operator+(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs)
    {
        TB_ASSERT((~lhs).size() == (~rhs).size(), "Need input vectors to have the same size");

        return ExprVecVecMap(lhs, rhs, OperationBinaryAdd{});
    }

    template<class VT1, class VT2, bool TF>
    inline constexpr decltype(auto) operator-(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs)
    {
        TB_ASSERT((~lhs).size() == (~rhs).size(), "Need input vectors to have the same size");

        return ExprVecVecMap(lhs, rhs, OperationBinarySub{});
    }

    template<class VT1, class VT2, bool TF>
    inline constexpr decltype(auto) operator*(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs)
    {
        TB_ASSERT((~lhs).size() == (~rhs).size(), "Need input vectors to have the same size");

        return ExprVecVecMap(lhs, rhs, OperationBinaryMul{});
    }

    template<class VT1, class VT2, bool TF>
    inline constexpr decltype(auto) operator/(const Vector<VT1, TF>& lhs, const Vector<VT2, TF>& rhs)
    {
        TB_ASSERT((~lhs).size() == (~rhs).size(), "Need input vectors to have the same size");

        return ExprVecVecMap(lhs, rhs, OperationBinaryDiv{});
    }


    /* ========== Single Vector Operations ==========*/

    template<class VT, bool TF>
    inline constexpr decltype(auto) operator-(const Vector<VT, TF>& vector)
    {
        using ScalarType = const VT::ElementType;
        return ExprVecMap(vector, OperationUnaryMul(ScalarType(-1)));
    }
}
