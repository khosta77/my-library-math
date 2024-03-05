#include "test_math_high_operation.h"

const std::string& PATH = "./project/matrix/data/math_high_operation/";
const std::string& PREFIX_A = "/A.txt";
const std::string& PREFIX_B = "/B.txt";
const std::string& PREFIX_X = "/X.txt";

const std::string& PATHG = (PATH + "Gausse/case_");

bool TestMathHighOperation::Gausse() {
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

const std::string& PATHT = (PATH + "RunThrough/case_");
const std::string& PREFIX_C = "/C.txt";
const std::string& PREFIX_Y = "/Y.txt";

bool TestMathHighOperation::RunThrough() {
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
        return ((X.isNull()) ? true : false);
    } catch (...) {
        return false;
    }
    return (x == X);
}

const std::string& PATHJ = (PATH + "Jacobi/case_");

bool TestMathHighOperation::Jacobi() {
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

const std::string& PATHS = (PATH + "Seidel/case_");

bool TestMathHighOperation::Seidel() {
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


