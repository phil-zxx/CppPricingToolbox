#include <doctest/doctest.h>
#include <toolbox/Algebra/VectorMatrix.hpp>

using namespace TB;


TEST_CASE("UnitTest_Algebra_Expr_AddMatVec1")
{
    const StaticMatrix<int, 3, 3> mat = { {5,7,-9},{4,2,3},{-8,6,1} };
    const DynamicVector<int> vec1     = { 11,55,99 };
    const DynamicVector<int> vec2     = { 15, 3, 44, -12 };

    const auto expr1 = mat + vec1;
    const auto expr2 = vec1 + mat;
    const auto expr3 = mat + trans(vec1);
    const auto expr4 = trans(vec1) + mat;

    CHECK(expr1 == DynamicMatrix<int>{ {16, 18,  2}, { 59, 57,  58 }, { 91, 105, 100 }});
    CHECK(expr2 == DynamicMatrix<int>{ {16, 18,  2}, { 59, 57,  58 }, { 91, 105, 100 }});
    CHECK(expr3 == DynamicMatrix<int>{ {16, 62, 90}, { 15, 57, 102 }, {  3,  61, 100 }});
    CHECK(expr4 == DynamicMatrix<int>{ {16, 62, 90}, { 15, 57, 102 }, {  3,  61, 100 }});

    CHECK(expr1.size()     == 9);
    CHECK(expr2.size()     == 9);
    CHECK(expr3.size()     == 9);
    CHECK(expr4.size()     == 9);
    CHECK(expr1.rowCount() == 3);
    CHECK(expr2.rowCount() == 3);
    CHECK(expr3.rowCount() == 3);
    CHECK(expr4.rowCount() == 3);
    CHECK(expr1.colCount() == 3);
    CHECK(expr2.colCount() == 3);
    CHECK(expr3.colCount() == 3);
    CHECK(expr4.colCount() == 3);
    CHECK(expr1.shape()    == MatrixShape(3, 3));
    CHECK(expr2.shape()    == MatrixShape(3, 3));
    CHECK(expr3.shape()    == MatrixShape(3, 3));
    CHECK(expr4.shape()    == MatrixShape(3, 3));

    CHECK(expr1[0] ==  16); CHECK(expr2[0] ==  16); CHECK(expr3[0] ==  16); CHECK(expr4[0] ==  16); 
    CHECK(expr1[1] ==  18); CHECK(expr2[1] ==  18); CHECK(expr3[1] ==  62); CHECK(expr4[1] ==  62); 
    CHECK(expr1[2] ==   2); CHECK(expr2[2] ==   2); CHECK(expr3[2] ==  90); CHECK(expr4[2] ==  90); 
    CHECK(expr1[3] ==  59); CHECK(expr2[3] ==  59); CHECK(expr3[3] ==  15); CHECK(expr4[3] ==  15); 
    CHECK(expr1[4] ==  57); CHECK(expr2[4] ==  57); CHECK(expr3[4] ==  57); CHECK(expr4[4] ==  57); 
    CHECK(expr1[5] ==  58); CHECK(expr2[5] ==  58); CHECK(expr3[5] == 102); CHECK(expr4[5] == 102); 
    CHECK(expr1[6] ==  91); CHECK(expr2[6] ==  91); CHECK(expr3[6] ==   3); CHECK(expr4[6] ==   3); 
    CHECK(expr1[7] == 105); CHECK(expr2[7] == 105); CHECK(expr3[7] ==  61); CHECK(expr4[7] ==  61); 
    CHECK(expr1[8] == 100); CHECK(expr2[8] == 100); CHECK(expr3[8] == 100); CHECK(expr4[8] == 100); 
    
    CHECK(expr1(0, 0) ==  16); CHECK(expr2(0, 0) ==  16); CHECK(expr3(0, 0) ==  16); CHECK(expr4(0, 0) ==  16); 
    CHECK(expr1(0, 1) ==  18); CHECK(expr2(0, 1) ==  18); CHECK(expr3(0, 1) ==  62); CHECK(expr4(0, 1) ==  62); 
    CHECK(expr1(0, 2) ==   2); CHECK(expr2(0, 2) ==   2); CHECK(expr3(0, 2) ==  90); CHECK(expr4(0, 2) ==  90); 
    CHECK(expr1(1, 0) ==  59); CHECK(expr2(1, 0) ==  59); CHECK(expr3(1, 0) ==  15); CHECK(expr4(1, 0) ==  15); 
    CHECK(expr1(1, 1) ==  57); CHECK(expr2(1, 1) ==  57); CHECK(expr3(1, 1) ==  57); CHECK(expr4(1, 1) ==  57); 
    CHECK(expr1(1, 2) ==  58); CHECK(expr2(1, 2) ==  58); CHECK(expr3(1, 2) == 102); CHECK(expr4(1, 2) == 102); 
    CHECK(expr1(2, 0) ==  91); CHECK(expr2(2, 0) ==  91); CHECK(expr3(2, 0) ==   3); CHECK(expr4(2, 0) ==   3); 
    CHECK(expr1(2, 1) == 105); CHECK(expr2(2, 1) == 105); CHECK(expr3(2, 1) ==  61); CHECK(expr4(2, 1) ==  61); 
    CHECK(expr1(2, 2) == 100); CHECK(expr2(2, 2) == 100); CHECK(expr3(2, 2) == 100); CHECK(expr4(2, 2) == 100); 

    CHECK_NOTHROW(mat  + vec1);
    CHECK_THROWS (mat  + vec2);
    CHECK_NOTHROW(vec1 + mat);
    CHECK_THROWS (vec2 + mat);
    CHECK_THROWS (vec2 + vec1);

    CHECK(-(vec1 / 11 + 2 * trans(mat) + mat - trans(vec1)) + 3 == DynamicMatrix<int>{ {-2, 42, 126}, { -9, 47, 82 }, { 31, 37, 90 }});
}

