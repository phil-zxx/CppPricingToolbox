#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_StaticVector_Initialisation")
{
    const StaticVector<double, 9> vec1;
    const StaticVector<double, 8> vec2(4);
    const StaticVector<double, 7> vec3(5, 9);
    const StaticVector<double, 6> vec4{ 7,8,9 };

    CHECK(vec1.capacity() == 9);
    CHECK(vec1.rowCount() == 0);
    CHECK(vec1.colCount() == 0);
    CHECK(vec1.size()     == 0);
    CHECK_THROWS(vec1.at(0));

    CHECK(vec2.capacity() == 8);
    CHECK(vec2.rowCount() == 4);
    CHECK(vec2.colCount() == 1);
    CHECK(vec2.size()     == 4);
    CHECK_NOTHROW(vec2.at(3));
    CHECK_THROWS (vec2.at(4));

    CHECK(vec3.capacity() == 7);
    CHECK(vec3.rowCount() == 5);
    CHECK(vec3.colCount() == 1);
    CHECK(vec3.size()     == 5);
    CHECK(vec3[0]         == 9);
    CHECK(vec3[1]         == 9);
    CHECK(vec3[2]         == 9);
    CHECK(vec3[3]         == 9);
    CHECK(vec3[4]         == 9);
    CHECK_NOTHROW(vec3.at(4));
    CHECK_THROWS (vec3.at(5));

    CHECK(vec4.capacity() == 6);
    CHECK(vec4.rowCount() == 3);
    CHECK(vec4.colCount() == 1);
    CHECK(vec4.size()     == 3);
    CHECK(vec4[0]         == 7);
    CHECK(vec4[1]         == 8);
    CHECK(vec4[2]         == 9);
    CHECK_NOTHROW(vec4.at(2));
    CHECK_THROWS (vec4.at(3));
}

TEST_CASE("UnitTest_DynamicVector_Initialisation")
{
    const DynamicVector<double> vec1;
    const DynamicVector<double> vec2(4);
    const DynamicVector<double> vec3(5, 9);
    const DynamicVector<double> vec4{ 7,8,9 };

    CHECK(vec1.capacity() == 0);
    CHECK(vec1.rowCount() == 0);
    CHECK(vec1.colCount() == 0);
    CHECK(vec1.size()     == 0);
    CHECK_THROWS(vec1.at(0));

    CHECK(vec2.capacity() == 4);
    CHECK(vec2.rowCount() == 4);
    CHECK(vec2.colCount() == 1);
    CHECK(vec2.size()     == 4);
    CHECK_NOTHROW(vec2.at(3));
    CHECK_THROWS (vec2.at(4));

    CHECK(vec3.capacity() == 5);
    CHECK(vec3.rowCount() == 5);
    CHECK(vec3.colCount() == 1);
    CHECK(vec3.size()     == 5);
    CHECK(vec3[0]         == 9);
    CHECK(vec3[1]         == 9);
    CHECK(vec3[2]         == 9);
    CHECK(vec3[3]         == 9);
    CHECK(vec3[4]         == 9);
    CHECK_NOTHROW(vec3.at(4));
    CHECK_THROWS (vec3.at(5));

    CHECK(vec4.capacity() == 3);
    CHECK(vec4.rowCount() == 3);
    CHECK(vec4.colCount() == 1);
    CHECK(vec4.size()     == 3);
    CHECK(vec4[0]         == 7);
    CHECK(vec4[1]         == 8);
    CHECK(vec4[2]         == 9);
    CHECK_NOTHROW(vec4.at(2));
    CHECK_THROWS (vec4.at(3));
}

TEST_CASE("UnitTest_StaticVector_Initialisation_Transposed")
{
    const StaticVector<double, 9, true> vec1;
    const StaticVector<double, 8, true> vec2(4);
    const StaticVector<double, 7, true> vec3(5, 9);
    const StaticVector<double, 6, true> vec4{ 7,8,9 };

    CHECK(vec1.capacity() == 9);
    CHECK(vec1.rowCount() == 0);
    CHECK(vec1.colCount() == 0);
    CHECK(vec1.size()     == 0);
    CHECK_THROWS(vec1.at(0));

    CHECK(vec2.capacity() == 8);
    CHECK(vec2.rowCount() == 1);
    CHECK(vec2.colCount() == 4);
    CHECK(vec2.size()     == 4);
    CHECK_NOTHROW(vec2.at(3));
    CHECK_THROWS (vec2.at(4));

    CHECK(vec3.capacity() == 7);
    CHECK(vec3.rowCount() == 1);
    CHECK(vec3.colCount() == 5);
    CHECK(vec3.size()     == 5);
    CHECK(vec3[0]         == 9);
    CHECK(vec3[1]         == 9);
    CHECK(vec3[2]         == 9);
    CHECK(vec3[3]         == 9);
    CHECK(vec3[4]         == 9);
    CHECK_NOTHROW(vec3.at(4));
    CHECK_THROWS (vec3.at(5));

    CHECK(vec4.capacity() == 6);
    CHECK(vec4.rowCount() == 1);
    CHECK(vec4.colCount() == 3);
    CHECK(vec4.size()     == 3);
    CHECK(vec4[0]         == 7);
    CHECK(vec4[1]         == 8);
    CHECK(vec4[2]         == 9);
    CHECK_NOTHROW(vec4.at(2));
    CHECK_THROWS (vec4.at(3));
}

