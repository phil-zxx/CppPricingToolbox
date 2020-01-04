#pragma once

#include <cstddef>
#include <vector>


namespace Toolbox
{
    struct SampleData
    {
        double a, b;
        int* p;
        std::vector<char> v;
    };

    template<class T, size_t N = sizeof(T)>
    class SerialisedData
    {
    public:
        constexpr SerialisedData(const T& obj) noexcept
            : data()
        {
            const auto ptr = reinterpret_cast<const std::byte*>(&obj);
            for (size_t i = 0; i < N; ++i)
                data[i] = ptr[i];
        }

        template<class T>
        constexpr T deserialise() const
        {
            const auto obj = reinterpret_cast<const T&>(data[0]);
            return obj;
        }

    private:
        std::byte data[N];
    };
}