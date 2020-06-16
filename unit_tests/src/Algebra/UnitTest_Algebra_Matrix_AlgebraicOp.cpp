#include <catch2/catch_test_macros.hpp>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Matrix_AlgebraicOp_Trans")
{
    const DynamicMatrix<double> mat = { {1,2,3},{2,9,4} };
    const auto matT = trans(mat);

    CHECK(mat.rowCount()  == 2);
    CHECK(mat.colCount()  == 3);
    CHECK(matT.rowCount() == 3);
    CHECK(matT.colCount() == 2);

    CHECK(mat(0, 0) == matT(0, 0));
    CHECK(mat(0, 1) == matT(1, 0));
    CHECK(mat(0, 2) == matT(2, 0));
    CHECK(mat(1, 0) == matT(0, 1));
    CHECK(mat(1, 1) == matT(1, 1));
    CHECK(mat(1, 2) == matT(2, 1));
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_AsType")
{
    const DynamicMatrix<double> mat = { {1.1, 2.2 ,3.3},{4.4, 5.5, 6.6} };
    const auto matI = asType<int>(mat);

    CHECK(mat.rowCount()  == 2);
    CHECK(mat.colCount()  == 3);
    CHECK(matI.rowCount() == 2);
    CHECK(matI.colCount() == 3);

    CHECK(matI(0, 0) == 1);
    CHECK(matI(0, 1) == 2);
    CHECK(matI(0, 2) == 3);
    CHECK(matI(1, 0) == 4);
    CHECK(matI(1, 1) == 5);
    CHECK(matI(1, 2) == 6);
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_Abs")
{
    const DynamicMatrix<int> mat = { {-1, 2},{3, -4},{-5,6},{-7,8} };
    const auto matA = abs(mat);

    CHECK(mat.rowCount()  == 4);
    CHECK(mat.colCount()  == 2);
    CHECK(matA.rowCount() == 4);
    CHECK(matA.colCount() == 2);

    CHECK(mat(0, 0) == -1); CHECK(matA(0, 0) == 1);
    CHECK(mat(0, 1) ==  2); CHECK(matA(0, 1) == 2);
    CHECK(mat(1, 0) ==  3); CHECK(matA(1, 0) == 3);
    CHECK(mat(1, 1) == -4); CHECK(matA(1, 1) == 4);
    CHECK(mat(2, 0) == -5); CHECK(matA(2, 0) == 5);
    CHECK(mat(2, 1) ==  6); CHECK(matA(2, 1) == 6);
    CHECK(mat(3, 0) == -7); CHECK(matA(3, 0) == 7);
    CHECK(mat(3, 1) ==  8); CHECK(matA(3, 1) == 8);
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_Sqrt")
{
    const DynamicMatrix<int> mat = { {-1,4},{9,-4},{-5,36}};
    const auto matS = sqrt(mat);

    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(matS.rowCount() == 3);
    CHECK(matS.colCount() == 2);

    CHECK(mat(0, 0) == -1); CHECK(std::isnan(matS(0, 0)));
    CHECK(mat(0, 1) ==  4); CHECK(matS(0, 1) == 2);
    CHECK(mat(1, 0) ==  9); CHECK(matS(1, 0) == 3);
    CHECK(mat(1, 1) == -4); CHECK(std::isnan(matS(1, 1)));
    CHECK(mat(2, 0) == -5); CHECK(std::isnan(matS(2, 0)));
    CHECK(mat(2, 1) == 36); CHECK(matS(2, 1) == 6);
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_Cbrt")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matC = cbrt(mat);

    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(matC.rowCount() == 3);
    CHECK(matC.colCount() == 2);

    CHECK(mat(0, 0) ==   -1); CHECK(matC(0, 0) == -1);
    CHECK(mat(0, 1) ==    8); CHECK(matC(0, 1) ==  2);
    CHECK(mat(1, 0) ==   27); CHECK(matC(1, 0) ==  3);
    CHECK(mat(1, 1) ==   -8); CHECK(matC(1, 1) == -2);
    CHECK(mat(2, 0) == -125); CHECK(matC(2, 0) == -5);
    CHECK(mat(2, 1) ==  216); CHECK(matC(2, 1) ==  6);
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_Squared")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matS = squared(mat);

    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(matS.rowCount() == 3);
    CHECK(matS.colCount() == 2);

    CHECK(mat(0, 0) ==   -1); CHECK(matS(0, 0) ==     1);
    CHECK(mat(0, 1) ==    8); CHECK(matS(0, 1) ==    64);
    CHECK(mat(1, 0) ==   27); CHECK(matS(1, 0) ==   729);
    CHECK(mat(1, 1) ==   -8); CHECK(matS(1, 1) ==    64);
    CHECK(mat(2, 0) == -125); CHECK(matS(2, 0) == 15625);
    CHECK(mat(2, 1) ==  216); CHECK(matS(2, 1) == 46656);
}

TEST_CASE("UnitTest_Matrix_AlgebraicOp_Power")
{
    const DynamicMatrix<int> mat = { {-1,8},{27,-8},{-125,216}};
    const auto matS = power(mat, 3);

    CHECK(mat.rowCount()  == 3);
    CHECK(mat.colCount()  == 2);
    CHECK(matS.rowCount() == 3);
    CHECK(matS.colCount() == 2);

    CHECK(mat(0, 0) ==   -1); CHECK(matS(0, 0) ==       -1);
    CHECK(mat(0, 1) ==    8); CHECK(matS(0, 1) ==      512);
    CHECK(mat(1, 0) ==   27); CHECK(matS(1, 0) ==    19683);
    CHECK(mat(1, 1) ==   -8); CHECK(matS(1, 1) ==     -512);
    CHECK(mat(2, 0) == -125); CHECK(matS(2, 0) == -1953125);
    CHECK(mat(2, 1) ==  216); CHECK(matS(2, 1) == 10077696);
}
