#include "../include/matrix.h"
#include "../include/exceptions.h"

static int sign(size_t x) {
        return x % 2 == 0 ? 1 : -1;
}

Matrix::Matrix(size_t rows, size_t cols) {
    this->rows = rows;
    this->cols = cols;
    this->matrix = new double[this->rows * this->cols];
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->matrix[i] = 0;
    }
}

Matrix::Matrix(std::istream &is) {
    this->rows = this->cols = 0;
    if (!(is >> this->rows >> this->cols)) {
        throw InvalidMatrixStream();
    } else {
        this->matrix = new double[this->rows * this->cols];
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if (!(is >> matrix[j + i * this->cols])) {
                    delete[] this->matrix;
                    throw InvalidMatrixStream();
                }
            }
        }
    }
}

Matrix::Matrix(const Matrix &rhs) {
    this->rows = rhs.getRows();
    this->cols = rhs.getCols();
    this->matrix = new double[this->rows * this->cols];
    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < this->cols; j++) {
            this->matrix[j + i * this->cols] = rhs.matrix[j + i * rhs.cols];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (&rhs != this) {
        delete[] this->matrix;
        this->rows = rhs.getRows();
        this->cols = rhs.getCols();
        this->matrix = new double[this->rows * this->cols];
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[j + i * this->cols] = rhs.matrix[j + i * rhs.cols];
            }
        }
    }
    return *this;
}

Matrix::~Matrix() {
    delete[] this->matrix;
}

// Basic operations
size_t Matrix::getRows() const {
    return this->rows;
}

size_t Matrix::getCols() const {
    return this->cols;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i >= this->rows || j >= this->cols) {
        throw OutOfRange(i, j, *this);
    }
    return this->matrix[j + i * this->cols];
}

double &Matrix::operator()(size_t i, size_t j) {
    if (i >= this->rows || j >= this->cols) {
        throw OutOfRange(i, j, *this);
    }
    return (double &) this->matrix[j + i * this->cols];
}

//  Math operations
bool Matrix::operator==(const Matrix &rhs) const {
    if (this->rows != rhs.rows || this->cols != rhs.cols) {
        return false;
    }
    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < this->cols; j++) {
            if (std::abs(this->matrix[j + i * this->cols] - rhs.matrix[j + i * this->cols]) > 1e-7) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const {
    return !(*this == rhs);
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    if (this->rows != rhs.rows || this->cols != rhs.cols) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        new_matrix.matrix[i] = this->matrix[i] + rhs.matrix[i];
    }
    return new_matrix;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
    if (this->rows != rhs.rows || this->cols != rhs.cols) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        new_matrix.matrix[i] = this->matrix[i] - rhs.matrix[i];
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    if (this->cols != rhs.rows) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix(this->rows, rhs.cols);
    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < rhs.cols; j++) {
            for (size_t k = 0; k < this->cols; k++) {
                new_matrix.matrix[j + i * new_matrix.cols] = new_matrix.matrix[j + i * new_matrix.cols]
                        + matrix[k + i * cols] * rhs.matrix[j + k * rhs.cols];

            }
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(double val) const {
    Matrix new_matrix(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        new_matrix.matrix[i] = this->matrix[i] * val;
    }
    return new_matrix;
}

Matrix operator*(double val, const Matrix &matrix) {
    return matrix * val;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    os << matrix.rows << ' ' << matrix.cols << '\n';
    for (size_t i = 0; i < matrix.rows * matrix.cols; i++) {
        os << std::setprecision(std::numeric_limits<double>::max_digits10)
           << matrix.matrix[i] << ' ';
    }
    os << '\n';
    return os;
}

// additional operations
Matrix Matrix::minor(size_t row, size_t col) const {
    Matrix minor(this->rows - 1, this->cols - 1);
    for (size_t l = 0; l < this->rows - 1; l++) {
        for (size_t k = 0; k < this->cols - 1; k++) {
            const size_t row_offset = l >= row;
            const size_t col_offset = k >= col;
            minor.matrix[k + l * minor.getCols()] =
                    this->matrix[(k + col_offset) + (l + row_offset) * this->cols];
        }
     }
    return minor;
}

Matrix Matrix::transp() const {
    Matrix tra_mtx(this->cols, this->rows);
    for (size_t i = 0; i < this->cols; i++) {
        for (size_t j = 0; j < this->rows; j++) {
            tra_mtx.matrix[j + i * tra_mtx.getCols()] = this->matrix[i + j * this->getCols()];
        }
    }
    return tra_mtx;
}

double Matrix::det() const {
    if (this->cols != this->rows) {
        throw DimensionMismatch(*this);
    } else {
        if ((this->rows == 1) && (this->rows == this->cols)) {
            return this->matrix[0];
        }
        if ((this->rows == 2) && (this->rows == this->cols)) {
            return this->matrix[0] * this->matrix[3] - this->matrix[2] * this->matrix[1];
        }
        double determinant = 0;
        for (size_t k = 0; k < this->cols; k++) {
            double v = this->minor(0, k).det();
            determinant += sign(k) * this->matrix[k] * v;
        }
        return determinant;
    }
}

Matrix Matrix::adj() const {
    if (this->det() == 0) {
        throw SingularMatrix();
    }
    Matrix adj_matrix(this->rows, this->cols);
    Matrix transp_matrix = this->transp();
    for (size_t i = 0; i < transp_matrix.rows; i++) {
        for (size_t j = 0; j < transp_matrix.cols; j++) {
            adj_matrix.matrix[i * transp_matrix.rows + j] = sign(i + j) * transp_matrix.minor(i, j).det();
        }
    }
    return adj_matrix;
}

Matrix Matrix::inv() const {
    if (this->cols != this->rows) {
        throw DimensionMismatch(*this);
    } else {
        double determinant = this->det();
        if (determinant == 0) {
            throw SingularMatrix();
        } else {
            double inv_det = 1 / determinant;
            return this->adj() * inv_det;
        }
    }
}


