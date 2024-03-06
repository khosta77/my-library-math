#include "./matrix/test/test.h"

int main() {        
#if 0
    matrixtest::make();
#elif 1  // Гаусс
    const Matrix A = utils::readFromFile("./project/matrix/data/math_high_operation/Gausse/case_0/A.txt");
    const Matrix B = utils::readFromFile("./project/matrix/data/math_high_operation/Gausse/case_0/B.txt");
    const Matrix x = SLEmethodGauss(A, B);
    std::cout << x;    
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


