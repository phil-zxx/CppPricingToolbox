#pragma once
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include <cassert>
#include <string>
#include <vector>
#include <limits>

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

namespace TB
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

    /* ========== is_matrix ========== */
    template <class T>
    struct is_matrix
    {
        using Tclean = remove_cv_ref_t<T>;

        template <class MT>
        static std::true_type test(Matrix<MT>*);

        static std::false_type test(void*);

        constexpr static bool value = decltype(test(std::declval<Tclean*>()))::value;
    };

    template <class T>
    constexpr bool is_matrix_v = is_matrix<T>::value;

    /* ========== is_scalar ========== */
    template<class T>
    constexpr bool is_scalar_v = std::is_arithmetic_v<T> && !is_boolean_v<T>;

    /* ========== is_expression_or_scalar ========== */
    template <class T>
    constexpr bool is_expression_or_scalar_v = is_expression_v<T> || is_scalar_v<T>;

    /* ========== at_least_one_is_matrix ========== */
    template <class LHS, class RHS>
    constexpr bool at_least_one_is_matrix_v = is_matrix_v<LHS> || is_matrix_v<RHS>;

    /* ========== has_storage ========== */
    template<class, class = void>
    struct has_storage : std::false_type { };

    template<class T>
    struct has_storage<T, std::void_t<decltype(T::m_storage)>> : std::true_type { };

    template<class T>
    constexpr bool has_storage_v = has_storage<T>::value;

    /* ========== is_mutable_matrix ========== */
    template<class T>
    constexpr bool is_mutable_matrix_v = !std::is_const_v<T> && !is_expression_v<T> && !is_scalar_v<T>;

    /* ========== if ========== */
    template<bool Test, class T, T val1, T val2>
    constexpr T if_v = std::conditional_t<Test, std::integral_constant<T, val1>, std::integral_constant<T, val2>>::value;
}

namespace TB
{
    struct ErrorOS
    {
        ErrorOS() = default;

        template<class T>
        ErrorOS& operator<<(const T i)
        {
            m_str.append(std::to_string(i));
            return *this;
        }

        ErrorOS& operator<<(const char* msg)
        {
            m_str.append(msg);
            return *this;
        }

        operator std::string() const
        {
            return m_str;
        }

        std::string m_str;
    };
}

#ifdef NDEBUG
    #define TB_ASSERT(expr, msg)
#else
    #define TB_ASSERT(expr, msg) assert((expr) || !msg)
#endif

#define TB_ENSURE(condition, message) \
    if (!(condition)) { \
        throw std::runtime_error(TB::ErrorOS() << "Error: " << __func__ << ":\n  " << __FILE__ << "(" << __LINE__ << "): \n" << message); \
     } else

#define TB_THROW(message) TB_ENSURE(false, message)

namespace TB
{
    struct MatrixShape
    {
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

namespace TB
{
    constexpr size_t DynamicSize = static_cast<size_t>(-1);

    template<class Type, size_t R, size_t C>
    class DenseMatrix : public Matrix<DenseMatrix<Type, R, C>>
    {
        static_assert(!((R == DynamicSize) ^ (C == DynamicSize)), "Matrix Dimensions R & C must be either fully dynamic or fully static");
        static_assert(R > 0 && C > 0, "Matrix Dimensions R & C must be greater than 0");
        constexpr static size_t internalSize = std::conditional_t<R != DynamicSize && C != DynamicSize, std::integral_constant<size_t, R * C>, std::integral_constant<size_t, DynamicSize>>::value;

    public:
        constexpr static bool hasDynamicSize = (internalSize == DynamicSize);

        using ElementType = Type;
        using DataType    = typename std::conditional_t<hasDynamicSize, Type*, Type[hasDynamicSize ? 1 : internalSize]>;

        constexpr explicit DenseMatrix() noexcept
            : m_shape(0, 0), m_size(0), m_capacity(0), m_data()
        {
            if constexpr (!hasDynamicSize)
                m_capacity = internalSize;
        }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount)
            : DenseMatrix(rowCount, colCount, 0) { }

        constexpr explicit DenseMatrix(const MatrixShape& shape)
            : DenseMatrix(shape.rows, shape.cols, 0) { }

        constexpr explicit DenseMatrix(size_t rowCount, size_t colCount, Type init)
            : DenseMatrix()
        {
            this->allocate(rowCount, colCount);
            for (size_t i = 0; i < size(); ++i)
                m_data[i] = init;
        }

        constexpr DenseMatrix(std::initializer_list<std::initializer_list<Type>> matrix)
            : DenseMatrix()
        {
            this->allocate(matrix.size(), matrix.size() > 0 ? matrix.begin()->size() : 0);

            size_t i = 0;
            for (const auto& row : matrix)
            {
                TB_ENSURE(row.size() == m_shape.cols, "Input matrix has rows of varying sizes (found " << row.size() << " and " << m_shape.cols << ")");

                for (const auto& element : row)
                {
                    m_data[i] = element;
                    ++i;
                }
            }
        }

        template<class MT>
        constexpr DenseMatrix(const Matrix<MT>& rhs)
            : DenseMatrix((~rhs).rowCount(), (~rhs).colCount())
        {
            this->copyFrom(~rhs);
        }

        DenseMatrix(const DenseMatrix& rhs) noexcept
            : DenseMatrix()
        {
            this->copyFrom(rhs);
        }

        DenseMatrix(DenseMatrix&& rhs) noexcept
            : DenseMatrix()
        {
            this->moveFrom(std::move(rhs));
        }

        void operator=(const DenseMatrix& rhs) noexcept
        {
            this->copyFrom(rhs);
        }

        template<class Type2, size_t R2, size_t C2>
        void operator=(const DenseMatrix<Type2, R2, C2>& rhs) noexcept
        {
            this->copyFrom(rhs);
        }

        void operator=(DenseMatrix&& rhs) noexcept
        {
            this->moveFrom(std::move(rhs));
        }

        constexpr const ElementType& operator[](size_t idx) const
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr ElementType& operator[](size_t idx)
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr const ElementType& at(size_t idx) const
        {
            TB_ENSURE(idx < size(), "Index (" << idx << ") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr ElementType& at(size_t idx)
        {
            TB_ENSURE(idx < size(), "Index (" << idx <<") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr const ElementType& operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        constexpr ElementType& operator()(size_t rowIdx, size_t colIdx)
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        void operator+=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs[i];
        }

        void operator+=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs;
        }

        void operator-=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply -= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs[i];
        }

        void operator-=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs;
        }

        void operator*=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply *= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs[i];
        }

        void operator*=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs;
        }

        void operator/=(const DenseMatrix& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply /= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs[i];
        }

