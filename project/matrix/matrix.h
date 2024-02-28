#ifndef _MATRIX_H_
#define _MATRIX_H_

//#include <vector>
#include <istream>
#include <iomanip>
#include <cmath>
#include <limits>
//#include <stdexcept>

/* @class Matrix класс матрицы двумерной. Различные операции для расчетов
 * @param rows Строки
 * @param cols Колонки
 * @param matrix Массив элементов матрицы
 * */
class Matrix {
private:
    size_t rows;
    size_t cols;
    double *matrix;

    /** @brief Метод возвращает знак из матрицы знаков
     *  @param x позиция элемента
     *  @return Знак матрицы матрицы знаков
     * */
    static int sign(size_t x) {
        return (((x % 2) == 0) ? 1 : -1);
    }
public:
    /** @defgroup Базовые операции
     *  В данной группе содержатся различные конструкторы, оператор присваивания, а так же методы
     *  получения/изменения элемента и получения размеров матрицы
     *  @{
     */

    /** @brief Конструктор выделяет под матрицу размерами rows x cols область памяти, заполненную 0-ями
     *  @param rows Колличество строк в матрице, считается по умолчанию, что он >= 0
     *  @param cols Колличество колонок в матрице, считается по умолчанию, что он >= 0
     * */
    explicit Matrix(const size_t &_rows = 0, const size_t &_cols = 0) noexcept : rows(_rows), cols(_cols) {
        matrix = new double[(rows * cols)];
        for (size_t i = 0, size = (rows * cols); i < size; ++i)
            matrix[i] = 0;
    }