TEST_CASE("UnitTest_Algebra_Expr_AddMatVec2")
{
    const StaticMatrix<int, 3, 4> mat   = { {5, 7, -9, 11}, {4, 2, 3, 22}, {-8, 6, 1, 33} };
    const DynamicVector<int> vec1       = { 11, 55, -22 };
    const DynamicVector<int, true> vec2 = { 15, 3, 44, -12 };

    const auto expr1 = mat  + vec1;
    const auto expr2 = vec1 + mat;
    const auto expr3 = mat  + vec2;
    const auto expr4 = vec2 + mat;

    CHECK(expr1 == DynamicMatrix<int>{ {16, 18,  2, 22}, { 59, 57, 58, 77 }, { -30, -16, -21, 11 }});
    CHECK(expr2 == DynamicMatrix<int>{ {16, 18,  2, 22}, { 59, 57, 58, 77 }, { -30, -16, -21, 11 }});
    CHECK(expr3 == DynamicMatrix<int>{ {20, 10, 35, -1}, { 19,  5, 47, 10 }, {   7,   9,  45, 21 }});
    CHECK(expr4 == DynamicMatrix<int>{ {20, 10, 35, -1}, { 19,  5, 47, 10 }, {   7,   9,  45, 21 }});
    
    CHECK(expr1.size()     == 12);
    CHECK(expr2.size()     == 12);
    CHECK(expr3.size()     == 12);
    CHECK(expr4.size()     == 12);
    CHECK(expr1.rowCount() == 3);
    CHECK(expr2.rowCount() == 3);
    CHECK(expr3.rowCount() == 3);
    CHECK(expr4.rowCount() == 3);
    CHECK(expr1.colCount() == 4);
    CHECK(expr2.colCount() == 4);
    CHECK(expr3.colCount() == 4);
    CHECK(expr4.colCount() == 4);
    CHECK(expr1.shape()    == MatrixShape(3, 4));
    CHECK(expr2.shape()    == MatrixShape(3, 4));
    CHECK(expr3.shape()    == MatrixShape(3, 4));
    CHECK(expr4.shape()    == MatrixShape(3, 4));

    CHECK(expr1[ 0] ==  16); CHECK(expr2[ 0] ==  16); CHECK(expr3[ 0] == 20); CHECK(expr4[ 0] == 20); 
    CHECK(expr1[ 1] ==  18); CHECK(expr2[ 1] ==  18); CHECK(expr3[ 1] == 10); CHECK(expr4[ 1] == 10); 
    CHECK(expr1[ 2] ==   2); CHECK(expr2[ 2] ==   2); CHECK(expr3[ 2] == 35); CHECK(expr4[ 2] == 35); 
    CHECK(expr1[ 3] ==  22); CHECK(expr2[ 3] ==  22); CHECK(expr3[ 3] == -1); CHECK(expr4[ 3] == -1); 
    CHECK(expr1[ 4] ==  59); CHECK(expr2[ 4] ==  59); CHECK(expr3[ 4] == 19); CHECK(expr4[ 4] == 19); 
    CHECK(expr1[ 5] ==  57); CHECK(expr2[ 5] ==  57); CHECK(expr3[ 5] ==  5); CHECK(expr4[ 5] ==  5); 
    CHECK(expr1[ 6] ==  58); CHECK(expr2[ 6] ==  58); CHECK(expr3[ 6] == 47); CHECK(expr4[ 6] == 47); 
    CHECK(expr1[ 7] ==  77); CHECK(expr2[ 7] ==  77); CHECK(expr3[ 7] == 10); CHECK(expr4[ 7] == 10); 
    CHECK(expr1[ 8] == -30); CHECK(expr2[ 8] == -30); CHECK(expr3[ 8] ==  7); CHECK(expr4[ 8] ==  7); 
    CHECK(expr1[ 9] == -16); CHECK(expr2[ 9] == -16); CHECK(expr3[ 9] ==  9); CHECK(expr4[ 9] ==  9); 
    CHECK(expr1[10] == -21); CHECK(expr2[10] == -21); CHECK(expr3[10] == 45); CHECK(expr4[10] == 45); 
    CHECK(expr1[11] ==  11); CHECK(expr2[11] ==  11); CHECK(expr3[11] == 21); CHECK(expr4[11] == 21); 
    
    CHECK(expr1(0, 0) ==  16); CHECK(expr2(0, 0) ==  16); CHECK(expr3(0, 0) == 20); CHECK(expr4(0, 0) == 20); 
    CHECK(expr1(0, 1) ==  18); CHECK(expr2(0, 1) ==  18); CHECK(expr3(0, 1) == 10); CHECK(expr4(0, 1) == 10); 
    CHECK(expr1(0, 2) ==   2); CHECK(expr2(0, 2) ==   2); CHECK(expr3(0, 2) == 35); CHECK(expr4(0, 2) == 35); 
    CHECK(expr1(0, 3) ==  22); CHECK(expr2(0, 3) ==  22); CHECK(expr3(0, 3) == -1); CHECK(expr4(0, 3) == -1); 
    CHECK(expr1(1, 0) ==  59); CHECK(expr2(1, 0) ==  59); CHECK(expr3(1, 0) == 19); CHECK(expr4(1, 0) == 19); 
    CHECK(expr1(1, 1) ==  57); CHECK(expr2(1, 1) ==  57); CHECK(expr3(1, 1) ==  5); CHECK(expr4(1, 1) ==  5); 
    CHECK(expr1(1, 2) ==  58); CHECK(expr2(1, 2) ==  58); CHECK(expr3(1, 2) == 47); CHECK(expr4(1, 2) == 47); 
    CHECK(expr1(1, 3) ==  77); CHECK(expr2(1, 3) ==  77); CHECK(expr3(1, 3) == 10); CHECK(expr4(1, 3) == 10); 
    CHECK(expr1(2, 0) == -30); CHECK(expr2(2, 0) == -30); CHECK(expr3(2, 0) ==  7); CHECK(expr4(2, 0) ==  7); 
    CHECK(expr1(2, 1) == -16); CHECK(expr2(2, 1) == -16); CHECK(expr3(2, 1) ==  9); CHECK(expr4(2, 1) ==  9); 
    CHECK(expr1(2, 2) == -21); CHECK(expr2(2, 2) == -21); CHECK(expr3(2, 2) == 45); CHECK(expr4(2, 2) == 45); 
    CHECK(expr1(2, 3) ==  11); CHECK(expr2(2, 3) ==  11); CHECK(expr3(2, 3) == 21); CHECK(expr4(2, 3) == 21); 

    CHECK_NOTHROW(mat  + vec1);
    CHECK_NOTHROW(mat  + vec2);
    CHECK_THROWS (mat  + trans(vec1));
    CHECK_THROWS (mat  + trans(vec2));
    CHECK_NOTHROW(vec1 + mat);
    CHECK_NOTHROW(vec2 + mat);
    CHECK_THROWS (trans(vec1) + mat);
    CHECK_THROWS (trans(vec2) + mat);
    CHECK_THROWS (vec1 + vec2);
    CHECK_THROWS (trans(vec2) + vec1);

    CHECK(-trans(vec2 + 2 * mat - vec1 / 11) * trans(vec1) == DynamicMatrix<int>{ {-264, -990, 22}, { -176, -110, 374 }, { -275, -2475, 1056 }, { -99, -1485, 1232 }});
}