TEST_CASE("UnitTest_DynamicVector_Initialisation_Transposed")
{
    const DynamicVector<double, true> vec1;
    const DynamicVector<double, true> vec2(4);
    const DynamicVector<double, true> vec3(5, 9);
    const DynamicVector<double, true> vec4{ 7,8,9 };

    CHECK(vec1.capacity() == 0);
    CHECK(vec1.rowCount() == 0);
    CHECK(vec1.colCount() == 0);
    CHECK(vec1.size()     == 0);
    CHECK_THROWS(vec1.at(0));

    CHECK(vec2.capacity() == 4);
    CHECK(vec2.rowCount() == 1);
    CHECK(vec2.colCount() == 4);
    CHECK(vec2.size()     == 4);
    CHECK_NOTHROW(vec2.at(3));
    CHECK_THROWS (vec2.at(4));

    CHECK(vec3.capacity() == 5);
    CHECK(vec3.rowCount() == 1);
    CHECK(vec3.colCount() == 5);
    CHECK(vec3.size()     == 5);
    CHECK(vec3[0]         == 9);
    CHECK(vec3[1]         == 9);
    CHECK(vec3[2]         == 9);
    CHECK(vec3[3]         == 9);
    CHECK(vec3[4]         == 9);
    CHECK_NOTHROW(vec3.at(4));
    CHECK_THROWS (vec3.at(5));

    CHECK(vec4.capacity() == 3);
    CHECK(vec4.rowCount() == 1);
    CHECK(vec4.colCount() == 3);
    CHECK(vec4.size()     == 3);
    CHECK(vec4[0]         == 7);
    CHECK(vec4[1]         == 8);
    CHECK(vec4[2]         == 9);
    CHECK_NOTHROW(vec4.at(2));
    CHECK_THROWS (vec4.at(3));
}

TEST_CASE("UnitTest_Vector_Initializerlist")
{
    const StaticVector<double, 10> vecS{ 7,5,25,11 };
    const DynamicVector<int> vecD{ 6,3,-3,6,-32,8,99 };

    CHECK(vecS.capacity() == 10);
    CHECK(vecS.rowCount() == 4);
    CHECK(vecS.colCount() == 1);
    CHECK(vecS.capacity() == 10);
    CHECK(vecS.size()     == 4);
    CHECK(vecS[0]         == 7.);
    CHECK(vecS[1]         == 5.);
    CHECK(vecS[2]         == 25.);
    CHECK(vecS.at(3)      == 11.);
    CHECK_THROWS(vecS.at(4));
    CHECK_THROWS(vecS.at(8));

    CHECK(vecD.capacity() == 7);
    CHECK(vecD.rowCount() == 7);
    CHECK(vecD.colCount() == 1);
    CHECK(vecD.size()     == 7);
    CHECK(vecD[0]         == 6);
    CHECK(vecD[1]         == 3);
    CHECK(vecD[2]         == -3);
    CHECK(vecD[3]         == 6);
    CHECK(vecD[4]         == -32);
    CHECK(vecD[5]         == 8);
    CHECK(vecD[6]         == 99);
    CHECK_THROWS(vecD.at(7));
    CHECK_THROWS(vecD.at(10));
}

TEST_CASE("UnitTest_Vector_InitialisationValidity")
{
    CHECK_NOTHROW(StaticVector<int, 3>(1));
    CHECK_NOTHROW(StaticVector<int, 3>(2));
    CHECK_NOTHROW(StaticVector<int, 3>(3));
    CHECK_THROWS (StaticVector<int, 3>(4));
    CHECK_THROWS (StaticVector<int, 10>(15));
    CHECK_NOTHROW(StaticVector<int, 4>{3,4,5,6});
    CHECK_THROWS (StaticVector<int, 4>{3,4,5,6,7});
    
    CHECK_NOTHROW(DynamicVector<int>{3,4,5,6});
    CHECK_NOTHROW(DynamicVector<int>{3,4,5,6,7});
}
