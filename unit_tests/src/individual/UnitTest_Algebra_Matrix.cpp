#include <toolbox/Algebra/VectorMatrix.hpp>
#include <catch2/catch.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Matrix_BaseFunctions")
{
    const StaticMatrix<double, 3, 3> matS{ {3,5,2},{6,4,9} };
    const DynamicMatrix<double> matD{ {5,7},{-1,3},{-8, 2},{-2, -4} };

    CHECK(matS.capacity() == 9);
    CHECK(matS.size()     == 6);
    CHECK(matS.rowCount() == 2);
    CHECK(matS.colCount() == 3);
    CHECK(matS[0]         == 3.);
    CHECK(matS[1]         == 5.);
    CHECK(matS[2]         == 2.);
    CHECK(matS[3]         == 6.);
    CHECK(matS[4]         == 4.);
    CHECK(matS[5]         == 9.);
    CHECK(matS(0, 0)      == 3.);
    CHECK(matS(0, 1)      == 5.);
    CHECK(matS(0, 2)      == 2.);
    CHECK(matS(1, 0)      == 6.);
    CHECK(matS(1, 1)      == 4.);
    CHECK(matS(1, 2)      == 9.);

    CHECK(matD.capacity() == 8);
    CHECK(matD.size()     == 8);
    CHECK(matD.rowCount() == 4);
    CHECK(matD.colCount() == 2);
    CHECK(matD[0]         ==  5.);
    CHECK(matD[1]         ==  7.);
    CHECK(matD[2]         == -1.);
    CHECK(matD[3]         ==  3.);
    CHECK(matD[4]         == -8.);
    CHECK(matD[5]         ==  2.);
    CHECK(matD[6]         == -2.);
    CHECK(matD(0, 0)      ==  5.);
    CHECK(matD(0, 1)      ==  7.);
    CHECK(matD(1, 0)      == -1.);
    CHECK(matD(1, 1)      ==  3.);
    CHECK(matD(2, 0)      == -8.);
    CHECK(matD(2, 1)      ==  2.);
    CHECK(matD(3, 0)      == -2.);
    CHECK(matD(3, 1)      == -4.);
}


TEST_CASE("UnitTest_Matrix_StorageOrder")
{
    const StaticMatrix<double, 3, 2, false> mat1{ {3,5,2},{6,4,9} };
    const StaticMatrix<double, 3, 2, true>  mat2{ {3,5,2},{6,4,9} };

    CHECK(mat1.capacity() == 6.);
    CHECK(mat1.size()     == 6.);
    CHECK(mat1.rowCount() == 2.);
    CHECK(mat1.colCount() == 3.);
    CHECK(mat1[0]         == 3.);
    CHECK(mat1[1]         == 5.);
    CHECK(mat1[2]         == 2.);
    CHECK(mat1[3]         == 6.);
    CHECK(mat1[4]         == 4.);
    CHECK(mat1[5]         == 9.);

    CHECK(mat2.capacity() == 6.);
    CHECK(mat2.size()     == 6.);
    CHECK(mat2.rowCount() == 2.);
    CHECK(mat2.colCount() == 3.);
    CHECK(mat2[0]         == 3.);
    CHECK(mat2[1]         == 6.);
    CHECK(mat2[2]         == 5.);
    CHECK(mat2[3]         == 4.);
    CHECK(mat2[4]         == 2.);
    CHECK(mat2[5]         == 9.);
}