        void operator/=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs;
        }

        constexpr const MatrixShape& shape() const
        {
            return m_shape;
        }

        constexpr size_t rowCount() const
        {
            return m_shape.rows;
        }

        constexpr size_t colCount() const
        {
            return m_shape.cols;
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr size_t capacity() const
        {
            return m_capacity;
        }

        const Type* data() const
        {
            return m_data;
        }

        Type* data()
        {
            return m_data;
        }

        const Type* begin() const
        {
            return m_data;
        }

        const Type* end() const
        {
            return m_data + size();
        }

        Type* begin()
        {
            return m_data;
        }

        Type* end()
        {
            return m_data + size();
        }

        ~DenseMatrix()
        {
            deallocate();
        }

        template<class Type2, size_t R2, size_t C2>
        constexpr void copyFrom(const DenseMatrix<Type2, R2, C2>& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            std::copy(rhs.data(), rhs.data() + rhs.size(), this->m_data);
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        constexpr void copyFrom(const MT& rhs)
        {
            this->allocate(rhs.rowCount(), rhs.colCount());

            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                m_data[i] = rhs[i];
        }

        constexpr void moveFrom(DenseMatrix&& rhs)
        {
            if constexpr (hasDynamicSize)
            {
                this->m_data = rhs.data();
                rhs.m_data   = nullptr;
            }
            else
            {
                std::move(rhs.data(), rhs.data() + rhs.size(), this->m_data);
            }

            this->m_size     = rhs.m_size;
            this->m_capacity = rhs.m_capacity;
            this->m_shape    = rhs.m_shape;

            rhs.m_size       = 0;
            rhs.m_capacity   = 0;
            rhs.m_shape.rows = 0;
            rhs.m_shape.cols = 0;
        }

        static constexpr DenseMatrix Identity(const size_t& size)
        {
            return DenseMatrix::Identity(size, size);
        }

        static constexpr DenseMatrix Identity(const size_t& rowSize, const size_t& colSize)
        {
            DenseMatrix result(rowSize, colSize, 0);
            for (size_t i = 0, size = rowSize < colSize ? rowSize : colSize; i < size; ++i)
                result(i, i) = 1;
            return result;
        }

    private:
        constexpr void allocate(size_t size)
        {
            this->allocate(size, 1);
        }

        constexpr void allocate(size_t rowCount, size_t colCount)
        {
            m_size       = rowCount * colCount;
            m_shape.rows = rowCount;
            m_shape.cols = colCount;

            if constexpr (hasDynamicSize)
            {
                if (m_size > m_capacity)
                {
                    deallocate();
                    m_capacity = m_size;
                    m_data     = new Type[m_capacity];
                }
            }
            else
            {
                TB_ENSURE(m_size       <= m_capacity, "Input size ("        << m_size << " = " << m_shape.rows << "x" << m_shape.cols << ") for static-sized storage cannot be larger than its static capacity (" << m_capacity << ")");
                TB_ENSURE(m_shape.rows <= R,          "Input row count ("   << m_shape.rows << ") for static-sized storage cannot be larger than its static row count (" << R << ")");
                TB_ENSURE(m_shape.cols <= C,          "Input column count(" << m_shape.cols << ") for static-sized storage cannot be larger than its static column count (" << C << ")");
            }
        }

        constexpr void deallocate()
        {
            if constexpr (hasDynamicSize)
            {
                if (m_data != nullptr)
                    delete[] m_data;
            }
        }

        MatrixShape m_shape;
        size_t m_size, m_capacity;
        DataType m_data;
    };
}

namespace TB
{
    template<class Type, size_t Size, bool TF>
    class DenseVector : public DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>>
    {
        using BaseType = DenseMatrix<Type, if_v<Size == DynamicSize, size_t, Size, TF ? 1 : Size>, if_v<Size == DynamicSize, size_t, Size, TF ? Size : 1>>;

    public:
        constexpr explicit DenseVector() noexcept
            : BaseType() { }

        constexpr explicit DenseVector(size_t size)
            : BaseType(TF ? 1 : size, TF ? size : 1) { }

        constexpr explicit DenseVector(size_t size, Type init)
            : BaseType(TF ? 1 : size, TF ? size : 1, init) { }

        DenseVector(const std::vector<Type>& vec)
            : BaseType(TF ? 1 : vec.size(), TF ? vec.size() : 1)
        {
            std::copy(vec.begin(), vec.end(), this->data());
        }

        DenseVector(std::initializer_list<Type> list)
            : BaseType(TF ? 1 : list.size(), TF ? list.size() : 1)
        {
            std::copy(list.begin(), list.end(), this->data());
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        constexpr DenseVector(const MT& rhs)
            : BaseType(rhs.rowCount(), rhs.colCount())
        {
            TB_ENSURE(rhs.rowCount() == 1 || rhs.colCount() == 1, "DenseVector constructor can only take matrix objects which have vector shape (rows=1 or cols=1)");

            this->copyFrom(rhs);
        }

        operator std::vector<Type>() const
        {
            return std::vector<Type>(this->begin(), this->end());
        }
    };
}

namespace TB
{
    template<class Type>
    class CustomMatrix : public Matrix<CustomMatrix<Type>>
    {
    public:
        using ElementType = Type;

        explicit CustomMatrix(size_t rowCount, size_t colCount, Type* externalPtr)
            : m_shape(rowCount, colCount), m_size(rowCount * colCount), m_capacity(rowCount* colCount), m_data(externalPtr) { }

        constexpr const ElementType& operator[](size_t idx) const
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr ElementType& operator[](size_t idx)
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return this->m_data[idx];
        }

        constexpr const ElementType& at(size_t idx) const
        {
            TB_ENSURE(idx < size(), "Index (" << idx << ") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr ElementType& at(size_t idx)
        {
            TB_ENSURE(idx < size(), "Index (" << idx <<") is out of bounds (size is only " << size() << ")");
            return this->m_data[idx];
        }

        constexpr const ElementType& operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        constexpr ElementType& operator()(size_t rowIdx, size_t colIdx)
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return m_data[rowIdx * colCount() + colIdx];
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator+=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply += when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs[i];
        }

        void operator+=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] += rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator-=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply -= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs[i];
        }

        void operator-=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] -= rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator*=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply *= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs[i];
        }

        void operator*=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] *= rhs;
        }

        template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
        void operator/=(const MT& rhs)
        {
            TB_ENSURE(this->shape() == rhs.shape(), "Cannot apply /= when this & rhs have different shapes");

            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs[i];
        }

        void operator/=(const ElementType& rhs)
        {
            for (size_t i = 0, size = this->size(); i < size; ++i)
                m_data[i] /= rhs;
        }

        constexpr const MatrixShape& shape() const
        {
            return m_shape;
        }

        constexpr size_t rowCount() const
        {
            return m_shape.rows;
        }

        constexpr size_t colCount() const
        {
            return m_shape.cols;
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr size_t capacity() const
        {
            return m_capacity;
        }

        const Type* data() const
        {
            return m_data;
        }

        Type* data()
        {
            return m_data;
        }

        const Type* begin() const
        {
            return m_data;
        }

        const Type* end() const
        {
            return m_data + size();
        }

        Type* begin()
        {
            return m_data;
        }

        Type* end()
        {
            return m_data + size();
        }

    private:
        MatrixShape m_shape;
        size_t m_size, m_capacity;
        Type* m_data;
    };
}

namespace TB
{
    template<class Type>
    class IdentityMatrix : public Matrix<IdentityMatrix<Type>>
    {
    public:
        using ElementType = Type;

        constexpr explicit IdentityMatrix(size_t size) noexcept
            : m_shape(size, size) { }

        constexpr explicit IdentityMatrix(size_t rowCount, size_t colCount) noexcept
            : m_shape(rowCount, colCount) { }

        constexpr explicit IdentityMatrix(const MatrixShape& shape) noexcept
            : m_shape(shape) { }

        constexpr ElementType operator[](size_t idx) const
        {
            TB_ASSERT(idx < size(), "Index is out of bounds");
            return idx / m_shape.cols == idx % m_shape.cols ? 1 : 0;
        }

        constexpr ElementType at(size_t idx) const
        {
            TB_ENSURE(idx < size(), "Index (" << idx << ") is out of bounds (size is only " << size() << ")");
            return idx / m_shape.cols == idx % m_shape.cols ? 1 : 0;
        }

