#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Basics_InitMat_Static")
{
    const StaticMatrix<double, 9, 2> mat1;
    const StaticMatrix<double, 8, 3> mat2(4, 2);
    const StaticMatrix<double, 7, 4> mat3(5, 4, 9);
    const StaticMatrix<double, 6, 5> mat4{ {7,8,9},{1,4,5} };

    CHECK(mat1.capacity() == 18);
    CHECK(mat1.rowCount() == 0);
    CHECK(mat1.colCount() == 0);
    CHECK(mat1.size()     == 0);
    CHECK(mat1.shape()    == MatrixShape(0, 0));
    CHECK_THROWS(mat1.at(0));

    CHECK(mat2.capacity() == 24);
    CHECK(mat2.rowCount() == 4);
    CHECK(mat2.colCount() == 2);
    CHECK(mat2.size()     == 8);
    CHECK(mat2.shape()    == MatrixShape(4, 2));
    CHECK_NOTHROW(mat2.at(7));
    CHECK_THROWS (mat2.at(8));

    CHECK(mat3.capacity() == 28);
    CHECK(mat3.rowCount() == 5);
    CHECK(mat3.colCount() == 4);
    CHECK(mat3.size()     == 20);
    CHECK(mat3.shape()    == MatrixShape(5, 4));
    CHECK(mat3[0]         == 9);
    CHECK(mat3[3]         == 9);
    CHECK(mat3[6]         == 9);
    CHECK(mat3[9]         == 9);
    CHECK(mat3[19]        == 9);
    CHECK(mat3(0, 0)      == 9);
    CHECK(mat3(0, 1)      == 9);
    CHECK(mat3(1, 2)      == 9);
    CHECK(mat3(2, 0)      == 9);
    CHECK(mat3(3, 1)      == 9);
    CHECK(mat3(4, 3)      == 9);
    CHECK_NOTHROW(mat3.at(19));
    CHECK_THROWS (mat3.at(20));
    CHECK_NOTHROW(mat3(4, 3));
    CHECK_THROWS (mat3(4, 4));
    CHECK_THROWS (mat3(5, 3));

    CHECK(mat4.capacity() == 30);
    CHECK(mat4.rowCount() == 2);
    CHECK(mat4.colCount() == 3);
    CHECK(mat4.size()     == 6);
    CHECK(mat4.shape()    == MatrixShape(2, 3));
    CHECK(mat4[0]         == 7);
    CHECK(mat4[1]         == 8);
    CHECK(mat4[2]         == 9);
    CHECK(mat4[3]         == 1);
    CHECK(mat4[4]         == 4);
    CHECK(mat4[5]         == 5);
    CHECK(mat4(0, 0)      == 7);
    CHECK(mat4(0, 1)      == 8);
    CHECK(mat4(0, 2)      == 9);
    CHECK(mat4(1, 0)      == 1);
    CHECK(mat4(1, 1)      == 4);
    CHECK(mat4(1, 2)      == 5);
    CHECK_NOTHROW(mat4.at(5));
    CHECK_THROWS (mat4.at(6));
    CHECK_NOTHROW(mat4(1, 2));
    CHECK_THROWS (mat4(2, 2));
    CHECK_THROWS (mat4(1, 3));
}

TEST_CASE("UnitTest_Algebra_Basics_InitMat_Dynamic")
{
    const DynamicMatrix<double> mat1;
    const DynamicMatrix<double> mat2(4, 2);
    const DynamicMatrix<double> mat3(5, 4, 9);
    const DynamicMatrix<double> mat4{ {7,8,9},{1,4,5} };

    CHECK(mat1.capacity() == 0);
    CHECK(mat1.rowCount() == 0);
    CHECK(mat1.colCount() == 0);
    CHECK(mat1.size()     == 0);
    CHECK(mat1.shape()    == MatrixShape(0, 0));
    CHECK_THROWS(mat1.at(0));

    CHECK(mat2.capacity() == 8);
    CHECK(mat2.rowCount() == 4);
    CHECK(mat2.colCount() == 2);
    CHECK(mat2.size()     == 8);
    CHECK(mat2.shape()    == MatrixShape(4, 2));
    CHECK_NOTHROW(mat2.at(7));
    CHECK_THROWS (mat2.at(8));

    CHECK(mat3.capacity() == 20);
    CHECK(mat3.rowCount() == 5);
    CHECK(mat3.colCount() == 4);
    CHECK(mat3.size()     == 20);
    CHECK(mat3.shape()    == MatrixShape(5, 4));
    CHECK(mat3[0]         == 9);
    CHECK(mat3[3]         == 9);
    CHECK(mat3[6]         == 9);
    CHECK(mat3[9]         == 9);
    CHECK(mat3[19]        == 9);
    CHECK(mat3(0, 0)      == 9);
    CHECK(mat3(0, 1)      == 9);
    CHECK(mat3(0, 2)      == 9);
    CHECK(mat3(1, 0)      == 9);
    CHECK(mat3(1, 1)      == 9);
    CHECK(mat3(4, 3)      == 9);
    CHECK_NOTHROW(mat3.at(19));
    CHECK_THROWS (mat3.at(20));
    CHECK_NOTHROW(mat3(4, 3));
    CHECK_THROWS (mat3(4, 4));
    CHECK_THROWS (mat3(5, 3));

    CHECK(mat4.capacity() == 6);
    CHECK(mat4.rowCount() == 2);
    CHECK(mat4.colCount() == 3);
    CHECK(mat4.size()     == 6);
    CHECK(mat4.shape()    == MatrixShape(2, 3));
    CHECK(mat4[0]         == 7);
    CHECK(mat4[1]         == 8);
    CHECK(mat4[2]         == 9);
    CHECK(mat4[3]         == 1);
    CHECK(mat4[4]         == 4);
    CHECK(mat4[5]         == 5);
    CHECK(mat4(0, 0)      == 7);
    CHECK(mat4(0, 1)      == 8);
    CHECK(mat4(0, 2)      == 9);
    CHECK(mat4(1, 0)      == 1);
    CHECK(mat4(1, 1)      == 4);
    CHECK(mat4(1, 2)      == 5);
    CHECK_NOTHROW(mat4.at(5));
    CHECK_THROWS (mat4.at(6));
    CHECK_NOTHROW(mat4(1, 2));
    CHECK_THROWS (mat4(2, 2));
    CHECK_THROWS (mat4(1, 3));
}

