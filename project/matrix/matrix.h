#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <istream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

/* @class Matrix
 * */
class Matrix {
private:
    size_t rows;
    size_t cols;
    double *matrix;

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
    Matrix(const Matrix &rhs) noexcept {
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

    /** @brief Спомощью такой перегруженной функциональные формы происходит 
     *         извлечение элемента без его изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j
     * */
    double operator()(size_t i, size_t j) const noexcept {
        if (((i >= rows) || (j >= cols)))
            return 0;
            // throw OutOfRange(i, j, *this);
        return matrix[(j + (i * cols))];
    }

    /** @brief Спомощью такой перегруженной функциональные формы происходит
     *         извлечение элемента для его дальнейшего изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j, для его изменения
     * */
    double& operator()(size_t i, size_t j) noexcept {
        if (((i >= rows) || (j >= cols)))
            return 0;
            // throw OutOfRange(i, j, *this);
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
            return nullptr;
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
            return nullptr;
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

    }

    /** @brief Умножить матрицу на определнный элемент
     *  @param val Элемент, на который умножаем матрицу
     *  @return Matrix * val, если не возможно вернуть nullptr
     * */
    Matrix operator*(double val) const noexcept {

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

    }

    /** @brief Транспонирование матрицы
     *  @return Возвращает транспонированную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix transp() const noexcept {

    }

    /** @brief Вычисление определителя матрицы
     *  @return Возвращает определитель матрицы, считать, что берем всегда у квадратной, в противном случае 0
     * */
    double det() const noexcept {

    }
    
    /** @brief Получает присоединенную матрицу
     *  @return Возвращает присоединенную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix adj() const noexcept {

    }

    /** @brief Обратная матрица
     *  @return Возвращает обратную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix inv() const noexcept {

    }

    /** @} */ // Конец группы: Дополнительные операции над матрицами

    /** @defgroup Продвинутые операции над матрицами
     *  Транспонирование, вычисление определителя, присоединенная матрица и т.д.
     *  @{
     */

    /** @} */ // Конец группы: Продвинутые операции над матрицами
};

Matrix operator*(double val, const Matrix& matrix) {

}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {

}

#endif  // _MATRIX_H_

