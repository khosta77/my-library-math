#ifndef TEST_MATH_BASE_OPERATION_H_
#define TEST_MATH_BASE_OPERATION_H_

#include "utils.h"

namespace TestMathBaseOperations {

    /** @brief тест оператора ==
     * */
    bool EqualYes();

    /** @brief тест оператора ==
     * */
    bool EqualNo();

    /** @brief тест оператора !=
     * */
    bool NoEqualYes();

    /** @brief тест оператора !=
     * */
    bool NoEqualNo();

    const std::string FN_PATH = "./project/matrix/data/math_base_operation/matrix_";

    //// SUM
    const std::string FN_A_SUM_00 = (FN_PATH + "sum/case_a_00.txt");
    const std::string FN_B_SUM_00 = (FN_PATH + "sum/case_b_00.txt");
    const std::string FN_X_SUM_00 = (FN_PATH + "sum/case_x_00.txt");
    
    //// SUB
    const std::string FN_A_SUB_00 = (FN_PATH + "sub/case_a_00.txt");
    const std::string FN_B_SUB_00 = (FN_PATH + "sub/case_b_00.txt");
    const std::string FN_X_SUB_00 = (FN_PATH + "sub/case_x_00.txt");
  
    //// SCALAR
    const std::string FN_A_SCA_00 = (FN_PATH + "scalar/case_a_00.txt");
    const std::string FN_B_SCA_00 = (FN_PATH + "scalar/case_b_00.txt");
    const std::string FN_B_SCA_01 = (FN_PATH + "scalar/case_b_01.txt");
    const std::string FN_X_SCA_00 = (FN_PATH + "scalar/case_x_00.txt");
    const std::string FN_X_SCA_01 = (FN_PATH + "scalar/case_x_01.txt");

    /** @brief Тест оператора +
     * */
    bool Sum(const std::string &A, const std::string &B, const std::string &X);

    /** @brief Тест оператора +
     * */
    bool ErrorSum();

    /** @brief Тест оператора -
     * */
    bool Sub(const std::string &A, const std::string &B, const std::string &X);

    /** @brief Тест оператора -
     * */
    bool ErrorSub();

    /** @brief Тест оператора M * M
     * */
    bool Scalar(const std::string &A, const std::string &B, const std::string &X);

    /** @brief Тест оператора M * M
     * */
    bool ErrorScalar();

    /** @brief Тест умножения матрицы на число
     * */
    bool ScalarMX();

    /** @brief Тест умножения матрицы на число
     * */
    bool ScalarXM();

};  // TestMathBaseOperations

#endif  // TEST_MATH_BASE_OPERATION_H_
