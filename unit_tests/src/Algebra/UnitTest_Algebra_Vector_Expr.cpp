#include <catch2/catch_test_macros.hpp>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;

TEST_CASE("UnitTest_Vector_Expressions")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    SECTION("Test_Type")
    {
        const auto expr1 = vecS;
        const auto expr2 = trans(vecS);
        const auto expr3 = vecS + 3;

        CHECK(std::string(typeid(expr1).name()) == "class Toolbox::DenseVector<int,10,0>");
        CHECK(std::string(typeid(expr2).name()) == "class Toolbox::MatrixExprTrans<struct Toolbox::OperatorId<void>,class Toolbox::DenseVector<int,10,0>,1>");
        CHECK(std::string(typeid(expr3).name()) == "class Toolbox::MatrixExpr<struct Toolbox::OperatorAdd,class Toolbox::DenseVector<int,10,0>,int,0>");
    }

    SECTION("Test_Expression1")
    {
        const auto expr1 = -(3 * vecS + 8 * asType<int>(vecD) - 3) / 2;
        const auto expr2 = trans(expr1);
        const DynamicVector<int, true> expr3(expr2);
        const DynamicVector<int, true> expr4(trans(expr2));

        CHECK(expr1[0] ==   6); CHECK(expr2[0] ==   6); CHECK(expr3[0] ==   6);
        CHECK(expr1[1] == -37); CHECK(expr2[1] == -37); CHECK(expr3[1] == -37);
        CHECK(expr1[2] ==  -5); CHECK(expr2[2] ==  -5); CHECK(expr3[2] ==  -5);

        CHECK(expr1.rowCount() == 3);
        CHECK(expr1.colCount() == 1);
        CHECK(expr1.size()     == 3);
        CHECK(expr1(0, 0)      == 6);
        CHECK(expr1(1, 0)      == -37);
        CHECK(expr1(2, 0)      == -5);
        CHECK_NOTHROW(expr1(1, 0));
        CHECK_THROWS (expr1(0, 1));

        CHECK(expr2.rowCount() == 1);
        CHECK(expr2.colCount() == 3);
        CHECK(expr2.size()     == 3);
        CHECK(expr2(0, 0)      == 6);
        CHECK(expr2(0, 1)      == -37);
        CHECK(expr2(0, 2)      == -5);
        CHECK_NOTHROW(expr2(0, 1));
        CHECK_THROWS (expr2(1, 0));

        CHECK(expr3.rowCount() == 1);
        CHECK(expr3.colCount() == 3);
        CHECK(expr3.size()     == 3);
        CHECK(expr3(0, 0)      == 6);
        CHECK(expr3(0, 1)      == -37);
        CHECK(expr3(0, 2)      == -5);
        CHECK_NOTHROW(expr3(0, 1));
        CHECK_THROWS (expr3(1, 0));

        CHECK(expr4.rowCount() == 3);
        CHECK(expr4.colCount() == 1);
        CHECK(expr4.size()     == 3);
        CHECK(expr4(0, 0)      == 6);
        CHECK(expr4(1, 0)      == -37);
        CHECK(expr4(2, 0)      == -5);
        CHECK_NOTHROW(expr4(1, 0));
        CHECK_THROWS (expr4(0, 1));
    }

    SECTION("Test_Expression2")
    {
        using VectorType = StaticVector<double, 5>;

        const VectorType v1 = { 5, 3, 2, 6, 9 };
        const VectorType v2 = { 7, 2, 9, 5, 1 };

        CHECK(v1[0] == 5);
        CHECK(v1[1] == 3);
        CHECK(v1[2] == 2);
        CHECK(v1[3] == 6);
        CHECK(v1[4] == 9);

        const VectorType expr1 = v1 + v2;
        const VectorType vecTrue1 = {12, 5, 11, 11, 10};
        CHECK(expr1.size() == 5);
        CHECK(expr1 == vecTrue1);
        CHECK(!(expr1 != vecTrue1));

        const auto expr2 = 4 * ((-v1 + v2 / 8.) * 10 - v1);
        const VectorType vecTrue2 = { -185, -122, -43, -239, -391 };
        CHECK(expr2.size() == 5);
        CHECK((expr2 == vecTrue2));
        CHECK(!(expr2 != vecTrue2));

        const auto expr3 = (-v1 * v2 / 2. + (v1 - 5.) / v2 - v1) * 30 + 600;
        const VectorType vecTrue3 = { -75, 390, 260, -24, 315 };
        CHECK(expr3.size() == 5);
        CHECK(expr3 == vecTrue3);
        CHECK(!(expr3 != vecTrue3));
    }
}
