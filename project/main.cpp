#include "./matrix/test/test.h"

#if 0
Matrix grouping(const Matrix& a, const Matrix& b, const Matrix& c) {
    Matrix sle(b.getRows(), b.getRows());

sle(0, 0) = b(0, 0); sle(0, 1) = c(0, 0); sle(0, 2) = 0;       sle(0, 3) = 0;       sle(0, 4) = 0;       sle(0, 5) = 0;
sle(1, 0) = a(0, 0); sle(1, 1) = b(1, 0); sle(1, 2) = c(1, 0); sle(1, 3) = 0;       sle(1, 4) = 0;       sle(1, 5) = 0;
sle(2, 0) = 0;       sle(2, 1) = a(1, 0); sle(2, 2) = b(2, 0); sle(2, 3) = c(2, 0); sle(2, 4) = 0;       sle(2, 5) = 0;
sle(3, 0) = 0;       sle(3, 1) = 0;       sle(3, 2) = a(2, 0); sle(3, 3) = b(3, 0); sle(3, 4) = c(3, 0); sle(3, 5) = 0;
sle(4, 0) = 0;       sle(4, 1) = 0;       sle(4, 2) = 0;       sle(4, 3) = a(3, 0); sle(4, 4) = b(4, 0); sle(4, 5) = c(4, 0);
sle(5, 0) = 0;       sle(5, 1) = 0;       sle(5, 2) = 0;       sle(5, 3) = 0;       sle(5, 4) = a(4, 0); sle(5, 5) = b(5, 0);

    return sle;
}
#endif

double norm1(const Matrix& A) {
    double sum = 0.0;
    for (size_t i = 0; i < A.getRows(); ++i)
        sum += std::abs(A(i, 0));
    return sum;
}

double calcR(const Matrix& X, const Matrix& X_) {
    const Matrix deltaX = (X - X_);
    return norm1(deltaX);
}

int main() {        
#if 0
    matrixtest::make();
#elif 1  // Гаусс
    const Matrix A = utils::readFromFile("./project/matrix/data/math_high_operation/Gausse/case_0/A.txt");
    const Matrix B = utils::readFromFile("./project/matrix/data/math_high_operation/Gausse/case_0/B.txt");
    const Matrix X = utils::readFromFile("./project/matrix/data/math_high_operation/Gausse/case_0/X.txt");

    double start = STSL::getCPUTime();
    Matrix x_gausse = SLEmethodGauss(A, B);
    double end = STSL::getCPUTime();
    std::cout << "Gausse time: " << (end - start) << std::endl;

    start = STSL::getCPUTime();
    Matrix x_jacobi = SLEmethodJacobi(A, B);
    end = STSL::getCPUTime();
    std::cout << "Jacobi time: " << (end - start) << std::endl;

    start = STSL::getCPUTime();
    Matrix x_zeidel = SLEmethodSeidel(A, B);
    end = STSL::getCPUTime();
    std::cout << "Zeidel time: " << (end - start) << std::endl;

    // Вывод матриц
    std::cout << x_gausse << x_jacobi << x_zeidel;
    
    // Расчет погрешностей
    std::cout << "Якоби: ||r0||1 = " << calcR(X, x_jacobi) << std::endl;
    std::cout << "Зейдель: ||r0||1 = " << calcR(X, x_zeidel) << std::endl;
    std::cout << "Гаусс: ||r0||1 = " << calcR(X, x_gausse) << std::endl;
/*
    //std::cout << Y;
    Y(0, 0) += 0.01;
    Y(2, 0) += 0.01;
    Y(3, 0) -= 0.01;
    Y(4, 0) += 0.01;

    Matrix x = SLEmethodRunThrough(A, B, C, Y);
    if (x != X)
        std::cout << x;
    else {
        std::cout << x;
        Matrix delta_x = (X - x);
    //    std::cout << delta_x;
    }
    auto abc = grouping(A, B, C);
    auto dx = (abc * x); 
    auto r = (Y - dx);
    std::cout << r;
*/
#elif 0 // Якоби
    const Matrix A = utils::readFromFile("./fasttest/a.txt");
    const Matrix B = utils::readFromFile("./fasttest/b.txt");
    const Matrix x = SLEmethodJacobi(A, B);
    std::cout << x;    
#elif 0 // Зейдель
    const Matrix A = utils::readFromFile("./fasttest/a.txt");
    const Matrix B = utils::readFromFile("./fasttest/b.txt");
    const Matrix x = SLEmethodSeidel(A, B);
    std::cout << x;    
#elif 0 // Прогонка
    const Matrix A = (utils::readFromFile("./fasttest/a.txt");
    const Matrix B = (utils::readFromFile("./fasttest/b.txt");
    const Matrix C = (utils::readFromFile("./fasttest/c.txt");
    const Matrix Y = (utils::readFromFile("./fasttest/y.txt");
    const Matrix x = SLEmethodRunThrough(A, B, C, Y);
    std::cout << x;
#endif 
	return 0;
}


