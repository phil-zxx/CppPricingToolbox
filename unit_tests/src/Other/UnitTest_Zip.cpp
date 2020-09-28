#include <doctest/doctest.h>
#include <toolbox/Generic/Zip.hpp>
#include <sstream>
#include <vector>
#include <array>

using namespace TB;

struct Dummy
{
    explicit Dummy(int value) noexcept
        : m_value(value) { }

    // This ensures that the Zip function below indeed makes no copies of the Dummy objects
    Dummy(const Dummy& rhs) noexcept = delete;
    Dummy(Dummy&& rhs) noexcept = delete;
    Dummy& operator=(const Dummy& rhs) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Dummy& rhs)
    {
        return os << "Dummy(" << rhs.m_value << ")";
    }

private:
    int m_value;
};

TEST_CASE("UnitTest_Zip")
{
    const std::vector<int> vec1{10, 20, 30};
    std::array<Dummy, 3>   vec2{Dummy(0), Dummy(123), Dummy(-80)};
    std::array<Dummy, 2>   vec3{Dummy(1), Dummy(456)};

    std::ostringstream os1;
    for (const auto& [a, b] : Zip(vec1, vec2))
        os1 << a << "|" << b << " ";
    CHECK(os1.str() == "10|Dummy(0) 20|Dummy(123) 30|Dummy(-80) ");

    std::ostringstream os2;
    for (const auto& [i, a, b] : Zip(vec1, vec2).withIndex())
        os2 << i << ":" << a << "|" << b << " ";
    CHECK(os2.str() == "0:10|Dummy(0) 1:20|Dummy(123) 2:30|Dummy(-80) ");

    CHECK_NOTHROW(Zip(vec1, vec2, vec2));
    CHECK_THROWS (Zip(vec3, vec2));
}
