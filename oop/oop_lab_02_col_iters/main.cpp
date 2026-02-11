#include <iostream>
#include <string>
#include "matrix.h"
using string = std::string;

int main()
{
    std::cout << "CONSTRUCTOR TESTING SECTION:" << "\n\n";
    try {
        std::cout << "Attempt to create matrix with negative size" << 
            " (conversion to very big size_t number)" << std::endl;
        Matrix<int> err_m(-1, 2);
    } catch (BaseException &err){
        std::cerr << err.what() << "\n\n";
    }

    size_t q = 2, z = 3;
    std::cout << "Constructor with two size_t numbers:\n";
    Matrix<int> a(q, z);
    std::cout << a << "\n\n";

    std::cout << "Check of constructor with c-matrix:\n";
    int **c_matrix = new int*[2];
    for (int i = 0; i < 2; ++i) 
    {
        c_matrix[i] = new int[2];
        for (int j = 0; j < 2; ++j)
            c_matrix[i][j] = i + j;
    }

    for (int i = 0; i < 2; i++)
    {    
        for (int j = 0; j < 2; j++)
            std::cout << c_matrix[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << "Constructor with one zero size:\n";
    Matrix<int> ab(0, 3);
    std::cout << "Sizes of matrix: " << ab.get_row_count() << " and " << ab.get_column_count() << "\n\n";
    std::cout << "Constructor with filler [Matrix<double> b(3, 2, 12)]:\n";
    Matrix<double> b(q, z, 12);
    std::cout << b << "\n\n";
    std::cout << "Constructor with initialization list [Matrix<double> c({ { 2., 3. }, { 3., 4. } })]:\n";
    Matrix<double> c({ { 2., 3. }, { 3., 4. } });
    std::cout << c << "\n\n";
    std::cout << "CONSTRUCTOR SECTION END\n\n\n";

    std::cout << "MATRIX COMPARE\n";
    std::cout << "Compare m01 and m02\n";
    Matrix<int> m01({{1, 2, 3}, {4, 5, 6}});
    Matrix<int> m02({{1, 2, 3}, {4, 5, 6}});
    if (m01 == m02)
        std::cout << "m01 = m02\n\n";
    else
        std::cout << "m01 != m02\n\n";

    Matrix<double> c1({ { 1., 2. }, { 3., 4. } });
    std::cout << "Check of transpose method on matrix c1:\n";
    std::cout << c1 << "\n";
    std::cout << "Command: c1.transpose();\n";
    Matrix<double> c1tr = c1.transpose();
    std::cout << "Result: \n" << c1tr << "\n\n";
    std::cout << "Check of power method on matrix c1:\n";
    std::cout << "Command: c1.power(2);\n";
    Matrix<double> c1power2 = c1.power(2);
    std::cout << "Result: \n" << c1power2 << "\n\n";

    std::cout << "GET ELEMENT METHODS SECTION:\n\n";
    Matrix<string> new_m = { { "a1", "a2", "a3" }, { "b1", "b2", "b3" }, { "c1", "c2", "c3" } };
    std::cout << "Working with matrix new_m: \n" << new_m << "\n\n";

    std::cout << "ITERATORS SECTION\n\n";
    std::cout << "Matrix from previos section:\n";
    std::cout << new_m << "\n\n";
    
    Matrix<int> m9 = {{2, 3}, {6, 8}};
    std::cout << "\nm9:\n" << m9;
    for (auto elem : m9)
        std::cout << elem << std::endl;
    // std::cout << "\n" << std::endl;

    Matrix<int> m10(m9.begin(), m9.end(), 2);
    std::cout << m10 << "\n" << std::endl;

    std::cout << "Matrix iterator constructor:\n";
    for (auto elem : new_m)
        std::cout << elem << std::endl;
    size_t rows = 3;
    Matrix<string> m1(new_m.begin(), new_m.end(), rows);
    std::cout << m1 << std::endl;

    std::cout << "Command: range-based for cycle (const elem &)\n";
    for (const auto &elem: new_m)
        std::cout << elem << ' ';
    std::cout << "\n\n";

    size_t cnt = 0;
    std::cout << "Range-based for filling matrix with string \"new_test<number>\":\n";
    for (auto &elem: new_m)
        elem = "new_test" + std::to_string(++cnt);
    std::cout << new_m << "\n\n";

    std::cout << "MatrixRow iterator:\n";
    Matrix<int> m10x10(10, 10);
    for (int i = 0; i < 10; ++i) 
        for (int j = 0; j < 10; ++j)
            m10x10[i][j] = i*10 + j;
    std::cout << "Matrix:\n" << m10x10 << std::endl;
    Matrix<int>::MatrixRow m_row = m10x10[3];
    std::cout << "MatrixRow:" << std::endl;
    for (Iterator i = m_row.begin(); i < m_row.end(); i++)
        std::cout << *i << ' ';
    std::cout << std::endl;
    Matrix<int>::MatrixColumn m_col = m10x10.get_column(3);
    std::cout << "MatrixColumn:" << std::endl;
    for (ColumnIterator i = m_col.begin(); i < m_col.end(); i++)
        std::cout << *i << ' ';
    std::cout << std::endl;

    std::cout << "ITERATORS SECTION ENDS\n\n";


    std::cout << "CONST ITERATORS AND OBJECTS SECTION\n\n";

    std::cout << "Create const matrix = { { '11', '12', '13' }, { '21', '22', '23' } }\n";
    const Matrix<string> const_m = { { "11", "12", "13" }, { "21", "22", "23" } };
    std::cout << "Range-based for cycle for const matrix:\n";
    for (const auto &elem: const_m)
        std::cout << elem << "; ";
    std::cout << "\n\n";

    std::cout << "Check of cbegin and cend methods of non-constant object (new_m matrix):\n";
    for (auto it = new_m.cbegin(); it < new_m.cend(); it++)
        std::cout << *it << "; ";
    std::cout << "\n\n";
    std::cout << "CONST ITERATORS AND OBJECTS SECTION ENDS\n\n";

    std::cout << "MATH OPERATIONS SECTION\n\n";
    Matrix<double> math_matrix = { { 1, 2, 3, 4 }, {7, 9, 11, 13}, {4, 2, 0, -2}, {1, 4, 7, 10} };
    std::cout << "Matrix to work with here (math_matrix): \n";
    std::cout << math_matrix << "\n\n";

    std::cout << "Operation: math_matrix += 2.5;\n";
    math_matrix += 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix -= 2.5;\n";
    math_matrix -= 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix *= 2.5;\n";
    math_matrix *= 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix /= 2.5;\n";
    math_matrix /= 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";

    std::cout << "Same operations, but using METHODS..\n";
    std::cout << "Operation: math_matrix.sum_value(2.5);\n";
    math_matrix.sum_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix.sub_value(2.5);\n";
    math_matrix.sub_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix.mul_value(2.5);\n";
    math_matrix.mul_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix.div_value(2.5);\n";
    math_matrix.div_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";

    Matrix<double> tmp;

    std::cout << "Operation: tmp = math_matrix + 2.5;\n";
    tmp = math_matrix + 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix - 2.5;\n";
    tmp = math_matrix - 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix * 2.5;\n";
    tmp = math_matrix * 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix / 2.5;\n";
    tmp = math_matrix / 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";

    std::cout << "Same operations, but using METHODS..\n";
    std::cout << "Operation: tmp = math_matrix.sum_value(2.5);\n";
    tmp = math_matrix.sum_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix.sub_value(2.5);\n";
    tmp = math_matrix.sub_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix.mul_value(2.5);\n";
    tmp = math_matrix.mul_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix.div_value(2.5);\n";
    tmp = math_matrix.div_value(2.5);
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";

    Matrix<double> det_matrix = { { 38, 382, 21, 9 }, { 21, 1, 9, 11 }, { 118, 5, 85, 2 }, { 10, 8, 22, 13 } };
    std::cout << "det_matrix:\n" << det_matrix << "\n\n";
    std::cout << "Operation: det_matrix.determinant();\n";
    std::cout << "Result: " << det_matrix.determinant() << "\n";
    std::cout << "Operation: det_matrix.inverse();\n";
    det_matrix.inverse();
    std::cout << "Result: \n" << det_matrix << "\n";
    // det_matrix.inverse();
    // std::cout << "\nInverse one more time\nResult: \n" << det_matrix << "\n";

    std::cout << "Matrix multiplication check: \n";
    Matrix<double> res;
    Matrix<double> m1_1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } };
    std::cout << "Operation: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    res = m1_1 * m2;
    std::cout << "Result:\n" << res << "\n\n";
    std::cout << "*with method* Operation: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    res = m1_1.mul_matrix(m2);
    std::cout << "Result:\n" << res << "\n\n";

    std::cout << "Matrix division check: \n";
    Matrix<double> m3 = { { 1, 2 }, { 3, 4 } };
    Matrix<double> m4 = { { 1, 2 }, { 3, 4 } };
    std::cout << "Operation: m3 / m4 (m4 = m3, sizes: 2x2, code line: " << __LINE__ << ")\n";
    res = m3 / m4;
    std::cout << "Result:\n" << res << "\n\n";
    std::cout << "*with method* Operation: m3 / m4 (m4 = m3, sizes: 2x2, code line: " << __LINE__ << ")\n";
    res = m3.div_matrix(m4);
    std::cout << "Result:\n" << res << "\n\n";

    std::cout << "MATH OPERATIONS SECTION END\n\n";


    std::cout << "ERRORS OPERATIONS SECTION\n\n";
    std::cout << "Attempt to reach wrong column:\n";
    try {
        res[0][100] = 1;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Attempt to reach wrong row:\n";
    try {
        res[100][0] = 22;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Attempt to read expired iterator\n";
    try {
        Iterator<double> it_tmp = res.begin();
        {
            Matrix<double> tmp = { { 1, 2 }, { 3, 4 } };
            it_tmp = tmp.begin();
        }
        std::cout << *it_tmp;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "call operator* for iterator out of the bounds:\n";
    try {
        Iterator<double> it_tmp = res.end();
        std::cout << *it_tmp;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "operator + for incompatible matrices:\n";
    try {
        Matrix<int> m1 = { { 1, 2, 3 } };
        Matrix<int> m2 = { { 1, 2 }, { 3, 4 } };
        std::cout << m1 + m2;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "operator * for incompatible matrices:\n";
    try {
        Matrix<int> m1 = { { 1, 2, 3 } };
        Matrix<int> m2 = { { 1, 2, 3 } };
        std::cout << m1 * m2;
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Call of constructor with invalid argument:\n";
    try {
        Matrix<int> matrix_inv = { { 1, 2 }, { 3 } };
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Call of operator= with init list (correct and incorrect):\n";
    try {
        Matrix<int> matrix_inv = { { 1, 2 }, { 3, 4 } };
        matrix_inv = { { 3, 4, 5 }, {1, 2, 3} };
        std::cout << "Correct init-list done:\n" << matrix_inv << "\n";
        matrix_inv = { { 4, 5 }, {1, 2, 3} };
    } catch (BaseException &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "ERRORS OPERATIONS SECTION END\n\n";

    std::cout << "Matrix<double>:\n";
    std::cout << c << std::endl;
    
    std::cout << "C matrix (double **):\n";
    double **c_mtx = c.make_c_matrix();
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
            std::cout << c_mtx[i][j] << "\t";
        std::cout << std::endl;
    }
    std::cout << "MATRIX -> C_MATRIX END\n";

    return 0;
}
