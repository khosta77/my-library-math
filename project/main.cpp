#include <iostream>

//#include "./StepanTestScriptLibrary/project/StepanTestScriptLibrary.h"

#include "./matrix/matrix.h"

int main() {

	Matrix A(4, 4);

	A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3; A(0, 3) = 4;
	A(1, 0) = 3; A(1, 1) = 5; A(1, 2) = 1; A(1, 3) = 7;
	A(2, 0) = 4; A(2, 1) = 1; A(2, 2) = 0; A(2, 3) = -1;
	A(3, 0) = 2; A(3, 1) = 2; A(3, 2) = 2; A(3, 3) = 3;

	Matrix B(4, 1);
	B(0, 0) = 22; B(1, 0) = 38; B(2, 0) = 8; B(3, 0) = 20;
	Matrix x = SLEmethodGauss(A, B);

	std::cout << x.transp() << std::endl;
	return 0;
}


