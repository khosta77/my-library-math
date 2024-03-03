#ifndef TEST_BASE_OPERATION_H_
#define TEST_BASE_OPERATION_H_

#include "utils.h"

namespace TestBaseOperations {

    /** @brief Тест конструктора с параметрами 0х0. Если не нулевая то вернет false, так же проверка метода
     *         isNull()
     */
    bool Constructor00();

    /** @brief Тест конструктора с параметрами XxX. Если метод isNull возвращает true, та значит массив не
     *         создан, тест не пройден. После осуществляется проверка заполнения матрицы нулями, если хотя
     *         бы одно значение не нулевой, вернуть false.
     * */
    bool ConstructorXX();

    const std::string FN_MC_00 = "./project/matrix/data/base_operation/matrix_creation/case_0.txt";
    const std::string FN_MC_01 = "./project/matrix/data/base_operation/matrix_creation/case_1.txt";
    const std::string FN_MC_02 = "./project/matrix/data/base_operation/matrix_creation_neg/bad_format.txt";
    const std::string FN_MC_03 = "./project/matrix/data/base_operation/matrix_creation_neg/corrupted_data.txt";
    const std::string FN_MC_04 = "./project/matrix/data/base_operation/matrix_creation_neg/empty_file.txt";

    /** @brief Тест ошибки при чтении, когда мы передаем файл.
     * */
    bool ConstructorStream(const std::string &fn);

    /** @brief Тест конструктора копирования
     * */
    bool ConstructorCopy(const std::string &fn);

    /** @brief тест перегрузки оператора =
     * */
    bool EquallyCall(const std::string &fn);

    /** @brief Тест получения колонок и строк
     * */
    bool CheckGetterRowCol();

    /** @brief Тест перегруженного оператора доступа ()
     * */
    bool AccessControl();

    /** @brief Тест потока вывода
     * */
    bool CheckingFlow();

};  // TestBaseOperations

#endif  // TEST_BASE_OPERATION_H_
