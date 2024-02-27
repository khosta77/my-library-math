#include <iostream>

//#include "./StepanTestScriptLibrary/project/StepanTestScriptLibrary.h"

#include "./matrix/matrix.h"

int main() {
	Matrix A(3, 3);
	A(0, 0) = 2; A(0, 1) = 4; A(0, 2) = 1;
	A(1, 0) = 5; A(1, 1) = 2; A(1, 2) = 1;
	A(2, 0) = 2; A(2, 1) = 3; A(2, 2) = 4;
	Matrix B(3, 1);
	B(0, 0) = 36; B(1, 0) = 47; B(2, 0) = 37;
	Matrix x = SLEmethodGauss(A, B);
	std::cout << x << std::endl;
	return 0;
}