    /** @brief Конструтор создающий матрицу из потока данных. В потоке данные представлены:
     *         3 3
     *         1 2 3
     *         4 5 6
     *         7 8 9
     *         Где 1 строка это rows x cols, считается по умолчанию, что они >= 0, последующие данные
     *  @param is Поток данных это может быть как поток из файла, так и из терминала,
     *            если равен nullptr то матрица rows(0) x cols(0).
     * */
    explicit Matrix(std::istream &is) noexcept {
        rows = cols = 0;
        if (!(is >> rows >> cols)) {
            return;
            //throw InvalidMatrixStream();
        } else {
            matrix = new double[(rows * cols)];
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    if (!(is >> matrix[(j + (i * cols))])) {
                        delete []matrix;
                        rows = cols = 0;
                        return;
                    }
                }
            }
        }
    }

    /** @brief Конструктор копирования
     *  @param rhs Другая матрица, если равна nullptr, то тогда матрица 0x0
     * */
    Matrix(Matrix &rhs) noexcept {
        rows = rhs.getRows();
        cols = rhs.getCols();
        matrix = new double[(rows * cols)];
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                matrix[(j + (i * cols))] = rhs.matrix[(j + (i * cols))];
    }

    /** @brief Оператор присваивания
     *  @param rhs Другая матрица, если равна nullptr, то тогда матрица 0x0
     *  @return Возвращает присвоенную матрицу
     * */
    Matrix &operator=(const Matrix &rhs) noexcept {
        if (&rhs != this) {
            delete[] matrix;
            rows = rhs.getRows();
            cols = rhs.getCols();
            matrix = new double[(rows * cols)];
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    matrix[(j + (i * cols))] = rhs.matrix[(j + (i * cols))];
        }
        return *this;
    }

    /** @brief Деструктор, должен очистить память
     * */
    ~Matrix() noexcept {
        delete []matrix;
    }

    /** @brief Оператор вывода данных, дружественный метод. Должен вывести как в поток терминала, так и в
     *         файл.
     *  @param os оператор вывода
     *  @param matrix матрица, которую хотим вывести
     *  @return Вывод матрицы
     * */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) noexcept;

    /** @brief Метод получения колличества строк
     *  @return Возвращает переменную rows
     * */
    size_t getRows() const noexcept {
        return rows;
    }

    /** @brief Метод получения колличества колонок
     *  @return Возвращает переменную cols
     * */
    size_t getCols() const noexcept {
        return cols;
    }

    bool isNull() const noexcept {
        return ((cols == 0) || (rows == 0));
    }

    /** @brief Спомощью такой перегруженной функциональные формы происходит 
     *         извлечение элемента без его изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j
     * */
    double operator()(size_t i, size_t j) const noexcept {
        if (((i >= rows) || (j >= cols)))
            return 0.0;
            // throw OutOfRange(i, j, *this);
        return matrix[(j + (i * cols))];
    }

    /** @brief Спомощью такой перегруженной функциональные формы происходит
     *         извлечение элемента для его дальнейшего изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j, для его изменения
     * */
    double& operator()(size_t i, size_t j) {
        if (((i >= rows) || (j >= cols)))
            // return  nullptr;
             throw; // OutOfRange(i, j, *this);
        return (double &) matrix[(j + (i * cols))];
    }

    /** @} */ // Конец группы: Базовые операции

    /** @defgroup Математические операции над матрицами
     *  Булевые операции и арифметические операции(сложение, вычитание, умножение)
     *  @{
     */

    /** @brief Булевая операции равенство
     *  @param rhs Матрица
     *  @return true если матрицы равны, false если не равны
     * */
    bool operator==(const Matrix &rhs) const noexcept {
        if (((rows != rhs.rows) || (cols != rhs.cols)))
            return false;
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                if (std::abs(matrix[(j + (i * cols))] - rhs.matrix[(j + (i * cols))]) > 1e-7)
                    return false;
        return true;
    }

    /** @brief Булевая операци неравенства
     *  @param rhs Матрица
     *  @return false если матрицы равны, true если матрицы не равны
     * */
    bool operator!=(const Matrix &rhs) const noexcept {
        return !(*this == rhs);
    }

    /** @brief Операция сложения матриц
     *  @param rhs Матрица
     *  @return Результат сложения матриц, если не возможно вернуть nullptr
     * */
    Matrix operator+(const Matrix &rhs) const noexcept {
        if (((rows != rhs.rows) || (cols != rhs.cols)))
            return Matrix(0, 0);
            // throw DimensionMismatch(*this, rhs);
        Matrix new_matrix(rows, cols);
        for (size_t i = 0, size = (rows * cols); i < size; ++i)
            new_matrix.matrix[i] = (matrix[i] + rhs.matrix[i]);
        return new_matrix;
    }
    
    /** @brief Операция вычитания матриц
     *  @param rhs Матрица
     *  @return Разницу матриц, если не возможно вернуть nullptr
     * */
    Matrix operator-(const Matrix &rhs) const noexcept {
        if (((rows != rhs.rows) || (cols != rhs.cols)))
            return Matrix(0, 0);
            // throw DimensionMismatch(*this, rhs);
        Matrix new_matrix(rows, cols);
        for (size_t i = 0, size = (rows * cols); i < size; ++i)
            new_matrix.matrix[i] = (matrix[i] - rhs.matrix[i]);
        return new_matrix;
    }
    
    /** @brief Операция умножения матриц
     *  @param rhs Матрица
     *  @return Умноженные матрицы, если не возможно вернуть nullptr
     * */
    Matrix operator*(const Matrix &rhs) const noexcept {
        if (cols != rhs.rows)
            return Matrix(0, 0);
            // throw DimensionMismatch(*this, rhs);
        Matrix new_matrix(rows, rhs.cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < rhs.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    new_matrix.matrix[(j + (i * new_matrix.cols))] = (
                            new_matrix.matrix[(j + (i * new_matrix.cols))]
                            + (matrix[(k + (i * cols))] * rhs.matrix[(j + (k * rhs.cols))]));
        return new_matrix;
    }

    /** @brief Умножить матрицу на определнный элемент
     *  @param val Элемент, на который умножаем матрицу
     *  @return Matrix * val, если не возможно вернуть nullptr
     * */
    Matrix operator*(double val) const noexcept {
        Matrix new_matrix(rows, cols);
        for (size_t i = 0, size = (rows * cols); i < size; ++i)
            new_matrix.matrix[i] = (matrix[i] * val);
        return new_matrix;
    }

    /** @brief Умножить матрицу на определнный элемент
     *  @param val Элемент, на который умножаем матрицу
     *  @param matrix Матрица
     *  @return Matrix * val, если не возможно вернуть nullptr
     * */
    friend Matrix operator*(double val, const Matrix &matrix) noexcept;

    /** @} */ // Конец группы: Математические операции над матрицами

    /** @defgroup Дополнительные операции над матрицами
     *  Транспонирование, вычисление определителя, присоединенная матрица и т.д.
     *  @{
     */

    /** @brief Вычисление минора матрицы
     *  @param row Номер строки, по которому берем минор
     *  @param col Номер строки, по которому берем минор
     *  @return Возвращает матрицу минора выбранного элемента, если элемент не в границах, вернуть nullptr
     * */
    Matrix minor(size_t row, size_t col) const noexcept {
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

    /** @brief Транспонирование матрицы
     *  @return Возвращает транспонированную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix transp() const noexcept {
        Matrix tra_mtx( cols, rows);
        for (size_t i = 0; i < cols; ++i)
            for (size_t j = 0; j < rows; ++j)
                tra_mtx.matrix[(j + (i * tra_mtx.cols))] = matrix[(i + (j * cols))];
        return tra_mtx;
    }

    /** @brief Вычисление определителя матрицы
     *  @return Возвращает определитель матрицы, считать, что берем всегда у квадратной, в противном случае 0
     * */
    double det() const noexcept {
        if (cols != rows)
            return std::numeric_limits<double>::min();
            // throw DimensionMismatch(*this);

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
    
    /** @brief Получает присоединенную матрицу
     *  @return Возвращает присоединенную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix adj() const noexcept {
        if (this->det() == 0)
            return Matrix(0, 0);
            // throw SingularMatrix();

        Matrix adj_matrix(rows, cols);
        Matrix transp_matrix = this->transp();
        for (size_t i = 0; i < transp_matrix.rows; ++i)
            for (size_t j = 0; j < transp_matrix.cols; ++j)
                adj_matrix.matrix[((i * transp_matrix.rows) + j)] = (sign(i + j)
                    * transp_matrix.minor(i, j).det());
        return adj_matrix;
    }

    /** @brief Обратная матрица
     *  @return Возвращает обратную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix inv() const noexcept {
        if (cols != rows)
            return Matrix(0, 0);
            // throw DimensionMismatch(*this);
        
        double determinant = this->det();
        if (determinant == 0)
            return Matrix(0, 0);
            // throw SingularMatrix();

        return (this->adj() * (1 / determinant));
    }

    /** @brief Метод Гаусса
     * */

    /** @} */ // Конец группы: Дополнительные операции над матрицами

    /** @defgroup Продвинутые операции над матрицами
     *  Транспонирование, вычисление определителя, присоединенная матрица и т.д.
     *  @{
     */

public:
    /** @brief Нормировка строки
     *  @param r Номер строки
     *  @param elem Элемент на который делем строку
     * */
    void rationingRow(size_t r, double elem) {
        if ((rows <= 0) || (r >= rows))
            return;
        for (size_t j = 0; j < cols; ++j)
            matrix[(j + (r * cols))] /= elem;
    }

    /** @brief Нормировка колонки
     *  @param r Номер колонки
     *  @param elem Элемент на который делем строку
     * */
    void rationingCol(size_t c, double elem) {
        if ((cols <= 0) || (c >= cols))
            return;
        for (size_t i = 0; i < rows; ++i)
            matrix[(c + (i * cols))] /= elem;
    }

    /** @brief Вычесть из одной строки другую
     *  @param from_i Из этой строки
     *  @param i Вычесть эту строку
     * */
    void minusRowRow(size_t from_i, size_t i) {
        // TODO: Чтобы они проверялись
        for (size_t j = 0; j < cols; ++j) {
            matrix[(j + (from_i * cols))] -= matrix[(j + (i * cols))];
        }
    }
public:
    /** @brief Получение расширенной матрицы системы
     *  @param A
     *  @param B
     * */
    Matrix getExtendedMatrixOfTheSystem(Matrix B) const {
        if (isNull() || B.isNull())
            return Matrix(0, 0);
        if (rows != B.rows)
            return Matrix(0, 0);

        Matrix AB(rows, (cols + B.cols));
        for (size_t i = 0; i < AB.rows; ++i)
            for (size_t j = 0, ja = 0; j < cols; ++j, ++ja)
                AB(i, j) = matrix[(ja + (i * cols))];
        for (size_t i = 0; i < AB.rows; ++i)
            for (size_t j = cols, jb = 0; j < AB.cols; ++j, ++jb)
                AB(i, j) = B(i, jb);
        return AB;
    }

    /** @brief Метод Гаусса
     *  @param A Матрица системы
     *  @param B Расширение для матрицы системы
     * */
    friend Matrix SLEmethodGauss(Matrix A, Matrix B);
    /** @} */ // Конец группы: Продвинутые операции над матрицами
};

std::ostream& operator<<(std::ostream &os, const Matrix &matrix) noexcept {
    os << matrix.rows << ' ' << matrix.cols << '\n';
    for (size_t i = 0; i < matrix.rows; ++i, os << '\n')
        for (size_t j = 0; j < matrix.cols; ++j)
            os << /*std::setprecision(std::numeric_limits<double>::max_digits10) <<*/
                 (round(matrix.matrix[(j + (i * matrix.cols))] * 10000) / 10000) << ' ';
    return os;
}

Matrix operator*(double val, const Matrix &matrix) noexcept {
    return (matrix * val);
}

Matrix SLEmethodGauss(Matrix A, Matrix B) {
    if (A.det() == 0)
        Matrix(0, 0);

    Matrix AB = A.getExtendedMatrixOfTheSystem(B);
    if (AB.isNull())
        return Matrix(0, 0);

    for (size_t i = 0; i < AB.getRows(); ++i) {
        for (size_t j = i; j < AB.getRows(); ++j) {
            AB.rationingRow(j, AB(j, i));
        }
        for (size_t j = (i + 1); j < AB.getRows(); ++j) {
            AB.minusRowRow(j, i);
        }
    }

    Matrix x(AB.getRows(), 1);
    for (size_t i = (x.getRows() - 1), k = (AB.getCols() - 2); ((i < x.getRows()) && (k < AB.getCols())); --i, --k) {
        x(i, 0) = AB(i, (AB.getCols() - 1));
        for (size_t j = (i - 1); j < x.getRows(); --j) {
            AB(j, (AB.getCols() - 1)) -= (AB(j, k) * x(i, 0));
        }
    }

    return x;
} 

#endif  // _MATRIX_H_

