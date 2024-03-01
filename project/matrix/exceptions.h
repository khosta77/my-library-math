#pragma once // NOLINT

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
    OutOfRange(size_t i, size_t j, const Matrix &matrix) : MatrixException(
                "Индексы (" + std::to_string(i) + ", " + std::to_string(j) +
                ") выход за границы матрицы. Размер матрицы [" +
                std::to_string(matrix.getRows()) + ", " + std::to_string(matrix.getCols()) + "]") {}
};

/** @brief Ошибка матрицы, несовместимости матрицы или не квадратичности матрицы
 * */
class DimensionMismatch : public MatrixException {
public:
    DimensionMismatch(const Matrix &m1, const Matrix &m2) : MatrixException(
                    "M1[" + std::to_string(m1.getRows()) + ", " + std::to_string(m1.getCols()) + "] и M2[" +
                    std::to_string(m2.getRows()) + ", " + std::to_string(m2.getCols()) +
                    "] не совместимы") {}

    explicit DimensionMismatch(const Matrix &m) : MatrixException(
                            "M[" + std::to_string(m.getRows()) + ", " + std::to_string(m.getCols()) +
                            "] это не квадратная матрица") {}
};

/** @brief Ошибка матрицы, матрицы не сингулярны, то есть detA == 0
 * */
class SingularMatrix : public MatrixException {
public:
    SingularMatrix() : MatrixException("Сингулярная матрица") {}
};


