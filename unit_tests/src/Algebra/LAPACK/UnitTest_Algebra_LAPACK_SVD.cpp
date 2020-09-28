#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/SingularValueDecomp.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_LAPACK_SVD1")
{
    const DynamicMatrix<double> mat{ {5,7},{1,3} };
    const SingularValueDecomp svd(mat);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {0.942367762637354, 0.334578839650489},{0.334578839650489, -0.942367762637354} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {0.553146906319590, 0.833083729302803},{0.833083729302803, -0.553146906319590} });
    CHECK(svd.singularValues == DynamicVector<double>{ 9.12310562561766, 0.876894374382339 });
    CHECK(svd.invertedMatrix == DynamicMatrix<double>{ {0.375,-0.875},{-0.125,0.625} });

    const auto sol = svd.solve({ 10,-6 });
    CHECK(sol == DynamicVector<double>{ 9,-5 });
    CHECK(mult(svd.invertedMatrix, mat) == IdentityMatrix<int>(mat.colCount()));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD2")
{
    const StaticMatrix<double, 3, 3> mat{ {0,0,0.1},{0,0.4,0},{0.5,0,0} };
    const SingularValueDecomp svd(mat);

    CHECK(svd.matrixU        == StaticMatrix<double, 3, 3>{ {0,0,1},{0,1,0},{1,0,0} });
    CHECK(svd.matrixV        == StaticMatrix<double, 3, 3>{ {1,0,0},{0,1,0},{0,0,1} });
    CHECK(svd.invertedMatrix == StaticMatrix<double, 3, 3>{ {0,0,2},{0,2.5,0},{10,0,0} });
    CHECK(svd.singularValues == StaticVector<double, 3>{ 0.5, 0.4, 0.1 });

    const auto sol = svd.solve({ 3,-2,10 });
    CHECK(sol == DynamicVector<double>{ 20,-5,30 });
    CHECK(mult(svd.invertedMatrix, mat) == IdentityMatrix<int>(mat.colCount()));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD3")
{
    const DynamicMatrix<double> mat{ {0,2},{2,0} };
    const SingularValueDecomp svd(mat);

    CHECK(svd.matrixU == DynamicMatrix<double>{ {1, 1}, { 1, -1 } } / std::sqrt(2));
    CHECK(svd.matrixV == DynamicMatrix<double>{ {1, -1}, { 1, 1 } } / std::sqrt(2));
    CHECK(svd.invertedMatrix == DynamicMatrix<double>{ {0, 0.5}, { 0.5,0 } });
    CHECK(svd.singularValues == DynamicVector<double>{ 2, 2 });

    const auto sol = svd.solve({ 12,8 });
    CHECK(sol == DynamicVector<double>{ 4, 6 });
    CHECK(mult(svd.invertedMatrix, mat) == IdentityMatrix<int>(mat.colCount()));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD_Null1")
{
    const DynamicMatrix<double> mat{ {0,0},{0,0} };
    const SingularValueDecomp svd(mat);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.invertedMatrix == DynamicVector<double>());
    CHECK(svd.singularValues == DynamicVector<double>{ 0, 0 });

    CHECK_THROWS(svd.solve({ 1,2 }));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD_Null2")
{
    const DynamicMatrix<double> mat{ {-5,0},{0,0} };
    const SingularValueDecomp svd(mat);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {-1, 0},{0, 1} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.invertedMatrix == DynamicVector<double>());
    CHECK(svd.singularValues == DynamicVector<double>{ 5, 0 });

    CHECK_THROWS(svd.solve({ 1,2 }));
}
