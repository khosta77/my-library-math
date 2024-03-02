#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <istream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>
#include <stdexcept>

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
    int sign(size_t x) const;
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
    explicit Matrix(const size_t &_rows = 0, const size_t &_cols = 0) noexcept;

    /** @brief Конструтор создающий матрицу из потока данных. В потоке данные представлены:
     *         3 3
     *         1 2 3
     *         4 5 6
     *         7 8 9
     *         Где 1 строка это rows x cols
     *  @param is Поток данных это может быть как поток из файла
     *  @exception InvalidMatrixStream() Ошибка чтения из потока
     * */
    explicit Matrix(std::istream &is);

    /** @brief Конструктор копирования
     *  @param rhs Другая матрица
     * */
    Matrix(const Matrix &rhs) noexcept;

    /** @brief Оператор присваивания
     *  @param rhs Другая матрица
     *  @return Возвращает присвоенную матрицу
     * */
    Matrix &operator=(const Matrix &rhs) noexcept;

    /** @brief Деструктор, должен очистить память
     * */
    ~Matrix() noexcept;

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
    size_t getRows() const noexcept;

    /** @brief Метод получения колличества колонок
     *  @return Возвращает переменную cols
     * */
    size_t getCols() const noexcept;

	/** @brief Проверка на нулевую матрицу
	 *  @return Если матрица пустая вернет true, в противном случае false
	 * */
    bool isNull() const noexcept;

    /** @brief Спомощью такой перегруженной функциональные формы происходит 
     *         извлечение элемента без его изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j
     *  @exception OutOfRange() Выход за пределы матрицы
     * */
    double operator()(size_t i, size_t j) const;

    /** @brief Спомощью такой перегруженной функциональные формы происходит
     *         извлечение элемента для его дальнейшего изменения.
     *  @param i номер строки, если не входит в границы, вернуть 0
     *  @param j номер колонки, если не входит в границы, вернуть 0
     *  @return Возвращает элемент под номер строки i и колонки j, для его изменения
     *  @exception OutOfRange() Выход за пределы матрицы
     * */
    double& operator()(size_t i, size_t j);

    /** @} */ // Конец группы: Базовые операции

    /** @defgroup Математические операции над матрицами
     *  Булевые операции и арифметические операции(сложение, вычитание, умножение)
     *  @{
     */

    /** @brief Булевая операции равенство
     *  @param rhs Матрица
     *  @return true если матрицы равны, false если не равны
     * */
    bool operator==(const Matrix &rhs) const noexcept;

    /** @brief Булевая операци неравенства
     *  @param rhs Матрица
     *  @return false если матрицы равны, true если матрицы не равны
     * */
    bool operator!=(const Matrix &rhs) const noexcept;

    /** @brief Операция сложения матриц
     *  @param rhs Матрица
     *  @return Результат сложения матриц, если не возможно вернуть nullptr
     *  @exception DimensionMismatch() Несовместимость матриц
     * */
    Matrix operator+(const Matrix &rhs) const;
    
    /** @brief Операция вычитания матриц
     *  @param rhs Матрица
     *  @return Разницу матриц, если не возможно вернуть nullptr
     *  @exception DimensionMismatch() Несовместимость матриц
     * */
    Matrix operator-(const Matrix &rhs) const;
    
    /** @brief Операция умножения матриц
     *  @param rhs Матрица
     *  @return Умноженные матрицы, если не возможно вернуть nullptr
     *  @exception DimensionMismatch() Несовместимость матриц
     * */
    Matrix operator*(const Matrix &rhs) const;

    /** @brief Умножить матрицу на определнный элемент
     *  @param val Элемент, на который умножаем матрицу
     *  @return Matrix * val, если не возможно вернуть nullptr
     * */
    Matrix operator*(double val) const noexcept;

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
    Matrix minor(size_t row, size_t col) const noexcept;

    /** @brief Транспонирование матрицы
     *  @return Возвращает транспонированную матрицу, если нельзя взять, вернуть nullptr
     * */
    Matrix transp() const noexcept;

    /** @brief Вычисление определителя матрицы
     *  @return Возвращает определитель матрицы
     *  @exception DimensionMismatch() Не квадратная матрица
     * */
    double det() const;
    
    /** @brief Получает присоединенную матрицу
     *  @return Возвращает присоединенную матрицу
     *  @exception DimensionMismatch() Не квадратная матрица
     *  @exception SingularMatrix() Определитель равен ноль
     * */
    Matrix adj() const;

    /** @brief Обратная матрица
     *  @return Возвращает обратную матрицу
     *  @exception DimensionMismatch() Не квадратная матрица
     *  @exception SingularMatrix() Определитель равен ноль
     * */
    Matrix inv() const;

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
    void rationingRow(size_t r, double elem);

    /** @brief Нормировка колонки
     *  @param r Номер колонки
     *  @param elem Элемент на который делем строку
     * */
    void rationingCol(size_t c, double elem);

    /** @brief Вычесть из одной строки другую
     *  @param from_i Из этой строки
     *  @param i Вычесть эту строку
     * */
    void minusRowRow(size_t from_i, size_t i);
public:
    /** @brief Получение расширенной матрицы системы
     *  @param A
     *  @param B
     * */
    Matrix getExtendedMatrixOfTheSystem(Matrix B) const;

    /** @brief Метод Гаусса
     *  @param A Матрица системы
     *  @param B Расширение для матрицы системы
     * */
    friend Matrix SLEmethodGauss(Matrix A, Matrix B);
    /** @} */ // Конец группы: Продвинутые операции над матрицами
};

#endif  // _MATRIX_H_
