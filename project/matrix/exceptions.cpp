#include "./exceptions.h"

OutOfRange::OutOfRange(size_t i, size_t j, const Matrix &matrix) : MatrixException(
        "Индексы (" + std::to_string(i) + ", " + std::to_string(j) +
        ") выход за границы матрицы. Размер матрицы [" +
        std::to_string(matrix.getRows()) + ", " + std::to_string(matrix.getCols()) + "]") {}

DimensionMismatch::DimensionMismatch(const Matrix &m1, const Matrix &m2) : MatrixException(
        "M1[" + std::to_string(m1.getRows()) + ", " + std::to_string(m1.getCols()) + "] и M2[" +
        std::to_string(m2.getRows()) + ", " + std::to_string(m2.getCols()) +
        "] не совместимы") {}

DimensionMismatch::DimensionMismatch(const Matrix &m) : MatrixException(
        "M[" + std::to_string(m.getRows()) + ", " + std::to_string(m.getCols()) +
        "] это не квадратная матрица") {}


