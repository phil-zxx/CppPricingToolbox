#pragma once

#include <toolbox/Algebra/Types/Base/Vector.hpp>
#include <toolbox/Algebra/Types/Base/Matrix.hpp>
#include <type_traits>


namespace Toolbox
{
    /* ========== remove_cv_ref ========== */
    template<class T>
    using remove_cv_ref_t = typename std::remove_cv_t<typename std::remove_reference_t<T>>;


    /* ========== is_boolean ========== */
    template<class T>
    constexpr bool is_boolean_v = std::is_same_v<bool, remove_cv_ref_t<T>>;


    /* ========== is_expression ========== */
    struct Expression { };

    template<class T>
    constexpr bool is_expression_v = std::is_base_of_v<Expression, remove_cv_ref_t<T>>;


    /* ========== is_instance_of_v ========== */
    template <class T, template <class...> class Template>
    constexpr bool is_instance_of_v = false;

    template <template <class...> class Template, class... Args>
    constexpr bool is_instance_of_v<Template<Args...>, Template> = true;


    /* ========== is_vector ========== */
    template <class T>
    struct is_vector
    {
        using Tclean = typename remove_cv_ref_t<T>;

        template <class VT, bool TF>
        static std::true_type test(Vector<VT, TF>*);

        static std::false_type test(void*);

        constexpr static bool value = decltype(test(std::declval<Tclean*>()))::value;
    };

    template <class T>
    constexpr bool is_vector_v = is_vector<T>::value;


    /* ========== is_matrix ========== */
    template <class T>
    struct is_matrix
    {
        using Tclean = typename remove_cv_ref_t<T>;

        template <class MT, bool SO>
        static std::true_type test(Matrix<MT, SO>*);

        static std::false_type test(void*);

        constexpr static bool value = decltype(test(std::declval<Tclean*>()))::value;
    };

    template <class T>
    constexpr bool is_matrix_v = is_matrix<T>::value;


    /* ========== is_scalar ========== */
    template<class T>
    constexpr bool is_scalar_v = std::is_arithmetic_v<T> && !is_boolean_v<T>;


    /* ========== is_vector_or_scalar ========== */
    template <class T>
    constexpr bool is_vector_or_scalar_v = is_vector_v<T> || is_scalar_v<T>;


    /* ========== is_binary_op_valid & is_unary_op_valid ========== */
    template <class LHS, class RHS>
    constexpr bool is_binary_op_valid_v = is_vector_or_scalar_v<LHS> || is_vector_or_scalar_v<RHS>;
    
    template <class RHS>
    constexpr bool is_unary_op_valid_v = is_vector_v<RHS>;
    

    /* ========== has_storage ========== */
    template<class, class = void>
    struct has_storage : std::false_type { };

    template<class T>
    struct has_storage<T, std::void_t<decltype(T::m_storage)>> : std::true_type { };

    template<class T>
    constexpr bool has_storage_v = has_storage<T>::value;
}
