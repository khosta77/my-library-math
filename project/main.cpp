#include "./matrix/test/test.h"

int main() {
#if 1
	Matrix a(2, 1);
    a(0, 0) = 2; a(1, 0) = 2;
    Matrix b(3, 1);
    b(0, 0) = 2; b(1, 0) = -4; b(2, 0) = -3;
    Matrix c(2, 1);
    c(0, 0) = -1; c(1, 0) = 1;
    Matrix y(3, 1);
    y(0, 0) = -1; y(1, 0) = -8; y(2, 0) = -14;
//	A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3; A(0, 3) = 4;
//	A(1, 0) = 3; A(1, 1) = 5; A(1, 2) = 1; A(1, 3) = 7;
//	A(2, 0) = 4; A(2, 1) = 1; A(2, 2) = 0; A(2, 3) = -1;
//	A(3, 0) = 2; A(3, 1) = 2; A(3, 2) = 2; A(3, 3) = 3;

//	Matrix B(4, 1);
//	B(0, 0) = 22; B(1, 0) = 38; B(2, 0) = 8; B(3, 0) = 20;
	Matrix x = SLEmethodRunThrough(a, b, c, y);

	std::cout << x/*.transp()*/ << std::endl;
#endif
    //matrixtest::make();
	return 0;
}