        constexpr ElementType operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_shape.rows, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_shape.rows << " rows)");
            TB_ENSURE(colIdx < m_shape.cols, "Column index (" << colIdx << ") is out of bounds (only have " << m_shape.cols << " columns)");

            return rowIdx == colIdx ? 1 : 0;
        }

        constexpr const MatrixShape& shape() const
        {
            return m_shape;
        }

        constexpr size_t rowCount() const
        {
            return m_shape.rows;
        }

        constexpr size_t colCount() const
        {
            return m_shape.cols;
        }

        constexpr size_t size() const
        {
            return m_shape.rows * m_shape.cols;
        }

    private:
        MatrixShape m_shape;
    };
}

namespace TB
{
    /* ========== apply_unary ========== */
    template<class OP, class LHS>
    decltype(auto) apply_unary(const LHS& lhs, size_t idx)
    {
        constexpr OP operation;

        return operation(lhs[idx]);
    }

    template<class OP, class LHS>
    decltype(auto) apply_unary(const LHS& lhs, size_t rowIdx, size_t colIdx)
    {
        constexpr OP operation;

        return operation(lhs(rowIdx, colIdx));
    }

    /* ========== apply_binary ========== */
    template<class OP, class LHS, class RHS>
    decltype(auto) apply_binary(const LHS& lhs, const RHS& rhs, size_t idx)
    {
        constexpr OP operation;

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs[idx], rhs[idx]);
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
            return operation(lhs[idx], rhs);
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs, rhs[idx]);

        static_assert(at_least_one_is_matrix_v<LHS, RHS>, "Need at least one input to be a matrix");
    }

    template<class OP, class LHS, class RHS>
    decltype(auto) apply_binary(const LHS& lhs, const RHS& rhs, size_t rowIdx, size_t colIdx)
    {
        constexpr OP operation;

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs(rowIdx, colIdx), rhs(rowIdx, colIdx));
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
            return operation(lhs(rowIdx, colIdx), rhs);
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
            return operation(lhs, rhs(rowIdx, colIdx));

        static_assert(at_least_one_is_matrix_v<LHS, RHS>, "Need at least one input to be a matrix");
    }
}

namespace TB
{
    /*
        ElementType_t<T> will recursively unravel T::ElementType::...::ElementType
        in order to get to the root ElementType. In other words:

        If type T has a sub-typename ElementType
            use ElementType_t<T::ElementType>
        else
            use T itself (in which case T should be a scalar type)
    */

    /* ========== ElementType ========== */
    template<class T, class = void>
    struct ElementTypeImpl
    {
        using type = T;
        static_assert(is_scalar_v<T> || std::is_same_v<T, void*>, "Need the root operator input type to be a scalar (or void*)");
    };

    template<class T>
    struct ElementTypeImpl<T, std::void_t<typename T::ElementType>>
    {
        using type = typename ElementTypeImpl<typename T::ElementType>::type;
    };

    template<class T>
    using ElementType_t = typename ElementTypeImpl<T>::type;
}

namespace TB
{
    /* ========== OpResultType ========== */
    template<class OP, class LHS, class RHS>
    struct OpResultType
    {
        using type = decltype(OP{}(std::declval<ElementType_t<LHS>>(), std::declval<ElementType_t<RHS>>()));
    };

    template<class OP, class ARG>
    struct OpResultType<OP, ARG, void*>
    {
        using type = decltype(OP{}(std::declval<ElementType_t<ARG>>()));
    };

    template<class OP, class LHS, class RHS = void*>
    using OpResultType_t = typename OpResultType<OP, LHS, RHS>::type;
}

namespace TB
{
    template <class OP, class LHS, class RHS>
    class MatrixExpr : public Matrix<MatrixExpr<OP, LHS, RHS>>, Expression
    {
    public:
        constexpr static bool is_unary_expression_v = std::is_same_v<void*, RHS>;

        using OT_LHS      = std::conditional_t<is_expression_or_scalar_v<LHS>, const LHS, const LHS&>;
        using OT_RHS      = std::conditional_t<is_expression_or_scalar_v<RHS> || is_unary_expression_v, const RHS, const RHS&>;
        using ElementType = OpResultType_t<OP, LHS, RHS>;

        constexpr explicit MatrixExpr(const LHS& arg)
            : m_lhs(arg), m_rhs(nullptr)
        {
            static_assert(is_unary_expression_v, "Operator is not unary, need to provide two inputs");
        }

        constexpr explicit MatrixExpr(const LHS& lhs, const RHS& rhs)
            : m_lhs(lhs), m_rhs(rhs)
        {
            if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
            {
                TB_ENSURE(lhs.shape() == rhs.shape(), "Matrix shapes do not match (" << lhs.shape() << " and " << rhs.shape() << ")");
            }

            static_assert(!is_unary_expression_v, "Operator is not binary, need to provide one input only");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            if constexpr(is_unary_expression_v)
                return apply_unary<OP, LHS>(m_lhs, i);
            else
                return apply_binary<OP, LHS, RHS>(m_lhs, m_rhs, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (is_unary_expression_v)
                return apply_unary<OP, LHS>(m_lhs, rowIdx, colIdx);
            else
                return apply_binary<OP, LHS, RHS>(m_lhs, m_rhs, rowIdx, colIdx);
        }

        constexpr size_t size() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.size();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.size();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr const MatrixShape& shape() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.shape();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.shape();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr size_t rowCount() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.rowCount();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.rowCount();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

        constexpr size_t colCount() const
        {
            if constexpr (is_matrix_v<LHS>)
                return m_lhs.colCount();
            else if constexpr (is_matrix_v<RHS>)
                return m_rhs.colCount();

            static_assert(at_least_one_is_matrix_v<LHS, RHS>, "At least one input must be a matrix");
        }

    private:
        OT_LHS m_lhs;
        OT_RHS m_rhs;
    };

    template <class OP, class MT>
    using MatrixExprUnary = MatrixExpr<OP, MT, void*>;

    template <class OP, class MT1, class MT2>
    using MatrixExprBinary = MatrixExpr<OP, MT1, MT2>;
}

namespace TB
{
    struct OperationAdd
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs + rhs;
        }
    };

    struct OperationSub
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs - rhs;
        }
    };

    struct OperationMul
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs * rhs;
        }
    };

    struct OperationDiv
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 lhs, Type2 rhs) const noexcept
        {
            return lhs / rhs;
        }
    };

    struct OperationNeg
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return -arg;
        }
    };
}

namespace TB
{
    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator+(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationAdd, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator-(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationSub, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator*(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationMul, LHS, RHS>(lhs, rhs);
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    decltype(auto) operator/(const LHS& lhs, const RHS& rhs)
    {
        return MatrixExprBinary<OperationDiv, LHS, RHS>(lhs, rhs);
    }

    template<class ARG, class = std::enable_if_t<is_matrix_v<ARG>>>
    decltype(auto) operator-(const ARG& arg)
    {
        return MatrixExprUnary<OperationNeg, ARG>(arg);
    }
}

namespace TB
{
    namespace detail
    {
        template<class T, class U, bool isFloatingPoint = std::is_floating_point_v<T> || std::is_floating_point_v<U>>
        bool isApproxEqual(const T& lhs, const U& rhs)
        {
            if constexpr (isFloatingPoint)
            {
                return std::abs(lhs - rhs) < 1.e-13;
            }
            else
            {
                return lhs == rhs;
            }
        }
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    bool operator==(const LHS& lhs, const RHS& rhs)
    {
        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            if (lhs.rowCount() != rhs.rowCount() || lhs.colCount() != rhs.colCount())
                return false;
        }

        if constexpr (is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs[i], rhs[i]) == false)
                    return false;
        }
        else if constexpr (is_matrix_v<LHS> && !is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = lhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs[i], rhs) == false)
                    return false;
        }
        else if constexpr (!is_matrix_v<LHS> && is_matrix_v<RHS>)
        {
            for (size_t i = 0, size = rhs.size(); i < size; ++i)
                if (detail::isApproxEqual(lhs, rhs[i]) == false)
                    return false;
        }

