#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Vector_BaseFunctions")
{
    const StaticVector<double, 10> vecS1(3), vecS2(3, 7);
    const DynamicVector<int> vecD(3, 5);

    CHECK(vecS1.capacity() == 10);
    CHECK(vecS1.size()     == 3);
    CHECK(vecS1.capacity() == vecS2.capacity());
    CHECK(vecS1.size()     == vecS2.size());
    CHECK(vecS1[0]         == 0.);
    CHECK(vecS1[1]         == 0.);
    CHECK(vecS1[2]         == 0.);
    CHECK(vecS2[0]         == 7.);
    CHECK(vecS2[1]         == 7.);
    CHECK(vecS2[2]         == 7.);
    CHECK(vecS1.at(2)      == 0.);
    CHECK(vecS2.at(2)      == 7.);
    CHECK_THROWS(vecS1.at(3));
    CHECK_THROWS(vecS2.at(3));

    CHECK(vecD.capacity() == 3);
    CHECK(vecD.size()     == 3);
    CHECK(vecD[0]         == 5);
    CHECK(vecD[1]         == 5);
    CHECK(vecD.at(2)      == 5);
    CHECK_THROWS(vecD.at(3));
}

TEST_CASE("UnitTest_Vector_InitList")
{
    const StaticVector<double, 10> vecS{ 7,5,25,11 };
    const DynamicVector<int> vecD{ 6,3,-3,6,-32,8,99 };

    CHECK(vecS.capacity() == 10);
    CHECK(vecS.size()     == 4);
    CHECK(vecS[0]         == 7.);
    CHECK(vecS[1]         == 5.);
    CHECK(vecS[2]         == 25.);
    CHECK(vecS.at(3)      == 11.);
    CHECK_THROWS(vecS.at(4));
    CHECK_THROWS(vecS.at(8));

    CHECK(vecD.capacity() == 7);
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

TEST_CASE("UnitTest_Vector_Size")
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

TEST_CASE("UnitTest_Vector_Expressions")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    SUBCASE("Test_Type")
    {
        const auto expr1 = vecS;
        const auto expr2 = trans(vecS);
        const auto expr3 = vecS + 3;

        CHECK(std::string(typeid(expr1).name()) == "class Toolbox::DenseVector<int,10,0>");
        CHECK(std::string(typeid(expr2).name()) == "class Toolbox::VectorExpr<struct Toolbox::OperatorId<void>,class Toolbox::DenseVector<int,10,0>,void * __ptr64,1>");
        CHECK(std::string(typeid(expr3).name()) == "class Toolbox::VectorExpr<struct Toolbox::OperatorAdd,class Toolbox::DenseVector<int,10,0>,int,0>");
    }

    SUBCASE("Test_MinMax")
    {
        const auto minS = min(vecS);
        const auto minD = min(vecD);
        const auto minE = min(vecS + 3 * abs(vecD));
        CHECK(minS == -9);
        CHECK(minD == -3);
        CHECK(minE == 6);
        
        const auto maxS = max(vecS);
        const auto maxD = max(vecD);
        const auto maxE = max(vecS + 3 * abs(vecD));
        CHECK(maxS == 7);
        CHECK(maxD == 7);
        CHECK(maxE == 28);

        const auto argMinS = argMin(vecS);
        const auto argMinD = argMin(vecD);
        const auto argMinE = argMin(vecS + 3 * abs(vecD));
        CHECK(argMinS == 2);
        CHECK(argMinD == 0);
        CHECK(argMinE == 2);

        const auto argMaxS = argMax(vecS);
        const auto argMaxD = argMax(vecD);
        const auto argMaxE = argMax(vecS + 3 * abs(vecD));
        CHECK(argMaxS == 1);
        CHECK(argMaxD == 1);
        CHECK(argMaxE == 1);
    }

    SUBCASE("Test_Dot1")
    {
        const auto dotProductDbl   = dot(vecS, vecD);
        const auto dotProductInt   = dot(vecS, asType<int>(vecD));
        const auto innerProductDbl = innerProduct(trans(vecS), vecD);
        const auto innerProductInt = innerProduct(trans(vecS), asType<int>(vecD));
        
        CHECK(dotProductDbl   == -11);
        CHECK(dotProductInt   == -11);
        CHECK(innerProductDbl == -11);
        CHECK(innerProductInt == -11);
        
        CHECK(std::string(typeid(dotProductDbl).name())   == "double");
        CHECK(std::string(typeid(dotProductInt).name())   == "int");
        CHECK(std::string(typeid(innerProductDbl).name()) == "double");
        CHECK(std::string(typeid(innerProductInt).name()) == "int");
    }

    SUBCASE("Test_Dot2")
    {
        const StaticVector<int, 5> v1{ { 5, 4, 10, 6, -3 } };
        const DynamicVector<int>   v2{ { 2, 6, -4, 3, 12 } };
        const auto dotProduct = dot(v1, v2);

        CHECK(dotProduct == -24);
    }

    SUBCASE("Test_Sum_Product")
    {
        const auto prodResult1 = prod(StaticVector<int, 10>());
        const auto prodResult2 = prod(vecS);
        const auto sumResult1  = sum(DynamicVector<int>());
        const auto sumResult2  = sum(vecD);
        
        CHECK(prodResult1 == 1);
        CHECK(sumResult1  == 0);
        CHECK(prodResult2 == -315);
        CHECK(sumResult2  == 9);
    }

    SUBCASE("Test_Expression1")
    {
        const auto expr1 = -(3 * vecS + 8 * asType<int>(vecD) - 3) / 2;
        const auto expr2 = trans(expr1);
        const DynamicVector<int, true> expr3(expr2);

        CHECK(expr1[0] ==   6); CHECK(expr2[0] ==   6); CHECK(expr3[0] ==   6);
        CHECK(expr1[1] == -37); CHECK(expr2[1] == -37); CHECK(expr3[1] == -37);
        CHECK(expr1[2] ==  -5); CHECK(expr2[2] ==  -5); CHECK(expr3[2] ==  -5);
        
        CHECK(expr1.transposeFlag == false);
        CHECK(expr2.transposeFlag == true);
        CHECK(expr3.transposeFlag == true);
    }

    SUBCASE("Test_Expression2")
    {
        using VectorType = StaticVector<double, 5>;

        const VectorType v1{ { 5, 3, 2, 6, 9 } };
        const VectorType v2{ { 7, 2, 9, 5, 1 } };

        CHECK(v1[0] == 5);
        CHECK(v1[1] == 3);
        CHECK(v1[2] == 2);
        CHECK(v1[3] == 6);
        CHECK(v1[4] == 9);

        const VectorType expr1 = v1 + v2;
        const VectorType vecTrue1{ {12, 5, 11, 11, 10} };
        CHECK(expr1.size() == 5);
        CHECK(expr1 == vecTrue1);
        CHECK(!(expr1 != vecTrue1));

        const auto expr2 = 4 * ((-v1 + v2 / 8.) * 10 - v1);
        const VectorType vecTrue2{ { -185, -122, -43, -239, -391 } };
        CHECK(expr2.size() == 5);
        CHECK(expr2 == vecTrue2);
        CHECK(!(expr2 != vecTrue2));

        const auto expr3 = (-v1 * v2 / 2. + (v1 - 5.) / v2 - v1) * 30 + 600;
        const VectorType vecTrue3{ { -75, 390, 260, -24, 315 } };
        CHECK(expr3.size() == 5);
        CHECK(expr3 == vecTrue3);
        CHECK(!(expr3 != vecTrue3));
    }
}
