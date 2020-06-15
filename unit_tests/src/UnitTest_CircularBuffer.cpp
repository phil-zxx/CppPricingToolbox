#include <catch2/catch_test_macros.hpp>
#include <toolbox/Generic/CircularBuffer.hpp>

using namespace Toolbox;


constexpr CircularBuffer<int, 4> create_buffer()
{
    CircularBuffer<int, 4> cb;

    cb.push_back(5);
    cb.push_back(8);
    cb.push_back(3);

    cb.push_back(4);
    cb.push_back(6);
    cb.push_back(9);
    cb.push_back(2);

    return cb;
}

TEST_CASE("UnitTest_CircularBuffer")
{
    constexpr CircularBuffer<int, 4> cb = create_buffer();

    static_assert(cb[0] == 4);
    static_assert(cb[1] == 6);
    static_assert(cb[2] == 9);
    static_assert(cb[3] == 2);
    static_assert(cb.at(3) == 2);
}
