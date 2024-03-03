#ifndef TEST_MATH_PRO_OPERATION_H_
#define TEST_MATH_PRO_OPERATION_H_

#include "utils.h"

namespace TestMathProOperations {
    //// TODO придумать тест для проверки минора

    /** @brief
     * */
    bool Transp();

    const std::string FN_PATH = "./project/matrix/data/math_pro_operation/matrix_";

    //// Det
    const std::string FN_DET_IN__00 = (FN_PATH + "det/case_0/in.txt");
    const std::string FN_DET_OUT_00 = (FN_PATH + "det/case_0/out.txt");
    const std::string FN_DET_IN__01 = (FN_PATH + "det/case_1/in.txt");
    const std::string FN_DET_OUT_01 = (FN_PATH + "det/case_1/out.txt");
    const std::string FN_DET_IN__02 = (FN_PATH + "det/case_2/in.txt");
    const std::string FN_DET_OUT_02 = "";

    /** @brief
     * */
    bool Det(const std::string &m, const std::string &d);

    //// Adj
    const std::string FN_ADJ_IN__00 = (FN_PATH + "adj/case_0/in.txt");
    const std::string FN_ADJ_OUT_00 = (FN_PATH + "adj/case_0/out.txt");
    const std::string FN_ADJ_IN__01 = (FN_PATH + "adj/case_1/in.txt");
    const std::string FN_ADJ_OUT_01 = (FN_PATH + "adj/case_1/out.txt");
    const std::string FN_ADJ_IN__02 = (FN_PATH + "adj/case_2/in.txt");
    const std::string FN_ADJ_OUT_02 = (FN_PATH + "adj/case_2/out.txt");

    /** @brief
     * */
    bool Adj(const std::string &in, const std::string &out);

    //// Inv
    const std::string FN_INV_IN__00 = (FN_PATH + "inv/case_0/in.txt");
    const std::string FN_INV_OUT_00 = (FN_PATH + "inv/case_0/out.txt");
    const std::string FN_INV_IN__01 = (FN_PATH + "inv/case_1/in.txt");
    const std::string FN_INV_OUT_01 = (FN_PATH + "inv/case_1/out.txt");
    const std::string FN_INV_IN__02 = (FN_PATH + "inv/case_2/in.txt");
    const std::string FN_INV_OUT_02 = (FN_PATH + "inv/case_2/out.txt");

    /** @brief
     * */
    bool Inv(const std::string &in, const std::string &out); 
};  // TestMathProOperations

#endif  // TEST_MATH_PRO_OPERATION_H_
