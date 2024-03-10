#include "./matrix.h"
#include "./exceptions.h"


int Matrix::sign(size_t x) const {
	return (((x % 2) == 0) ? 1 : -1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                    Base matrix operation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(const size_t &_rows, const size_t &_cols) noexcept : rows(_rows), cols(_cols) {
    matrix = new double[(rows * cols)];
    for (size_t i = 0, size = (rows * cols); i < size; ++i)
		matrix[i] = 0;
}

Matrix::Matrix(std::istream &is) {
	rows = cols = 0;
    if (!(is >> rows >> cols))
		throw InvalidMatrixStream();

    matrix = new double[(rows * cols)];
	for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
			if (!(is >> matrix[(j + (i * cols))])) {
                delete []matrix;
                throw InvalidMatrixStream();
            }
}

Matrix::Matrix(const Matrix &rhs) noexcept {
	rows = rhs.getRows();
    cols = rhs.getCols();
	matrix = new double[(rows * cols)];
    for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
            matrix[(j + (i * cols))] = rhs.matrix[(j + (i * cols))];
}

Matrix &Matrix::operator=(const Matrix &rhs) noexcept {
	if (&rhs != this) {
        delete []matrix;
		rows = rhs.getRows();
        cols = rhs.getCols();
        matrix = new double[(rows * cols)];
		for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                matrix[(j + (i * cols))] = rhs.matrix[(j + (i * cols))];
	}
    return *this;
}

Matrix::~Matrix() noexcept {
	delete []matrix;
}

// friend
std::ostream& operator<<(std::ostream &os, const Matrix &matrix) noexcept {
    os << matrix.rows << ' ' << matrix.cols << '\n';
    for (size_t i = 0; i < matrix.rows; ++i, os << '\n')
        for (size_t j = 0; j < matrix.cols; ++j)
#if 1
            os << std::setprecision(std::numeric_limits<double>::max_digits10) 
               << matrix.matrix[(j + (i * matrix.cols))] << ' ';
#else
            os << (round(matrix.matrix[(j + (i * matrix.cols))] * 10000) / 10000) << ' ';
#endif
    return os;
}

size_t Matrix::getRows() const noexcept {
	return rows;
}

size_t Matrix::getCols() const noexcept {
	return cols;
}

bool Matrix::isNull() const noexcept {
	return ((cols == 0) || (rows == 0));
}

double Matrix::operator()(size_t i, size_t j) const {
	if (((i >= rows) || (j >= cols)))
        throw OutOfRange(i, j, *this);
	return matrix[(j + (i * cols))];
}

double &Matrix::operator()(size_t i, size_t j) {
	if (((i >= rows) || (j >= cols)))
         throw OutOfRange(i, j, *this);
	return (double &) matrix[(j + (i * cols))];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                    Math operation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Matrix::operator==(const Matrix &rhs) const noexcept {
	if (((rows != rhs.rows) || (cols != rhs.cols)))
        return false;
	for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
			if (std::abs(matrix[(j + (i * cols))] - rhs.matrix[(j + (i * cols))]) > 1e-7)
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const noexcept {
	return !(*this == rhs);
}

Matrix Matrix::operator+(const Matrix &rhs) const {
	if (((rows != rhs.rows) || (cols != rhs.cols)))
        throw DimensionMismatch(*this, rhs);
	Matrix new_matrix(rows, cols);
	for (size_t i = 0, size = (rows * cols); i < size; ++i)
        new_matrix.matrix[i] = (matrix[i] + rhs.matrix[i]);
	return new_matrix;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
	if (((rows != rhs.rows) || (cols != rhs.cols)))
        throw DimensionMismatch(*this, rhs);
	Matrix new_matrix(rows, cols);
    for (size_t i = 0, size = (rows * cols); i < size; ++i)
		new_matrix.matrix[i] = (matrix[i] - rhs.matrix[i]);
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
	if (cols != rhs.rows)
        throw DimensionMismatch(*this, rhs);
        Matrix new_matrix(rows, rhs.cols);
    for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < rhs.cols; ++j)
            for (size_t k = 0; k < cols; ++k)
                new_matrix.matrix[(j + (i * new_matrix.cols))] = (
						new_matrix.matrix[(j + (i * new_matrix.cols))]
                        + (matrix[(k + (i * cols))] * rhs.matrix[(j + (k * rhs.cols))]));
    return new_matrix;
}

Matrix Matrix::operator*(double val) const noexcept {
	Matrix new_matrix(rows, cols);
    for (size_t i = 0, size = (rows * cols); i < size; ++i)
		new_matrix.matrix[i] = (matrix[i] * val);
    return new_matrix;
}

// friend
Matrix operator*(double val, const Matrix &matrix) noexcept {
    return (matrix * val);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                    Pro operation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::minor(size_t row, size_t col) const noexcept {
	Matrix minor((rows - 1), (cols - 1));
    for (size_t l = 0, R = (rows - 1); l < R; ++l) {
		for (size_t k = 0, C = (cols - 1); k < C; ++k) {
            const size_t row_offset = (l >= row);
            const size_t col_offset = (k >= col);
			minor.matrix[k + l * minor.cols] = matrix[(k + col_offset) + (l + row_offset) * cols];
        }
    }
    return minor;
}

Matrix Matrix::transp() const noexcept {
	Matrix tra_mtx(cols, rows);
    for (size_t i = 0; i < cols; ++i)
		for (size_t j = 0; j < rows; ++j)
            tra_mtx.matrix[(j + (i * tra_mtx.cols))] = matrix[(i + (j * cols))];
    return tra_mtx;
}

double Matrix::det() const {
	if (cols != rows)
        throw DimensionMismatch(*this);

    if ((rows == 1))
		return matrix[0];

    if ((rows == 2))
        return ((matrix[0] * matrix[3]) - (matrix[2] * matrix[1]));

    double determinant = 0, v = 0;
	for (size_t k = 0; k < cols; ++k) {
        v = this->minor(0, k).det();
		determinant += (sign(k) * matrix[k] * v);
    }
    return determinant;
}

Matrix Matrix::adj() const {
    if (cols != rows)
		throw DimensionMismatch(*this);

	if (this->det() == 0)
        throw SingularMatrix();

	Matrix adj_matrix(rows, cols);
    Matrix transp_matrix = this->transp();
	for (size_t i = 0; i < transp_matrix.rows; ++i)
        for (size_t j = 0; j < transp_matrix.cols; ++j)
			adj_matrix.matrix[((i * transp_matrix.rows) + j)] = (sign(i + j)
                * transp_matrix.minor(i, j).det());
    return adj_matrix;
}

Matrix Matrix::inv() const {
	if (cols != rows)
        throw DimensionMismatch(*this);

	double determinant = this->det();
    if (determinant == 0)
		throw SingularMatrix();

    return (this->adj() * (1 / determinant));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                    Math high operation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Matrix::rationingRow(size_t r, double elem) {
	if (r >= rows)
        return;
	for (size_t j = 0; j < cols; ++j)
        matrix[(j + (r * cols))] /= elem;
}

void Matrix::rationingCol(size_t c, double elem) {
    if (c >= cols)
		return;
	for (size_t i = 0; i < rows; ++i)
        matrix[(c + (i * cols))] /= elem;
}

void Matrix::minusRowRow(size_t from_i, size_t i) {
	// TODO: Чтобы они проверялись
    for (size_t j = 0; j < cols; ++j) {
		matrix[(j + (from_i * cols))] -= matrix[(j + (i * cols))];
    }
}

Matrix Matrix::getExtendedMatrixOfTheSystem(Matrix B) const {
	Matrix AB(rows, (cols + B.cols));
    for (size_t i = 0; i < AB.rows; ++i)
		for (size_t j = 0, ja = 0; j < cols; ++j, ++ja)
            AB(i, j) = matrix[(ja + (i * cols))];
    for (size_t i = 0; i < AB.rows; ++i)
		for (size_t j = cols, jb = 0; j < AB.cols; ++j, ++jb)
            AB(i, j) = B(i, jb);
    return AB;
}

// friend
Matrix SLEmethodGauss(const Matrix& A, const Matrix& B) {
    if (A.det() == 0)  // Проверка существует ли единственное решение
        throw SingularMatrix();
	if ((A.rows != B.rows) || (B.cols > 1) || (A.isNull()) || (B.isNull())) // проверка корректно ли вычисл.
        throw DimensionMismatch(A, B);

    Matrix AB = A.getExtendedMatrixOfTheSystem(B);  // Расширенная матрица системы

    const size_t row = AB.getRows();
    const size_t col = AB.getCols();
    for (size_t i = 0; i < row; ++i) {  // Выбор главного элемента по столбцу
        for (size_t j = i; j < row; ++j)
            AB.rationingRow(j, AB(j, i));  // Деление строки, на элемент
        for (size_t j = (i + 1); j < row; ++j)
            AB.minusRowRow(j, i);  // Вычитание строки
    }

    Matrix x(row, 1);  // Вычисление ответа путем обратного хода
    for (size_t i = (row - 1), k = (col - 2); ((i < row) && (col)); --i, --k) {
        x(i, 0) = AB(i, (col - 1));
        for (size_t j = (i - 1); j < row; --j)
            AB(j, (col - 1)) -= (AB(j, k) * x(i, 0));
    }
    return x;
}

static Matrix getSleForThroughStraight(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& y) {
    Matrix sle(b.getRows(), 4);
    const size_t ROW = sle.getRows();

    sle(0, 0) = 0; sle(0, 1) = b(0, 0); sle(0, 2) = c(0, 0); sle(0, 3) = y(0, 0);
    for (size_t i = 1; i < (ROW - 1); ++i) {
        sle(i, 0) = a((i - 1), 0); sle(i, 1) = b(i, 0); sle(i, 2) = c(i, 0); sle(i, 3) = y(i, 0);
    }
    sle((ROW - 1), 0) = a((ROW - 2), 0);
    sle((ROW - 1), 1) = b((ROW - 1), 0);
    sle((ROW - 1), 3) = y((ROW - 1), 0);
    return sle;
}

static bool checkConditionThroughStraight(const Matrix& sle) {
    for (size_t i = 0; i < sle.getRows(); ++i)
        if((std::abs(sle(i, 1)) < (std::abs(sle(i, 0)) + std::abs(sle(i, 2)))))
            return false;
    return true;
}

static Matrix SLEmethodThroughStraightRunning(const Matrix& sle) {
    const size_t ROW = sle.getRows();
    Matrix albe(ROW, 2);

    //// Для i = 0
    albe(0, 0) = (-sle(0, 2) / sle(0, 1)); albe(0, 1) = (sle(0, 3) / sle(0, 1));

    //// Для i = 1:(n - 1)
    double yi = 0.0;
    for (size_t i = 1; i < (ROW - 1); ++i) {
        yi = (sle(i, 1) + (sle(i, 0) * albe((i - 1), 0)));
        albe(i, 0) = (-sle(i, 2) / yi);
        albe(i, 1) = ((sle(i, 3) - (sle(i, 0) * (albe((i - 1), 1)))) / yi);
    }

    //// Для i = n
    yi = (sle((ROW - 1), 1) + (sle((ROW - 1), 0) * albe((ROW - 2), 0)));
    albe((ROW - 1), 1) = ((sle((ROW - 1), 3) - (sle((ROW - 1), 0) * albe((ROW - 2), 1))) / yi);

    return albe;
}

static Matrix SLEmethodThroughReverseСourse(const Matrix& sle, const Matrix& albe) {
    Matrix x(sle.getRows(), 1);
    x((sle.getRows() - 1), 0) = albe((sle.getRows() - 1), 1);
    for (size_t i = (sle.getRows() - 2); i < (sle.getRows()); --i)
        x(i, 0) = (albe(i, 1) + (albe(i, 0) * x((i + 1), 0)));
    return x;
}

// https://baktybek0v.github.io/tridiagonal-matrix/
// friend
Matrix SLEmethodRunThrough(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& y) {
    const Matrix sle = getSleForThroughStraight(a, b, c, y);

    if (!checkConditionThroughStraight(sle))  // Достаточной условие примененния матода прогонки
        throw NonFulfillmentOfConditions();

    const Matrix albe = SLEmethodThroughStraightRunning(sle);  // Прямой ход
    const Matrix x = SLEmethodThroughReverseСourse(sle, albe);  // Обратный ход
    return x;
}

static Matrix getSleMethodJacobiBetaM(const Matrix& AB) {
    Matrix beta(AB.getRows(), (AB.getCols() - 1));
    for (size_t i = 0; i < beta.getRows(); ++i)
        for (size_t j = 0; j < beta.getCols(); ++j)
            if (j != i)
                beta(i, j) = ((-AB(i, j)) / AB(i, i));
            else
                beta(i, j) = 0;
    return beta;
}

static Matrix getSleMethodJacobiCeM(const Matrix& AB) {
    Matrix ce(AB.getRows(), 1);
    const size_t last_elemen_j = (AB.getCols() - 1);
    for (size_t i = 0; i < ce.getRows(); ++i)
        ce(i, 0) = (AB(i, last_elemen_j) / AB(i, i));
    return ce;
}

static double calcMethodJacobiAbsX(const Matrix& x1, const Matrix& x2) {
    const Matrix x = (x1 - x2);
    double x_det = 1;
    for (size_t i = 0; i < x.getRows(); ++i)
        x_det *= x(i, 0);
    return std::abs(x_det);
}

static Matrix enumerationMethodJacobi(const Matrix& beta, const Matrix& ce, const double& eps1) {
    Matrix x1(beta.getRows(), 1), x2(beta.getRows(), 1);
    size_t i = 0;
    double x = (eps1 + 1.0);
    for (i = 0; x > eps1; ++i) {
        if ((i % 2) == 0) {
            x2 = ((beta * x1) + ce);
            x = calcMethodJacobiAbsX(x2, x1);
        } else {
            x1 = ((beta * x2) + ce);
            x = calcMethodJacobiAbsX(x1, x2);
        }
    }
     std::cout << i << std::endl;
    return ((i % 2) == 0) ? x2 : x1;
}

// friend
Matrix SLEmethodJacobi(const Matrix& A, const Matrix& B, const double& eps) {
    if (A.det() == 0)
        throw SingularMatrix();
	if ((A.rows != B.rows) || (B.cols > 1) || (A.isNull()) || (B.isNull()))
        throw DimensionMismatch(A, B);

    const Matrix AB = A.getExtendedMatrixOfTheSystem(B);
    const Matrix beta = getSleMethodJacobiBetaM(AB);
    const double Bdet = std::abs(beta.det());
    if (Bdet >= 1.0)
        throw MethodJacobiBdetMore1();
    const Matrix ce = getSleMethodJacobiCeM(AB);
    const double eps1 = (((1.0 - Bdet) / Bdet) * eps);
    return enumerationMethodJacobi(beta, ce, eps1);
}

static Matrix getMatrixB1(const Matrix& beta) {
    Matrix B1(beta.getRows(), beta.getCols());
    for (size_t i = 0; i < beta.getRows(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            B1(i, j) = beta(i, j);
        }
    }
    return B1;
}
/*
static void SeidelScalar(Matrix& x, const Matrix& B1, const Matrix& B2, const Matrix& ce) {
    const size_t row = B1.getRows();
    const size_t col = B1.getCols();

    for (size_t i = 1; i < col; ++i)
        x(0, 0) += (B2(0, i) * x(i, 0));
    x(0, 0) += ce(0, 0);

    double buf_x_0 = 0.0;
    double buf_x_1 = 0.0;

    for (size_t i = 1; i < row; ++i) {
        for (size_t k = 0; k < i; ++k)
            buf_x_0 += (B1(i, k) * x(k, 0));
        for (size_t k = i; k < col; ++k)
            buf_x_1 += (B2(i, k) * x1(k, 0));
        x2(i, 0) = (buf_x_0 + buf_x_1 + ce(i, 0));
        buf_x_0 = 0.0;
        buf_x_1 = 0.0;
    }
}
*/
static Matrix enumerationMethodSeidel(const Matrix& B1, const Matrix& B2, const Matrix& ce, 
                                      const double& eps2) {
    Matrix x1(B1.getRows(), 1), x2(B1.getRows(), 1);
    x2 = ((B2 * x1) + ce);
    size_t i = 0;
    [[maybe_unused]] double x = (eps2 + 1.0);
    for (i = 0; x > eps2; ++i) {
        if ((i % 2) == 0) {
            //SeidelScalar(x1, x1, B1, B2, ce);
            x2 = ((B1 * x2) + (B2 * x1) + ce);
            x = calcMethodJacobiAbsX(x2, x1);
        } else {
         //   SeidelScalar(x1, x1, B1, B2, ce);
            x1 = ((B1 * x1) + (B2 * x2) + ce);
            x = calcMethodJacobiAbsX(x1, x2);
        }
    }
     std::cout << i << std::endl;
    return ((i % 2) == 0) ? x2 : x1;
}

// friend
Matrix SLEmethodSeidel(const Matrix& A, const Matrix& B, const double& eps) {
    if (A.det() == 0)
        throw SingularMatrix();
	if ((A.rows != B.rows) || (B.cols > 1) || (A.isNull()) || (B.isNull()))
        throw DimensionMismatch(A, B);

    const Matrix AB = A.getExtendedMatrixOfTheSystem(B);
    const Matrix beta = getSleMethodJacobiBetaM(AB);
    const double Bdet = std::abs(beta.det());
    if (Bdet >= 1.0)
        throw MethodJacobiBdetMore1();
    const Matrix B1 = getMatrixB1(beta);
    const Matrix B2 = (beta - B1);
    const Matrix ce = getSleMethodJacobiCeM(AB);
    const double eps2 = (((1.0 - Bdet) / Bdet) * eps);
    return enumerationMethodSeidel(B1, B2, ce, eps2);
}


