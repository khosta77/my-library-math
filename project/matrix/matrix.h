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
    explicit Matrix(const size_t &rows = 0, const size_t &cols = 0);

    /** @brief Конструтор создающий матрицу из потока данных. В потоке данные представлены:
     *         3 3
     *         1 2 3
     *         4 5 6
     *         7 8 9
     *         Где 1 строка это rows x cols, считается по умолчанию, что они >= 0, последующие данные
     *  @param is Поток данных это может быть как поток из файла, так и из терминала,
     *            если равен nullptr то матрица 0x0.
     * */
    explicit Matrix(std::istream &is);

    /** @brief Конструктор копирования
     *  @param rhs Другая матрица, если равна nullptr, то тогда матрица 0x0
     * */
    Matrix(const Matrix &rhs);

    /** @breif Оператор присваивания
     *  @param rhs Другая матрица, если равна nullptr, то тогда матрица 0x0
     *  @return Возвращает присвоенную матрицу
     * */
    Matrix &operator=(const Matrix &rhs);

    /** @brief Деструктор, должен очистить память
     * */
    ~Matrix();

    /** @brief Метод получения колличества строк
     *  @return Возвращает переменную rows
     * */
    size_t getRows() const;

    /** @brief Метод получения колличества колонок
     *  @return Возвращает переменную cols
     * */
    size_t getCols() const;

    /** @brief Спомощью такой перегруженной функциональные формы происходит 
     *         извлечение элемента без его изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j
     * */
    double operator()(size_t i, size_t j) const;

    /** @brief Спомощью такой перегруженной функциональные формы происходит
     *         извлечение элемента для его дальнейшего изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j, для его изменения
     * */
    double& operator()(size_t i, size_t j);

    /** @} */ // end of group1

    //  Math operations
    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;

    Matrix operator*(double val) const;

    friend Matrix operator*(double val, const Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    // additional operations
    Matrix minor(size_t row, size_t col) const;
    Matrix transp() const;
    double det() const;
    Matrix adj() const;
    Matrix inv() const;
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

#endif  // _MATRIX_H_

