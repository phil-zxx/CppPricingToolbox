#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>
#include <toolbox/Algebra/LAPACK/SingularValueDecomp.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Algebra_LAPACK_SVD")
{
    const DynamicMatrix<double> matD{ {5,7},{1,3} };

    const SingularValueDecomp svd(matD);

    CHECK(svd.matrixU == DynamicMatrix<double>{{0.942367762637354,0.334578839650489},{0.334578839650489,-0.942367762637354}});
    CHECK(svd.matrixV == DynamicMatrix<double>{{0.553146906319590,0.833083729302803},{0.833083729302803,-0.553146906319590}});
    CHECK(svd.singularValues == DynamicVector<double>{9.12310562561766,0.876894374382339});
}
