#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Func_IsSquareSymm")
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
