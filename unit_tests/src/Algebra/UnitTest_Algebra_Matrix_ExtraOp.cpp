#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Matrix_isSquare_isSymmetric")
{
    const DynamicMatrix<double> mat1 = { {1,2,3},{2,9,4},{3,3.99999999,8} };
    const DynamicMatrix<double> mat2 = { {1,2,3},{2,9,4},{3,4,8} };
    const DynamicMatrix<double> mat3 = { {1,2,3},{2,9,4} };

    CHECK(  mat1 == mat1);
    CHECK(!(mat1 != mat1));
    CHECK(  mat1 != mat2);
    CHECK(!(mat1 == mat2));

    CHECK(isSquare(mat1) == true);
    CHECK(isSquare(mat2) == true);
    CHECK(isSquare(mat3) == false);
    CHECK(isSymmetric(mat1) == false);
    CHECK(isSymmetric(mat2) == true);
    CHECK(isSymmetric(mat3) == false);
}

TEST_CASE("UnitTest_Matrix_Operator+-*/=")
{
    DynamicMatrix<int> mat = { {1,2},{3,4} };
    mat += mat;

    CHECK(mat(0, 0) == 2);
    CHECK(mat(0, 1) == 4);
    CHECK(mat(1, 0) == 6);
    CHECK(mat(1, 1) == 8);
    CHECK(mat == DynamicMatrix<int>{{2,4},{6,8}});

    const auto expr = trans(4 * (mat * mat) - 50);
    CHECK(expr(0, 0) == -34);
    CHECK(expr(0, 1) ==  94);
    CHECK(expr(1, 0) ==  14);
    CHECK(expr(1, 1) == 206);
    CHECK(expr == DynamicMatrix<int>{{-34, 94},{ 14, 206 }});

    mat += expr;
    mat += 5;
    CHECK(mat(0, 0) == -27);
    CHECK(mat(0, 1) == 103);
    CHECK(mat(1, 0) ==  25);
    CHECK(mat(1, 1) == 219);
    CHECK(mat == DynamicMatrix<int>{{-27, 103},{ 25, 219 }});

    mat -= (mat * mat);
    mat -= -5000;
    CHECK(mat(0, 0) ==  4244);
    CHECK(mat(0, 1) == -5506);
    CHECK(mat(1, 0) ==  4400);
    CHECK(mat(1, 1) == -42742);
    CHECK(mat == DynamicMatrix<int>{{4244, -5506},{ 4400, -42742 }});

    mat /= {{1061, 2753},{ 22, 3053 }};
    mat /= 2;
    CHECK(mat(0, 0) ==    2);
    CHECK(mat(0, 1) ==   -1);
    CHECK(mat(1, 0) ==  100);
    CHECK(mat(1, 1) ==   -7);
    CHECK(mat == DynamicMatrix<int>{ {2, -1}, { 100, -7 }});
}
