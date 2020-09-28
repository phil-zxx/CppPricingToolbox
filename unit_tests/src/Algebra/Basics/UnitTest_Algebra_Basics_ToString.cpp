#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Basics_ToString")
{
    const StaticVector<double, 4> vec1;
    const StaticVector<double, 3> vec2(3, 5);
    const DynamicMatrix<double> mat1{ {5,1.e-4,5},{987,-5,-1589},{0,4,-898},{std::numeric_limits<double>::quiet_NaN(),100,4.56789},{1.e-8,1.e-9,std::numeric_limits<double>::infinity()} };

    const std::string vec1StrTrue = "[]";
    const std::string vec2StrTrue = "[[          5 ],\n [          5 ],\n [          5 ]]";
    const std::string mat1StrTrue = "[[          5      0.0001           5 ],\n [        987          -5       -1589 ],\n [          .           4        -898 ],\n [        nan         100     4.56789 ],\n [      1e-08           .         inf ]]";

    CHECK(vec1.toString() == vec1StrTrue);
    CHECK(vec2.toString() == vec2StrTrue);
    CHECK(mat1.toString() == mat1StrTrue);

    std::ostringstream osVec1; osVec1 << vec1;
    std::ostringstream osVec2; osVec2 << vec2;
    std::ostringstream osMat1; osMat1 << mat1;
    CHECK(osVec1.str() == vec1StrTrue);
    CHECK(osVec2.str() == vec2StrTrue);
    CHECK(osMat1.str() == mat1StrTrue);
}