TEST_CASE("UnitTest_Algebra_Basics_InitMat_List")
{
    const StaticMatrix<double, 3, 4> matS{ {7,5,25,11},{9,4,7,2} };
    const DynamicMatrix<int> matD{ {6,3},{-3,6},{-32,8},{99,100} };

    CHECK(matS.capacity() == 12);
    CHECK(matS.rowCount() == 2);
    CHECK(matS.colCount() == 4);
    CHECK(matS.size()     == 8);
    CHECK(matS.shape()    == MatrixShape(2, 4));
    CHECK(matS[0]         == 7);
    CHECK(matS[1]         == 5);
    CHECK(matS[2]         == 25);
    CHECK(matS.at(3)      == 11);
    CHECK(matS[4]         == 9);
    CHECK(matS.at(5)      == 4);
    CHECK(matS.at(6)      == 7);
    CHECK(matS.at(7)      == 2);
    CHECK(matS(0, 0)      == 7);
    CHECK(matS(0, 1)      == 5);
    CHECK(matS(0, 2)      == 25);
    CHECK(matS(0, 3)      == 11);
    CHECK(matS(1, 0)      == 9);
    CHECK(matS(1, 1)      == 4);
    CHECK(matS(1, 2)      == 7);
    CHECK(matS(1, 3)      == 2);
    CHECK_THROWS (matS.at(8));
    CHECK_THROWS (matS.at(9));
    CHECK_NOTHROW(matS(1, 3));
    CHECK_THROWS (matS(2, 3));
    CHECK_THROWS (matS(1, 4));

    CHECK(matD.capacity() == 8);
    CHECK(matD.rowCount() == 4);
    CHECK(matD.colCount() == 2);
    CHECK(matD.size()     == 8);
    CHECK(matD.shape()    == MatrixShape(4, 2));
    CHECK(matD[0]         ==   6);
    CHECK(matD[1]         ==   3);
    CHECK(matD[2]         ==  -3);
    CHECK(matD.at(3)      ==   6);
    CHECK(matD.at(4)      == -32);
    CHECK(matD[5]         ==   8);
    CHECK(matD[6]         ==  99);
    CHECK(matD.at(7)      == 100);
    CHECK(matD(0, 0)      ==   6);
    CHECK(matD(0, 1)      ==   3);
    CHECK(matD(1, 0)      ==  -3);
    CHECK(matD(1, 1)      ==   6);
    CHECK(matD(2, 0)      == -32);
    CHECK(matD(2, 1)      ==   8);
    CHECK(matD(3, 0)      ==  99);
    CHECK(matD(3, 1)      == 100);
    CHECK_THROWS (matD.at(8));
    CHECK_THROWS (matD.at(9));
    CHECK_NOTHROW(matD(3, 1));
    CHECK_THROWS (matD(4, 1));
    CHECK_THROWS (matD(3, 2));
}

TEST_CASE("UnitTest_Algebra_Basics_InitMat_Throw")
{
    CHECK_NOTHROW(StaticMatrix<int, 3, 2>(1, 1));
    CHECK_NOTHROW(StaticMatrix<int, 3, 2>(2, 2));
    CHECK_NOTHROW(StaticMatrix<int, 3, 2>(3, 2));
    CHECK_THROWS (StaticMatrix<int, 3, 2>(4, 1));
    CHECK_THROWS (StaticMatrix<int, 9, 5>(9, 6));
    CHECK_NOTHROW(StaticMatrix<int, 2, 4>{ {3,4,5,6},{3,4,5,6} });
    CHECK_THROWS (StaticMatrix<int, 2, 4>{ {3,4,5,6},{3,4,5,6},{3,4,5,6} });
    CHECK_NOTHROW(StaticMatrix<double, 3, 3>{ {3, 5, 2}, { 6,4,9 } });
    CHECK_NOTHROW(StaticMatrix<double, 2, 3>{ {3, 5, 2}, { 6,4,9 } });
    CHECK_THROWS (StaticMatrix<double, 3, 2>{ {3, 5, 2}, { 6,4,9 } });

    const size_t N = static_cast<size_t>(-1);
    CHECK_THROWS (DynamicMatrix<int>(N, 1));
    CHECK_THROWS (DynamicMatrix<int>(N, 1, 99));
    CHECK_NOTHROW(DynamicMatrix<int>{ {1,2,3,4},{5,6,7,8} });
    CHECK_THROWS (DynamicMatrix<int>{ {1,2,3,4},{5,6,7} });
}
