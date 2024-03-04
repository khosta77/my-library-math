#ifndef _EXCEPTIONS_MATRIX_H_
#define _EXCEPTIONS_MATRIX_H_

#include <exception>
#include <string>

#include "matrix.h"

/** @brief Ошибка матрицы, с выводом сообщения
 * */
class MatrixException : public std::exception {
public:
    explicit MatrixException(const std::string &msg) : m_msg(msg) {}
    const char *what() const noexcept override {
		return m_msg.c_str();
	}

private:
    std::string m_msg;
};

/** @brief Ошибка матрицы при чтении из потока
 * */
class InvalidMatrixStream : public MatrixException {
public:
    InvalidMatrixStream() : MatrixException("Произошла ошибка при чтении из потока") {}
};

/** @brief Ошибка матрицы, выход за пределы матрицы
 * */
class OutOfRange : public MatrixException {
public:
    OutOfRange(size_t i, size_t j, const Matrix &matrix);
};

/** @brief Ошибка матрицы, несовместимости матрицы или не квадратичности матрицы
 * */
class DimensionMismatch : public MatrixException {
public:
    DimensionMismatch(const Matrix &m1, const Matrix &m2);
    explicit DimensionMismatch(const Matrix &m);
};

/** @brief Ошибка матрицы, матрицы не сингулярны, то есть detA == 0
 * */
class SingularMatrix : public MatrixException {
public:
    SingularMatrix() : MatrixException("Сингулярная матрица") {}
};

/** @brief Не выполненны условия для метода прогонки
 * */
class NonFulfillmentOfConditions : public MatrixException {
public:
    NonFulfillmentOfConditions() : MatrixException("Условия для метода прогонки не выполнены") {}
};

/** @brief В методе Якоби abs(|B|) >= 1
 * */
class MethodJacobiBdetMore1 : public MatrixException {
public:
    MethodJacobiBdetMore1() : MatrixException("В методе Якоби определитель B больше или равен 1") {}
};

#endif  // _EXCEPTIONS_MATRIX_H_
