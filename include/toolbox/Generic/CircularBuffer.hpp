#pragma once

#include <array>
#include <sstream>


namespace TB
{
    template<class T, int N>
    class CircularBuffer
    {
    public:
        constexpr CircularBuffer() noexcept
            : m_data(), m_startIdx(0), m_size(0) { }

        constexpr void push_back(const T val) noexcept
        {
            if (m_size < N)
            {
                m_data[m_size] = val;
                ++m_size;
            }
            else
            {
                m_data[m_startIdx] = val;
                increase_start_idx();
            }
        }

        constexpr T at(const size_t& i) const
        {
            if (i >= N)
                throw("Index out of bound");

            return operator[](i);
        }

        constexpr T operator[](const size_t& i) const
        {
            if (m_startIdx + i < N)
                return m_data[m_startIdx + i];
            else
                return m_data[m_startIdx + i - N];
        }

        constexpr void pop_front()
        {
            if (m_size > 0)
            {
                increase_start_idx();
                --m_size;
            }
        }

        constexpr void pop_back()
        {
            if (m_size > 0)
                --m_size;
        }

        constexpr size_t size() const
        {
            return m_size;
        }

        friend std::ostream& operator<<(std::ostream& os, const CircularBuffer& rhs)
        {
            os << "[ ";
            for (size_t i = 0; i < rhs.size(); ++i)
                os << rhs.at(i) << " ";
            return os << "]";
        }

    private:
        std::array<T, N> m_data;
        size_t m_startIdx, m_size;

        constexpr void increase_start_idx()
        {
            ++m_startIdx;
            if (m_startIdx == N)
                m_startIdx = 0;
        }
    };
}
