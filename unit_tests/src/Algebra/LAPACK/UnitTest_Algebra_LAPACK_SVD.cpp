#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/SingularValueDecomp.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_LAPACK_SVD")
{
    const DynamicMatrix<double> matD{ {5,7},{1,3} };
    const SingularValueDecomp svd(matD);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {0.942367762637354, 0.334578839650489},{0.334578839650489, -0.942367762637354} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {0.553146906319590, 0.833083729302803},{0.833083729302803, -0.553146906319590} });
    CHECK(svd.singularValues == DynamicVector<double>{ 9.12310562561766, 0.876894374382339 });
    CHECK(svd.invertedMatrix == DynamicMatrix<double>{ {0.375,-0.875},{-0.125,0.625} });

    const auto sol = svd.solve({10,-6});
    CHECK(sol == DynamicVector<double>{ 9,-5 });
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD_Null1")
{
    const DynamicMatrix<double> matD{ {0,0},{0,0} };
    const SingularValueDecomp svd(matD);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.singularValues == DynamicVector<double>{ 0, 0 });
    CHECK(svd.invertedMatrix == DynamicVector<double>());

    CHECK_THROWS(svd.solve({ 1,2 }));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD_Null2")
{
    const DynamicMatrix<double> matD{ {-5,0},{0,0} };
    const SingularValueDecomp svd(matD);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {-1, 0},{0, 1} });
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {1, 0},{0, 1} });
    CHECK(svd.singularValues == DynamicVector<double>{ 5, 0 });
    CHECK(svd.invertedMatrix == DynamicVector<double>());

    CHECK_THROWS(svd.solve({ 1,2 }));
}

TEST_CASE("UnitTest_Algebra_LAPACK_SVD_Null3")
{
    const DynamicMatrix<double> matD{ {0,2},{2,0} };
    const SingularValueDecomp svd(matD);

    CHECK(svd.matrixU        == DynamicMatrix<double>{ {1, 1},{1, -1} } / std::sqrt(2));
    CHECK(svd.matrixV        == DynamicMatrix<double>{ {1, -1},{1, 1} } / std::sqrt(2));
    CHECK(svd.singularValues == DynamicVector<double>{ 2, 2 });
    CHECK(svd.invertedMatrix == DynamicMatrix<double>{ {0,0.5},{0.5,0} });

    const auto sol = svd.solve({ 12,8 });
    CHECK(sol == DynamicVector<double>{ 4,6 });
}
