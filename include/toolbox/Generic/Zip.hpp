#pragma once

#include <tuple>
#include <stdexcept>


namespace Toolbox
{
    template<bool WithIndexFlag = false, class... Ts>
    class Zip
    {
    public:
        explicit Zip(const std::tuple<const Ts&...>& data)
            : m_data(data) { }

        explicit Zip(const Ts&... objs)
            : m_data(objs...)
        {
            auto ensureSameSize = [N = std::get<0>(m_data).size()](const auto& obj) {
                if (N != obj.size())
                    throw std::out_of_range("Zip input vectors have non-matching sizes"); };
            (ensureSameSize(objs), ...);
        }

        struct ZipIterator
        {
        public:
            explicit ZipIterator(const std::tuple<const Ts&...>& data, size_t idx)
                : m_data(data), m_idx(idx) { }

            ZipIterator& operator++()
            {
                ++m_idx;
                return *this;
            }

            ZipIterator operator++(int)
            {
                return ZipIterator(m_data, m_idx++);
            }

            bool operator!=(const ZipIterator& rhs) const
            {
                return m_idx != rhs.m_idx;
            }

            decltype(auto) operator*() const
            {
                if constexpr (WithIndexFlag)
                    return std::apply([this](const auto&... obj) { return std::forward_as_tuple(m_idx, obj.at(m_idx)...); }, m_data);
                else
                    return std::apply([this](const auto&... obj) { return std::forward_as_tuple(obj.at(m_idx)...); }, m_data);
            }

        private:
            const std::tuple<const Ts&...>& m_data;
            size_t m_idx;
        };

        ZipIterator begin() const
        {
            return ZipIterator(m_data, 0);
        }

        ZipIterator end() const
        {
            return ZipIterator(m_data, std::get<0>(m_data).size());
        }

        decltype(auto) withIndex() const
        {
            return Zip<true, Ts...>(m_data);
        }

    private:
        const std::tuple<const Ts&...> m_data;
    };
}
