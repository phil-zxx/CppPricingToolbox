#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Vector_AlgebraicOp_SumProd")
{
    const StaticVector<int, 10> vecS = { 5,7,-9 };
    const DynamicVector<double> vecD = { -3,7,5 };

    const auto sumResult1  = sum(DynamicVector<int>());
    const auto sumResult2  = sum(vecD);
    const auto prodResult1 = prod(StaticVector<int, 10>());
    const auto prodResult2 = prod(vecS);

    CHECK(sumResult1  == 0);
    CHECK(sumResult2  == 9);
    CHECK(prodResult1 == 1);
    CHECK(prodResult2 == -315);
}
