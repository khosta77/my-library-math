#include "./matrix/test/test.h"
#include "./matrix/test/utils.h"


namespace TestMathHighOperation {
    using path = const std::string&;

    path PATH = "./project/matrix/data/math_high_operation/";
    path PREFIX_A = "/A.txt";
    path PREFIX_B = "/B.txt";
    path PREFIX_X = "/X.txt";

    path PATHG = (PATH + "Gausse/case_");

    bool Gausse() {
        static size_t i = 0;
        const Matrix A = utils::readFromFile((PATHG + std::to_string(i) + PREFIX_A));
        const Matrix B = utils::readFromFile((PATHG + std::to_string(i) + PREFIX_B));
        const Matrix X = utils::readFromFile((PATHG + std::to_string(i++) + PREFIX_X));
        Matrix x;
        try {
            x = SLEmethodGauss(A, B);
        } catch (const SingularMatrix& eSM) {
            return ((A.det() == 0.0) ? true : false);
        } catch (const DimensionMismatch& eDM) {
            return ((A.getRows() != B.getRows()) || (B.getCols() > 1) || (A.isNull()) || (B.isNull()));
        } catch (...) {
            return false;
        }
        return (x == X);
    }

    path PATHT = (PATH + "RunThrough/case_");
    path PREFIX_C = "/C.txt";
    path PREFIX_Y = "/Y.txt";

    bool RunThrough() {
        static size_t i = 0;
        const Matrix A = (utils::readFromFile((PATHT + std::to_string(i) + PREFIX_A)).transp());
        const Matrix B = (utils::readFromFile((PATHT + std::to_string(i) + PREFIX_B)).transp());
        const Matrix C = (utils::readFromFile((PATHT + std::to_string(i) + PREFIX_C)).transp());
        const Matrix Y = (utils::readFromFile((PATHT + std::to_string(i) + PREFIX_Y)).transp());
        const Matrix X = (utils::readFromFile((PATHT + std::to_string(i++) + PREFIX_X)).transp());
        Matrix x;
        try {
            x = SLEmethodRunThrough(A, B, C, Y);
        } catch (const NonFulfillmentOfConditions& eNFOC) {
            return ((fx.empty()) ? true : false);
        } catch (...) {
            return false;
        }
        return (x == X);
    }

    path PATHJ = (PATH + "Jacobi/case_");

    bool Jacobi() {
        static size_t i = 0;
        const Matrix A = utils::readFromFile((PATHJ + std::to_string(i) + PREFIX_A));
        const Matrix B = utils::readFromFile((PATHJ + std::to_string(i) + PREFIX_B));
        Matrix X;
        Matrix x;
        try {
            x = SLEmethodJacobi(A, B);
        } catch (const SingularMatrix& eSM) {
            return ((A.det() == 0.0) ? true : false);
        } catch (const DimensionMismatch& eDM) {
            return (A.getRows() != B.getRows()) || (B.getCols() > 1) || (A.isNull()) || (B.isNull());
        } catch (const MethodJacobiBdetMore1& eMJBM1) {
            try {    X = utils::readFromFile((PATHJ + std::to_string(i++) + PREFIX_X)); } 
            catch (const InvalidMatrixStream& eIMS) {    return true; }
            catch (...) {}
            return false;
        } catch (...) {
            return false;
        }
        X = utils::readFromFile((PATHJ + std::to_string(i++) + PREFIX_X));
        return (x == X);
    }

    path PATHS = (PATH + "Seidel/case_");

    bool Seidel() {
        static size_t i = 0;
        const Matrix A = utils::readFromFile((PATHS + std::to_string(i) + PREFIX_A));
        const Matrix B = utils::readFromFile((PATHS + std::to_string(i) + PREFIX_B));
        Matrix X;
        Matrix x;
        try {
            x = SLEmethodJacobi(A, B);
        } catch (const SingularMatrix& eSM) {
            return ((A.det() == 0.0) ? true : false);
        } catch (const DimensionMismatch& eDM) {
            return (A.getRows() != B.getRows()) || (B.getCols() > 1) || (A.isNull()) || (B.isNull());
        } catch (const MethodJacobiBdetMore1& eMJBM1) {
            try {    X = utils::readFromFile((PATHS + std::to_string(i++) + PREFIX_X)); } 
            catch (const InvalidMatrixStream& eIMS) {    return true; }
            catch (...) {}
            return false;
        } catch (...) {
            return false;
        }
        X = utils::readFromFile((PATHS + std::to_string(i++) + PREFIX_X));
        return (x == X);
    }

};

int main() {
    std::cout << TestMathHighOperation::RunThrough() << std::endl;
    std::cout << TestMathHighOperation::RunThrough() << std::endl;

#if 0
    std::cout << TestMathHighOperation::Gausse(TestMathHighOperation::GCASE_A_00,
                                               TestMathHighOperation::GCASE_B_00,
                                               TestMathHighOperation::GCASE_X_00) << std::endl;
    std::cout << TestMathHighOperation::Gausse(TestMathHighOperation::GCASE_A_01,
                                               TestMathHighOperation::GCASE_B_01,
                                               TestMathHighOperation::GCASE_X_01) << std::endl;
    std::cout << TestMathHighOperation::Jacobi(TestMathHighOperation::GCASE_A_00,
                                               TestMathHighOperation::GCASE_B_00,
                                               TestMathHighOperation::GCASE_X_00) << std::endl;
    std::cout << TestMathHighOperation::Jacobi(TestMathHighOperation::GCASE_A_01,
                                               TestMathHighOperation::GCASE_B_01,
                                               TestMathHighOperation::GCASE_X_01) << std::endl;
    std::cout << TestMathHighOperation::Seidel(TestMathHighOperation::GCASE_A_00,
                                               TestMathHighOperation::GCASE_B_00,
                                               TestMathHighOperation::GCASE_X_00) << std::endl;
    std::cout << TestMathHighOperation::Seidel(TestMathHighOperation::GCASE_A_01,
                                               TestMathHighOperation::GCASE_B_01,
                                               TestMathHighOperation::GCASE_X_01) << std::endl;
#endif

#if 0
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

	std::cout << x.transp() << std::endl;
#endif
    //matrixtest::make();
	return 0;
}


