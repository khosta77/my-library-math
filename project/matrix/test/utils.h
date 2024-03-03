#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <random>
#include <filesystem>
#include <fstream>
#include <vector>

#include "../matrix.h"
#include "../exceptions.h"

namespace utils {
    using MatrixData = std::vector<std::vector<double>>;
    using MatrixRow = std::vector<double>;

    MatrixData createMatrixData(std::istream& is);
    std::ostream& operator<<(std::ostream& os, const MatrixData& matrix_data);

    const size_t MAX_SIZE = 10;
    [[maybe_unused]] const double MIN_VAL = -100.0;
    [[maybe_unused]] const double MAX_VAL = 100.0;

    double genDouble(double from = MIN_VAL, double to = MAX_VAL);
    size_t genSizeT(size_t from = 0, size_t to = MAX_SIZE);
    Matrix genMatrix(size_t rows = 0, size_t cols = 0);
    Matrix readFromFile(const std::string &fn);

    static std::random_device engine;

    bool operator==(const Matrix &matrix, const MatrixData &matrix_data);
    bool operator==(const MatrixData &matrix_data, const Matrix &matrix);

};  // utils

#endif  // UTILS_H_
