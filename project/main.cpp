#include "./matrix/test/test.h"

int main() {
#if 1
/*
	Matrix a(2, 1);
    a(0, 0) = 2; a(1, 0) = 2;
    Matrix b(3, 1);
    b(0, 0) = 2; b(1, 0) = -4; b(2, 0) = -3;
    Matrix c(2, 1);
    c(0, 0) = -1; c(1, 0) = 1;
    Matrix y(3, 1);
    y(0, 0) = -1; y(1, 0) = -8; y(2, 0) = -14;
*/
    Matrix A(4, 4);
    A(0, 0) = 31.2; A(0, 1) = -1.32; A(0, 2) = -7.68; A(0, 3) = 4.09;
	A(1, 0) = 7.23; A(1, 1) = -126; A(1, 2) = 7.14; A(1, 3) = 3.04;
	A(2, 0) = 9.49; A(2, 1) = 6.4; A(2, 2) = 6; A(2, 3) = 8.45;
	A(3, 0) = 2.68; A(3, 1) = -3.29; A(3, 2) = 0.28; A(3, 3) = 13.4;
	Matrix B(4, 1);
	B(0, 0) = -83.32; B(1, 0) = 38.9; B(2, 0) = -56.7; B(3, 0) = -504.09;
	Matrix x = SLEmethodSeidel(A, B, 1e-15);
// 3.7777777777777812 -2.2222222222222361 0.44444444444444103 5.3333333333333419 
	std::cout << x.transp() << std::endl;
#endif
    //matrixtest::make();
	return 0;
}


