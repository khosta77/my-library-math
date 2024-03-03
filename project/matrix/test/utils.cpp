#include "utils.h"

utils::MatrixData utils::createMatrixData(std::istream &is) {
    size_t rows = 0;
    size_t cols = 0;

    is >> rows >> cols;
    if (!is) {
        throw std::runtime_error("MatrixData чтение не удалось");
    }

    MatrixData matrix_data(rows, MatrixRow(cols, 0.0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            is >> matrix_data[i][j];
            if (!is) {
                throw std::runtime_error("MatrixData чтение с ошибкой");
            }
        }
    }

    return matrix_data;
}

std::ostream& utils::operator<<(std::ostream &os, const utils::MatrixData &matrix_data) {
    auto rows = matrix_data.size();
    auto cols = matrix_data[0].size();

    os << rows << ' ' << cols << std::endl;

    for (auto& row: matrix_data) {
         for (auto& data: row) {
            os << data << ' ';
         }
        os << std::endl;
    }

    return os;
}

bool utils::operator==(const Matrix &matrix, const utils::MatrixData &matrix_data) {
    auto rows = matrix_data.size();
    auto cols = matrix_data[0].size();

    if (matrix.getRows() != rows || matrix.getCols() != cols) {
        return false;
    }

    for (size_t i = 0; i < matrix_data.size(); ++i) {
        for (size_t j = 0; j < matrix_data[i].size(); ++j) {
            if (matrix(i, j) != matrix_data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool utils::operator==(const utils::MatrixData &matrix_data, const Matrix &matrix) {
    return matrix == matrix_data;
}

double utils::genDouble(double from, double to) {
    return std::uniform_real_distribution<double>(from, to)(engine);
}

size_t utils::genSizeT(size_t from, size_t to) {
    return std::uniform_int_distribution<size_t>(from, to)(engine);
}

Matrix utils::genMatrix(size_t rows, size_t cols) {
    size_t rows_ = rows ? rows : genSizeT(1);
    size_t cols_ = cols ? cols : genSizeT(1);

    Matrix matrix(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            matrix(i, j) = genDouble();
        }
    }

    return matrix;
}

Matrix utils::readFromFile(const std::string &fn) {
    std::ifstream in(fn.c_str(), (std::ios_base::in));
    Matrix matrix(in);
    in.close();
    return matrix;
}


