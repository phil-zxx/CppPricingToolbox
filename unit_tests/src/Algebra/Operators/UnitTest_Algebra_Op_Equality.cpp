#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_Op_Equality1")
{
    DynamicMatrix<double> mat1   = { {1,2},{3,4} };
    StaticMatrix<int, 5, 5> mat2 = { {1,2},{3,4} };

    // Matrices should be equal
    CHECK(mat1 == mat2);
    CHECK(mat2 == mat1);
    CHECK(!(mat1 != mat2));
    CHECK(!(mat2 != mat1));
}

TEST_CASE("UnitTest_Algebra_Op_Equality2")
{
    DynamicMatrix<double> mat1 = { {1,2,3} };
    DynamicMatrix<double> mat2 = { {1},{2},{3} };
    DynamicMatrix<double> mat3 = trans(mat2);

    // Matrices should NOT be equal
    CHECK(mat1 != mat2);
    CHECK(mat2 != mat1);
    CHECK(!(mat1 == mat2));
    CHECK(!(mat2 == mat1));

    // Matrices should be equal
    CHECK(mat1 == mat3);
    CHECK(mat3 == mat1);
    CHECK(!(mat1 != mat3));
    CHECK(!(mat3 != mat1));
}

TEST_CASE("UnitTest_Algebra_Op_Equality3")
{
    DynamicMatrix<double> mat1, mat2;

    // Matrices should be equal
    CHECK(mat1 == mat2);
    CHECK(mat2 == mat1);
    CHECK(!(mat1 != mat2));
    CHECK(!(mat2 != mat1));
}

TEST_CASE("UnitTest_Algebra_Op_Equality4")
{
    DynamicMatrix<double> mat1 = { {9,3,4},{2,5,33} };
    DynamicMatrix<double> mat2 = { {9,3},{4,2},{5,33} };

    // Matrices should NOT be equal
    CHECK(mat1 != mat2);
    CHECK(mat2 != mat1);
    CHECK(!(mat1 == mat2));
    CHECK(!(mat2 == mat1));
}

TEST_CASE("UnitTest_Algebra_Op_Equality5")
{
    DynamicMatrix<double> mat = { {9},{3},{-4},{8} };
    StaticVector<int, 5> vec  = { {9,3,-4,8} };

    // Matrix & Vector should be equal
    CHECK(mat == vec);
    CHECK(vec == mat);
    CHECK(!(mat != vec));
    CHECK(!(vec != mat));
}