        return true;
    }

    template<class LHS, class RHS, class = std::enable_if_t<at_least_one_is_matrix_v<LHS, RHS>>>
    bool operator!=(const LHS& lhs, const RHS& rhs)
    {
        return !(lhs == rhs);
    }
}

namespace TB
{
    template <class MT>
    class MatrixExprTrans : public Matrix<MatrixExprTrans<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprTrans(const MT& mat)
            : m_mat(mat), m_rowCount(m_mat.colCount()), m_colCount(m_mat.rowCount()) { }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return m_mat[(i % m_colCount) * m_rowCount + (i / m_colCount)];
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            return m_mat(colIdx, rowIdx);  // (rowIdx, colIdx) are swapped to (colIdx, rowIdx) as this is transposed
        }

        constexpr size_t size() const
        {
            return m_mat.size();
        }

        constexpr MatrixShape shape() const
        {
            return m_mat.shape().transposed();
        }

        constexpr size_t rowCount() const
        {
            return m_rowCount;
        }

        constexpr size_t colCount() const
        {
            return m_colCount;
        }

    private:
        OT_MT m_mat;
        const size_t m_rowCount, m_colCount;
    };
}

namespace TB
{
    template <class MT>
    class MatrixExprReshape : public Matrix<MatrixExprReshape<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, const MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprReshape(const MT& mat, const size_t& rowCount, const size_t& colCount)
            : m_mat(mat), m_rowCount(rowCount), m_colCount(colCount)
        {
            TB_ENSURE(mat.size() == rowCount * colCount, "Need matrix size (" << mat.size() << ") to be equal to product of row & col count (" << rowCount << " * " << colCount << ")");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            return m_mat[i];
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            return m_mat[rowIdx * m_colCount + colIdx];
        }

        constexpr size_t size() const
        {
            return m_mat.size();
        }

        constexpr MatrixShape shape() const
        {
            return MatrixShape(m_rowCount, m_colCount);
        }

        constexpr size_t rowCount() const
        {
            return m_rowCount;
        }

        constexpr size_t colCount() const
        {
            return m_colCount;
        }

    private:
        OT_MT m_mat;
        const size_t m_rowCount, m_colCount;
    };
}

namespace TB
{
    template<class TypeOut = void>
    struct OperationId
    {
        template<class TypeIn>
        constexpr auto operator()(TypeIn arg) const noexcept
        {
            if constexpr(std::is_same_v<TypeOut, void>)
                return arg;
            else
                return static_cast<TypeOut>(arg);
        }
    };

    struct OperationAbs
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::abs(arg);
        }
    };

    struct OperationSqrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::sqrt(arg);
        }
    };

    struct OperationCbrt
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return std::cbrt(arg);
        }
    };

    struct OperationSquared
    {
        template<class Type>
        constexpr auto operator()(Type arg) const noexcept
        {
            return arg * arg;
        }
    };

    struct OperationPower
    {
        template<class Type1, class Type2>
        constexpr auto operator()(Type1 arg, Type2 n) const noexcept
        {
            return std::pow(arg, n);
        }
    };
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) trans(const MT& arg)
    {
        return MatrixExprTrans<MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) reshape(const MT& arg, const size_t& rowCount, const size_t& colCount)
    {
        return MatrixExprReshape<MT>(arg, rowCount, colCount);
    }

    template<class T, class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) asType(const MT& arg)
    {
        return MatrixExprUnary<OperationId<T>, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) abs(const MT& arg)
    {
        return MatrixExprUnary<OperationAbs, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) sqrt(const MT& arg)
    {
        return MatrixExprUnary<OperationSqrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) cbrt(const MT& arg)
    {
        return MatrixExprUnary<OperationCbrt, MT>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) squared(const MT& arg)
    {
        return MatrixExprUnary<OperationSquared, MT>(arg);
    }

    template<class MT, class ST, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) power(const MT& arg, const ST& n)
    {
        return MatrixExprBinary<OperationPower, MT, ST>(arg, n);
    }
}

namespace TB
{
    template<class T>
    T TB_min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    template<class T>
    T TB_min(const T a, const T b, const T c)
    {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    template<class T>
    T TB_max(const T a, const T b)
    {
        return a > b ? a : b;
    }

    template<class T>
    T TB_max(const T a, const T b, const T c)
    {
        return a > b ? (a > c ? a : c) : (b > c ? b : c);
    }

    constexpr double TB_INF_NEG = -std::numeric_limits<double>::infinity();
    constexpr double TB_INF_POS = std::numeric_limits<double>::infinity();
    constexpr double TB_EPS     = std::numeric_limits<double>::epsilon();
    constexpr double TB_NAN     = std::numeric_limits<double>::quiet_NaN();
    constexpr double TB_ZERO    = std::numeric_limits<double>::min();
}

namespace TB
{
    template <class MT, bool TF>
    class MatrixExprDiagView : public Matrix<MatrixExprDiagView<MT, TF>>, Expression
    {
        enum TypeFlag : bool { ROW = false, COLUMN = true };

    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprDiagView(MT& mat)
            : m_mat(mat), m_size(TB_min(m_mat.rowCount(), m_mat.colCount())) { }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < m_size, "Index (" << i << ") is out if bounds");
            return m_mat(i, i);
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < m_size, "Index (" << i << ") is out if bounds");
            return m_mat(i, i);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
            else if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(colIdx, colIdx);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx == 0, "Column index (" << colIdx << ") is out of bounds (only have " << 1 << " column)");
                return m_mat(rowIdx, rowIdx);
            }
            else if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx == 0, "Row index (" << rowIdx << ") is out of bounds (only have " << 1 << " row)");
                return m_mat(colIdx, colIdx);
            }
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable");

            for (size_t i = 0, size = m_size; i < size; ++i)
                m_mat(i, i) *= rhs;
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (TF == COLUMN)
                return MatrixShape(m_size, 1);
            else if constexpr (TF == ROW)
                return MatrixShape(1, m_size);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (TF == COLUMN)
                return m_size;
            else if constexpr (TF == ROW)
                return 1;
        }

        constexpr size_t colCount() const
        {
            if constexpr (TF == COLUMN)
                return 1;
            else if constexpr (TF == ROW)
                return m_size;
        }

    private:
        OT_MT m_mat;
        size_t m_size;
    };
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(const MT& arg)
    {
        return MatrixExprDiagView<const MT, false>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonal(MT& arg)
    {
        return MatrixExprDiagView<MT, false>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonalT(const MT& arg)
    {
        return MatrixExprDiagView<const MT, true>(arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) diagonalT(MT& arg)
    {
        return MatrixExprDiagView<MT, true>(arg);
    }
}

namespace TB
{
    template <class MT, bool TF>
    class MatrixExprRowColView : public Matrix<MatrixExprRowColView<MT, TF>>, Expression
    {
        enum TypeFlag : bool { ROW = false, COLUMN = true };

    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprRowColView(MT& mat, const size_t& idx)
            : m_mat(mat), m_idx(idx), m_size(1)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(idx < m_mat.rowCount(), "Row index (" << idx << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(idx < m_mat.colCount(), "Column index (" << idx << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr explicit MatrixExprRowColView(MT& mat, const size_t& idx, const size_t& size)
            : m_mat(mat), m_idx(idx), m_size(size)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(idx + size <= m_mat.rowCount(), "Row index + size (" << idx + size << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(idx + size <= m_mat.colCount(), "Column index + size (" << idx + size << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
            }
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            if constexpr (TF == ROW)
            {
                const size_t colCount = m_mat.colCount();
                return m_mat(m_idx + i / colCount, i % colCount);
            }
            else if constexpr (TF == COLUMN)
            {
                return m_mat(i / m_size, m_idx + i % m_size);
            }
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            if constexpr (TF == ROW)
            {
                const size_t colCount = m_mat.colCount();
                return m_mat(m_idx + i / colCount, i % colCount);
            }
            else if constexpr (TF == COLUMN)
            {
                return m_mat(i / m_size, m_idx + i % m_size);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx < m_size, "Row index (" << rowIdx << ") is out of bounds (only have " << m_size << " rows)");
                return m_mat(m_idx + rowIdx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx < m_size, "Column index (" << colIdx << ") is out of bounds (only have " << m_size << " columns)");
                return m_mat(rowIdx, m_idx + colIdx);
            }
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            if constexpr (TF == ROW)
            {
                TB_ENSURE(rowIdx < m_size, "Row index (" << rowIdx << ") is out of bounds (only have " << m_size << " rows)");
                return m_mat(m_idx + rowIdx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                TB_ENSURE(colIdx < m_size, "Column index (" << colIdx << ") is out of bounds (only have " << m_size << " columns)");
                return m_mat(rowIdx, m_idx + colIdx);
            }
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable in order to apply operator*=");

            if constexpr (TF == ROW)
            {
                for (size_t rowIdx = m_idx, rowCount = m_idx + m_size; rowIdx < rowCount; ++rowIdx)
                    for (size_t colIdx = 0, colCount = m_mat.colCount(); colIdx < colCount; ++colIdx)
                        m_mat(rowIdx, colIdx) *= rhs;
            }
            else if constexpr (TF == COLUMN)
            {
                for (size_t colIdx = m_idx, colCount = m_idx + m_size; colIdx < colCount; ++colIdx)
                    for (size_t rowIdx = 0, rowCount = m_mat.rowCount(); rowIdx < rowCount; ++rowIdx)
                        m_mat(rowIdx, colIdx) *= rhs;
            }
        }

        template<class MT2, class = std::enable_if_t<is_matrix_v<MT2>>>
        void operator-=(const MT2& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable in order to apply operator-=");

            TB_ENSURE(this->shape() == rhs.shape(), "Shapes of lhs (" << m_mat.shape() << ") and rhs (" << rhs.shape() << ") do not match");

            if constexpr (TF == ROW)
            {
                for (size_t rowIdx = m_idx, rowCount = m_idx + m_size; rowIdx < rowCount; ++rowIdx)
                    for (size_t colIdx = 0, colCount = m_mat.colCount(); colIdx < colCount; ++colIdx)
                        m_mat(rowIdx, colIdx) -= rhs(rowIdx - m_idx, colIdx);
            }
            else if constexpr (TF == COLUMN)
            {
                for (size_t colIdx = m_idx, colCount = m_idx + m_size; colIdx < colCount; ++colIdx)
                    for (size_t rowIdx = 0, rowCount = m_mat.rowCount(); rowIdx < rowCount; ++rowIdx)
                        m_mat(rowIdx, colIdx) -= rhs(rowIdx, colIdx - m_idx);
            }
        }

        constexpr size_t size() const
        {
            if constexpr (TF == ROW)
                return m_mat.colCount() * m_size;
            else if constexpr (TF == COLUMN)
                return m_mat.rowCount() * m_size;
        }

        constexpr MatrixShape shape() const
        {
            if constexpr (TF == ROW)
                return MatrixShape(m_size, m_mat.colCount());
            else if constexpr (TF == COLUMN)
                return MatrixShape(m_mat.rowCount(), m_size);
        }

        constexpr size_t rowCount() const
        {
            if constexpr (TF == ROW)
                return m_size;
            else if constexpr (TF == COLUMN)
                return m_mat.rowCount();
        }

        constexpr size_t colCount() const
        {
            if constexpr (TF == ROW)
                return m_mat.colCount();
            else if constexpr (TF == COLUMN)
                return m_size;
        }

    private:
        OT_MT m_mat;
        size_t m_idx, m_size;
    };

    template <class MT> using MatrixExprRowView = MatrixExprRowColView<MT, false>;
    template <class MT> using MatrixExprColView = MatrixExprRowColView<MT, true>;
}

namespace TB
{
    /* ===== Row Views (i) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) row(const MT& arg, size_t rowIdx)
    {
        return MatrixExprRowView<const MT>(arg, rowIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) row(MT& arg, size_t rowIdx)
    {
        return MatrixExprRowView<MT>(arg, rowIdx);
    }

    /* ===== Rows Views (i:end) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(const MT& arg, size_t rowIdxStart)
    {
        return MatrixExprRowView<const MT>(arg, rowIdxStart, arg.rowCount() - rowIdxStart);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(MT& arg, size_t rowIdxStart)
    {
        return MatrixExprRowView<MT>(arg, rowIdxStart, arg.rowCount() - rowIdxStart);
    }

    /* ===== Rows Views (i:j) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(const MT& arg, size_t rowIdx, size_t rowSize)
    {
        return MatrixExprRowView<const MT>(arg, rowIdx, rowSize);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) rows(MT& arg, size_t rowIdx, size_t rowSize)
    {
        return MatrixExprRowView<MT>(arg, rowIdx, rowSize);
    }

    /* ===== Column Views (i) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) column(const MT& arg, size_t colIdx)
    {
        return MatrixExprColView<const MT>(arg, colIdx);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) column(MT& arg, size_t colIdx)
    {
        return MatrixExprColView<MT>(arg, colIdx);
    }

    /* ===== Columns Views (i:end) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(const MT& arg, size_t colIdxStart)
    {
        return MatrixExprColView<const MT>(arg, colIdxStart, arg.colCount() - colIdxStart);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(MT& arg, size_t colIdxStart)
    {
        return MatrixExprColView<MT>(arg, colIdxStart, arg.colCount() - colIdxStart);
    }

    /* ===== Columns Views (i:j) ===== */

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(const MT& arg, size_t colIdx, size_t colSize)
    {
        return MatrixExprColView<const MT>(arg, colIdx, colSize);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) columns(MT& arg, size_t colIdx, size_t colSize)
    {
        return MatrixExprColView<MT>(arg, colIdx, colSize);
    }
}

namespace TB
{
    template <class MT>
    class MatrixExprSubmatrixView : public Matrix<MatrixExprSubmatrixView<MT>>, Expression
    {
    public:
        using OT_MT       = std::conditional_t<is_expression_v<MT>, const MT, MT&>;
        using ElementType = typename MT::ElementType;

        constexpr explicit MatrixExprSubmatrixView(MT& mat, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
            : m_mat(mat), m_rowIdx(rowIdx), m_colIdx(colIdx), m_rowSize(rowSize), m_colSize(colSize)
        {
            TB_ENSURE(rowIdx + rowSize <= m_mat.rowCount(), "Row index + size ("    << rowIdx + rowSize << ") is out of bounds (only have " << m_mat.rowCount() << " rows)");
            TB_ENSURE(colIdx + colSize <= m_mat.colCount(), "Column index + size (" << colIdx + colSize << ") is out of bounds (only have " << m_mat.colCount() << " columns)");
        }

        constexpr decltype(auto) operator[](size_t i) const
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            return m_mat(m_rowIdx + i / m_colSize, m_colIdx + i % m_colSize);
        }

        constexpr decltype(auto) operator[](size_t i)
        {
            TB_ENSURE(i < this->size(), "Index (" << i << ") is out if bounds");

            return m_mat(m_rowIdx + i / m_colSize, m_colIdx + i % m_colSize);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx) const
        {
            TB_ENSURE(rowIdx < m_rowSize, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_rowSize << " rows)");
            TB_ENSURE(colIdx < m_colSize, "Column index (" << colIdx << ") is out of bounds (only have " << m_colSize << " columns)");

            return m_mat(m_rowIdx + rowIdx, m_colIdx + colIdx);
        }

        constexpr decltype(auto) operator()(size_t rowIdx, size_t colIdx)
        {
            TB_ENSURE(rowIdx < m_rowSize, "Row index ("    << rowIdx << ") is out of bounds (only have " << m_rowSize << " rows)");
            TB_ENSURE(colIdx < m_colSize, "Column index (" << colIdx << ") is out of bounds (only have " << m_colSize << " columns)");

            return m_mat(m_rowIdx + rowIdx, m_colIdx + colIdx);
        }

        void operator*=(const ElementType& rhs)
        {
            static_assert(is_mutable_matrix_v<MT>, "Need underlying matrix to be mutable");

            for (size_t rowIdx = m_rowIdx, rowCount = m_rowIdx + m_rowSize; rowIdx < rowCount; ++rowIdx)
                for (size_t colIdx = m_colIdx, colCount = m_colIdx + m_colSize; colIdx < colCount; ++colIdx)
                    m_mat(rowIdx, colIdx) *= rhs;
        }

        constexpr size_t size() const
        {
            return m_rowSize * m_colSize;
        }

        constexpr MatrixShape shape() const
        {
            return MatrixShape(m_rowSize, m_colSize);
        }

        constexpr size_t rowCount() const
        {
            return m_rowSize;
        }

        constexpr size_t colCount() const
        {
            return m_colSize;
        }

    private:
        OT_MT m_mat;
        size_t m_rowIdx, m_colIdx, m_rowSize, m_colSize;
    };
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(const MT& arg, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
    {
        return MatrixExprSubmatrixView<const MT>(arg, rowIdx, colIdx, rowSize, colSize);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    constexpr decltype(auto) submatrix(MT& arg, const size_t& rowIdx, const size_t& colIdx, const size_t& rowSize, const size_t& colSize)
    {
        return MatrixExprSubmatrixView<MT>(arg, rowIdx, colIdx, rowSize, colSize);
    }
}

namespace TB
{
    template <class OP, class LHS, class RHS, class = std::enable_if_t<is_matrix_v<LHS> && is_matrix_v<RHS>>>
    struct SumExprBinary
    {
        constexpr static decltype(auto) evaluate(const LHS& lhs, const RHS& rhs)
        {
            constexpr OP pairwiseOperation;

            if (lhs.size() != rhs.size())
                throw("Vector sizes do not match");

            using ElementType = OpResultType_t<OP, LHS, RHS>;

            const size_t N = lhs.size();
            if (N == 0)
                return ElementType(0);

            ElementType totalSum = pairwiseOperation(lhs[0], rhs[0]);
            for (size_t i = 1; i < N; ++i)
                totalSum += pairwiseOperation(lhs[i], rhs[i]);

            return totalSum;
        }
    };

    template <class OP, class VT1, class VT2>
    using SumExprBinary_t = SumExprBinary<OP, VT1, VT2>;
}

namespace TB
{
    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) dot(const MT1& lhs, const MT2& rhs)
    {
        return SumExprBinary<OperationMul, MT1, MT2>::evaluate(lhs, rhs);
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) innerProduct(const MT1& lhs, const MT2& rhs)
    {
        TB_ENSURE(lhs.rowCount() == 1 && rhs.colCount() == 1 && lhs.colCount() == rhs.rowCount(), "Inner-product requires LHS to be a row vector (1 x M) and RHS to be a column vector (M x 1)");

        return dot(lhs, rhs);
    }
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) isSquare(const MT& arg)
    {
        return arg.rowCount() == arg.colCount();
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) isSymmetric(const MT& arg)
    {
        if (!isSquare(arg))
            return false;

        const size_t n = arg.colCount();
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (detail::isApproxEqual(arg(i, j), arg(j, i)) == false)
                    return false;
            }
        }

        return true;
    }
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) minEl(const MT& arg)
    {
        TB_ENSURE(arg.size() > 0, "Cannot use min function on an empty matrix");

        auto minElTemp = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < minElTemp)
                minElTemp = arg[i];
        }

        return minElTemp;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    decltype(auto) maxEl(const MT& arg)
    {
        return -(minEl(-arg));
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMin(const MT& arg)
    {
        TB_ENSURE(arg.size() > 0, "Cannot use argMin function on an empty matrix");

        auto minElTemp = arg[0];
        size_t minIdx  = 0;

        for (size_t i = 1, size = arg.size(); i < size; ++i)
        {
            if (arg[i] < minElTemp)
            {
                minElTemp = arg[i];
                minIdx    = i;
            }
        }

        return minIdx;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMax(const MT& arg)
    {
        return argMin(-arg);
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    size_t argMaxFrom(const MT& arg, const size_t& offset)
    {
        TB_ENSURE(arg.size() > offset, "Need matrix size (" << arg.size() << ") to be larger than the offset (" << offset << ") in argMaxFrom function");

        auto maxElTemp = arg[offset];
        size_t maxIdx  = offset;

        for (size_t i = 1 + offset, size = arg.size(); i < size; ++i)
        {
            if (arg[i] > maxElTemp)
            {
                maxElTemp = arg[i];
                maxIdx    = i;
            }
        }

        return maxIdx;
    }
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    double norm2(const MT& arg)
    {
        return std::sqrt(dot(arg, arg));
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    double norm(const MT& arg, const double& order)
    {
        if (order == TB_INF_NEG)
        {
            return minEl(abs(arg));
        }
        else if (order == TB_INF_POS)
        {
            return maxEl(abs(arg));
        }
        else if (order == 2.0)
        {
            return norm2(arg);
        }
        else
        {
            double absSum = 0;
            for (size_t i = 0, size = arg.size(); i < size; ++i)
                absSum += std::pow(std::abs(arg[i]), order);

            return std::pow(absSum, 1. / order);
        }
    }
}

namespace TB
{
    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) mult(const MT1& lhs, const MT2& rhs)
    {
        const size_t rowCountL = lhs.rowCount();
        const size_t colCountL = lhs.colCount();
        const size_t rowCountR = rhs.rowCount();
        const size_t colCountR = rhs.colCount();
        TB_ENSURE(colCountL == rowCountR, "Need lhs matrix column count (" << colCountL << ") to be equal to rhs matrix row count (" << rowCountR << ") when multiplying");

        using ET = OpResultType_t<OperationMul, MT1, MT2>;
        DenseMatrix<ET, DynamicSize, DynamicSize> result(rowCountL, colCountR, 0);

        for (size_t iCol = 0; iCol < colCountR; ++iCol)
        {
            for (size_t iRow = 0; iRow < rowCountL; ++iRow)
            {
                for (size_t j = 0; j < colCountL; ++j)
                    result(iRow, iCol) += lhs(iRow, j) * rhs(j, iCol);
            }
        }

        return result;
    }

    template<class MT1, class MT2, class = std::enable_if_t<is_matrix_v<MT1> && is_matrix_v<MT2>>>
    decltype(auto) multWithDiagonal(const MT1& lhs, const MT2& rhs)
    {
        const size_t rowCountL = lhs.rowCount();
        const size_t colCountL = lhs.colCount();
        const size_t sizeR     = rhs.size();
        TB_ENSURE(rhs.rowCount() == 1 || rhs.colCount() == 1, "Need rhs to be a row or column vector, but have dimensions " << rhs.rowCount() << "x" << rhs.colCount() << "");
        TB_ENSURE(colCountL == sizeR,                         "Need lhs matrix column count (" << colCountL << ") to be equal to rhs vector size (" << sizeR << ") when multiplying");

        using ET = OpResultType_t<OperationMul, MT1, MT2>;
        DenseMatrix<ET, DynamicSize, DynamicSize> result(rowCountL, sizeR, 0);

        for (size_t k = 0; k < sizeR; ++k)
        {
            for (size_t i = 0; i < rowCountL; ++i)
            {
                result(i, k) += lhs(i, k) * rhs[k];
            }
        }

        return result;
    }
}

namespace TB
{
    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    auto sum(const MT& arg)
    {
        using ElementType = typename MT::ElementType;

        if (arg.size() == 0)
            return ElementType(0);

        ElementType sum = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            sum += arg[i];

        return sum;
    }

    template<class MT, class = std::enable_if_t<is_matrix_v<MT>>>
    auto prod(const MT& arg)
    {
        using ElementType = typename MT::ElementType;

        if (arg.size() == 0)
            return ElementType(1);

        ElementType product = arg[0];
        for (size_t i = 1, size = arg.size(); i < size; ++i)
            product *= arg[i];

        return product;
    }
}

namespace TB
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

namespace TB
{
    template<class Type, size_t Size, bool TF = false>
    using StaticVector = DenseVector<Type, Size, TF>;

    template<class Type, bool TF = false>
    using DynamicVector = DenseVector<Type, DynamicSize, TF>;

    template<class Type, size_t Rows, size_t Cols>
    using StaticMatrix = DenseMatrix<Type, Rows, Cols>;

    template<class Type>
    using DynamicMatrix = DenseMatrix<Type, DynamicSize, DynamicSize>;
}

namespace TB
{
    /* Based on https://www.geeksforgeeks.org/cholesky-decomposition-matrix-decomposition */

    template<size_t R, size_t C>
    class CholeskyDecomp
    {
    public:
        DenseMatrix<double, R, C> lowerTriangular;

        explicit CholeskyDecomp(const DenseMatrix<double, R, C>& matrix);
    };

    // Inline Definitions

    template<size_t R, size_t C>
    inline CholeskyDecomp<R, C>::CholeskyDecomp(const DenseMatrix<double, R, C>& matrix)
        : lowerTriangular(matrix.shape())
    {
        TB_ENSURE(matrix.size() > 0,   "Input matrix in CholeskyDecomp cannot be empty");
        TB_ENSURE(isSymmetric(matrix), "Only square symmetric matrices are allowed in CholeskyDecomp");

        const size_t n = matrix.rowCount();

        // Decomposing a matrix into Lower Triangular
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j <= i; ++j)
            {
                double sum = 0;

                if (i == j)  // Summation for diagonals
                {
                    for (size_t k = 0; k < j; k++)
                        sum += lowerTriangular(j, k) * lowerTriangular(j, k);
                    lowerTriangular(j, j) = std::sqrt(matrix(j, j) - sum);
                }
                else
                {
                    // Evaluating L(i, j) using L(j, j)
                    for (size_t k = 0; k < j; ++k)
                        sum += lowerTriangular(i, k) * lowerTriangular(j, k);

                    TB_ENSURE(std::abs(lowerTriangular(j, j)) > 0, "Input matrix in CholeskyDecomp cannot be processed (possibly singular)");

                    lowerTriangular(i, j) = (matrix(i, j) - sum) / lowerTriangular(j, j);
                }
            }
        }
    }
}

namespace TB
{
    class JacobiRotation
    {
    public:
        double c, s;

        explicit JacobiRotation() noexcept;
        explicit JacobiRotation(const double& c, const double& s) noexcept;

        template<class MT>
        explicit JacobiRotation(const size_t& p, const size_t& q, const MT& mat);

        template<class MT>
        void rotateMatrixFromLeft(const size_t& p, const size_t& q, MT& mat) const;

        template<class MT>
        void rotateMatrixFromRight(const size_t& p, const size_t& q, MT& mat) const;

        JacobiRotation transposed() const;
        JacobiRotation mult(const JacobiRotation& rhs);
    };

    // Inline Definitions

    inline JacobiRotation::JacobiRotation() noexcept
        : c(0), s(0) { }

    inline JacobiRotation::JacobiRotation(const double& c, const double& s) noexcept
        : c(c), s(s) { }

    template<class MT>
    inline JacobiRotation::JacobiRotation(const size_t& p, const size_t& q, const MT& mat)
    {
        const double x    = mat(p, p), y = mat(p, q), z = mat(q, q);
        const double deno = 2. * std::abs(y);

        if (deno < std::numeric_limits<double>::min())
        {
            c = 1.;
            s = 0.;
        }
        else
        {
            const double tau    = (x - z) / deno;
            const double w      = std::sqrt(tau * tau + 1.0);
            const double t      = 1. / (tau > 0. ? tau + w : tau - w);
            const double sign_t = t > 0. ? 1. : -1.;
            const double n      = 1. / std::sqrt(t * t + 1.);
            s = -sign_t * (y / std::abs(y)) * std::abs(t) * n;
            c = n;
        }
    }

    template<class MT>
    inline void JacobiRotation::rotateMatrixFromLeft(const size_t& p, const size_t& q, MT& mat) const
    {
        for (size_t ci = 0, size = mat.colCount(); ci < size; ++ci)
        {
            const double temp = c * mat(q, ci) - s * mat(p, ci);
            mat(p, ci)        = s * mat(q, ci) + c * mat(p, ci);
            mat(q, ci)        = temp;
        }
    }

    template<class MT>
    inline void JacobiRotation::rotateMatrixFromRight(const size_t& p, const size_t& q, MT& mat) const
    {
        for (size_t ri = 0, size = mat.rowCount(); ri < size; ++ri)
        {
            const double temp = s * mat(ri, p) + c * mat(ri, q);
            mat(ri, p)        = c * mat(ri, p) - s * mat(ri, q);
            mat(ri, q)        = temp;
        }
    }

    inline JacobiRotation JacobiRotation::transposed() const
    {
        return JacobiRotation(c, -s);
    }

    inline JacobiRotation JacobiRotation::mult(const JacobiRotation& rhs)
    {
        return JacobiRotation(c * rhs.c - s * rhs.s, s * rhs.c + c * rhs.s);
    }
}

namespace TB
{
    /* Based on https://gitlab.com/libeigen/eigen/-/blob/master/Eigen/src/SVD/JacobiSVD.h */

    template<size_t R, size_t C>
    class SingularValueDecomp
    {
        using DenseVectorType = DenseVector<double, R == DynamicSize ? DynamicSize : (R < C ? R : C), false>;

    public:
        DenseMatrix<double, R, C> matrixU, matrixV, invertedMatrix;
        DenseVectorType singularValues;

        explicit SingularValueDecomp(const DenseMatrix<double, R, C>& matrix);

        DenseVectorType solve(const DenseVectorType& y) const;

    private:
        static void JacobiSVD2x2(const DenseMatrix<double, R, C>& matrix, const size_t& p, const size_t& q, JacobiRotation& j_left, JacobiRotation& j_right);
    };

    // Inline Definitions

    template<size_t R, size_t C>
    inline SingularValueDecomp<R, C>::SingularValueDecomp(const DenseMatrix<double, R, C>& matrix)
        : matrixU(DenseMatrix<double, R, C>::Identity(TB_min(matrix.rowCount(), matrix.colCount()))),
          matrixV(DenseMatrix<double, R, C>::Identity(TB_min(matrix.rowCount(), matrix.colCount()))),
          invertedMatrix(),
          singularValues(TB_min(matrix.rowCount(), matrix.colCount()))
    {
        constexpr double precision = 2.0 * TB_EPS;

        // Scaling factor to reduce over/under-flows
        double scale = maxEl(abs(matrix));
        if (scale == 0.)
            return;

        /*** step 1. The R-SVD step: we use a QR decomposition to reduce to the case of a square matrix */
        DenseMatrix<double, R, C> workMatrix = matrix / scale;

        /*** step 2. The main Jacobi SVD iteration. ***/
        double maxDiagEntry = maxEl(abs(diagonal(workMatrix)));
        const size_t mSize  = diagonal(workMatrix).size();

        bool finished = false;
        while (!finished)
        {
            finished = true;

            // do a sweep: for all index pairs (p,q), perform SVD of the corresponding 2x2 sub-matrix
            for (size_t p = 1; p < mSize; ++p)
            {
                for (size_t q = 0; q < p; ++q)
                {
                    // if this 2x2 sub-matrix is not diagonal already...
                    // notice that this comparison will evaluate to false if any NaN is involved, ensuring that NaN's don't
                    // keep us iterating forever. Similarly, small denormal numbers are considered zero.
                    const double threshold = TB_max(TB_ZERO, precision * maxDiagEntry);
                    if (std::abs(workMatrix(p, q)) > threshold || std::abs(workMatrix(q, p)) > threshold)
                    {
                        finished = false;
                        // perform SVD decomposition of 2x2 sub-matrix corresponding to indices p,q to make it diagonal
                        JacobiRotation j_left, j_right;
                        JacobiSVD2x2(workMatrix, p, q, j_left, j_right);

                        j_left.rotateMatrixFromLeft(p, q, workMatrix);
                        j_left.transposed().rotateMatrixFromRight(p, q, matrixU);

                        j_right.rotateMatrixFromRight(p, q, workMatrix);
                        j_right.rotateMatrixFromRight(p, q, matrixV);

                        // keep track of the largest diagonal coefficient
                        maxDiagEntry = TB_max(maxDiagEntry, std::abs(workMatrix(p, p)), std::abs(workMatrix(q, q)));
                    }
                }
            }
        }

        /*** step 3. The work matrix is now diagonal, so ensure it's positive so its diagonal entries are the singular values ***/
        for (size_t i = 0; i < mSize; ++i)
        {
            const double a    = workMatrix(i, i);
            singularValues[i] = std::abs(a);
            if (a < 0.)
                column(matrixU, i) *= -1.;
        }

        singularValues *= scale;

        /*** step 4. Sort singular values in descending order and compute the number of nonzero singular values ***/
        for (size_t i = 0; i < mSize; i++)
        {
            size_t pos = argMaxFrom(singularValues, i);
            const double maxRemainingSingularValue = singularValues[pos];

            if (maxRemainingSingularValue == 0.)
                break;

            if (i != pos)
            {
                std::swap(singularValues[i], singularValues[pos]);
                swapColumns(matrixU, i, pos);
                swapColumns(matrixV, i, pos);
            }
        }

        if (minEl(abs(singularValues)) > 0)
            invertedMatrix = mult(multWithDiagonal(matrixV, 1. / singularValues), trans(matrixU));
    }

    template<size_t R, size_t C>
    inline void SingularValueDecomp<R, C>::JacobiSVD2x2(const DenseMatrix<double, R, C>& matrix, const size_t& p, const size_t& q, JacobiRotation& j_left, JacobiRotation& j_right)
    {
        StaticMatrix<double, 2, 2> m(2, 2);
        m(0, 0) = matrix(p, p);
        m(0, 1) = matrix(p, q);
        m(1, 0) = matrix(q, p);
        m(1, 1) = matrix(q, q);

        JacobiRotation rot1;
        const double t = m(0, 0) + m(1, 1);
        const double d = m(1, 0) - m(0, 1);

        if (std::abs(d) < std::numeric_limits<double>::min())
        {
            rot1.s = 0.;
            rot1.c = 1.;
        }
        else
        {
            const double u   = t / d;
            const double tmp = std::sqrt(1. + u * u);
            rot1.s = 1. / tmp;
            rot1.c = u / tmp;
        }

        rot1.rotateMatrixFromLeft(0, 1, m);
        j_right = JacobiRotation(0, 1, m);
        j_left  = rot1.mult(j_right.transposed());
    }

    template<size_t R, size_t C>
    inline typename SingularValueDecomp<R, C>::DenseVectorType SingularValueDecomp<R, C>::solve(const DenseVectorType& y) const
    {
        return mult(invertedMatrix, y);
    }
}

namespace TB
{
    /* Based on https://www.cs.cornell.edu/~bindel/class/cs6210-f09/lec18.pdf */

    template<size_t R, size_t C>
    class QRDecomp
    {
    public:
        DenseMatrix<double, R, C> matrixQ, matrixR;

        explicit QRDecomp(const DenseMatrix<double, R, C>& matrix);
    };

    // Inline Definitions

    template<size_t R, size_t C>
    inline QRDecomp<R, C>::QRDecomp(const DenseMatrix<double, R, C>& matrix)
        : matrixQ(DenseMatrix<double, R, C>::Identity(matrix.rowCount())),
          matrixR(matrix)
    {
        const size_t rowCount = matrixR.rowCount();
        const size_t colCount = matrixR.colCount();

        for (size_t j = 0; j < colCount; ++j)
        {
            const double colNorm = norm(submatrix(matrixR, j, j, rowCount - j, 1), 2);

            if (colNorm != 0)
            {
                const double Rjj = matrixR(j, j);
                const double s   = Rjj > 0 ? -1 : 1;
                const double u1  = Rjj - s * colNorm;
                const double tau = -s * u1 / colNorm;

                DenseMatrix<double, R, C> w = submatrix(matrixR, j, j, rowCount - j, 1) / u1;
                w(0, 0) = 1;

                rows(matrixR, j)    -= mult(tau * w, mult(trans(w), submatrix(matrixR, j, 0, rowCount - j, colCount)));
                columns(matrixQ, j) -= mult(mult(submatrix(matrixQ, 0, j, rowCount, colCount - j), w), trans(tau * w));

            }
        }
    }
}
