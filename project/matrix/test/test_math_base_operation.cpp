#include "test_math_base_operation.h"

bool TestMathBaseOperations::EqualYes() {
    const Matrix M1 = utils::genMatrix();
    const Matrix M2(M1);
    return ((M1 == M2) ? true : false);
}

bool TestMathBaseOperations::EqualNo() {
    const Matrix M1 = utils::genMatrix();
    const Matrix M2 = utils::genMatrix();
    return ((M1 == M2) ? false : true);
}

bool TestMathBaseOperations::NoEqualYes() {
    const Matrix M1 = utils::genMatrix();
    const Matrix M2(M1);
    return ((M1 != M2) ? false : true);
}

bool TestMathBaseOperations::NoEqualNo() {
    const Matrix M1 = utils::genMatrix();
    const Matrix M2 = utils::genMatrix();
    return ((M1 != M2) ? true : false);
}
    
bool TestMathBaseOperations::Sum(const std::string &A, const std::string &B, const std::string &X) {
    const Matrix a = utils::readFromFile(A);
    const Matrix b = utils::readFromFile(B);
    const Matrix x = utils::readFromFile(X);
    Matrix sum;
    try {
        sum = (a + b);
    } catch (...) {
        return false;
    }
    return (sum == x);
}

bool TestMathBaseOperations::ErrorSum() {
    const Matrix a = utils::genMatrix();
    const Matrix b = utils::genMatrix((a.getRows() + utils::genSizeT(1)), a.getCols());
    Matrix sum;
    try {
        sum = (a + b);
    } catch (const DimensionMismatch &eDM) {
        return true;
    } catch (...) {}
    return false;
}

bool TestMathBaseOperations::Sub(const std::string &A, const std::string &B, const std::string &X) {
    const Matrix a = utils::readFromFile(A);
    const Matrix b = utils::readFromFile(B);
    const Matrix x = utils::readFromFile(X);
    Matrix sub;
    try {
        sub = (a - b);
    } catch (...) {
        return false;
    }
    return (sub == x);
}

bool TestMathBaseOperations::ErrorSub() {
    const Matrix a = utils::genMatrix();
    const Matrix b = utils::genMatrix((a.getRows() + utils::genSizeT(1)), a.getCols());
    Matrix sub;
    try {
        sub = (a - b);
    } catch (const DimensionMismatch &eDM) {
        return true;
    } catch (...) {}
    return false;
}

bool TestMathBaseOperations::Scalar(const std::string &A, const std::string &B, const std::string &X) {
    const Matrix a = utils::readFromFile(A);
    const Matrix b = utils::readFromFile(B);
    const Matrix x = utils::readFromFile(X);
    Matrix scalar;
    try {
        scalar = (a * b);
    } catch (...) {
        return false;
    }
    return (scalar == x);
}

bool TestMathBaseOperations::ErrorScalar() {
    const Matrix a = utils::genMatrix();
    const Matrix b = utils::genMatrix((a.getCols() + utils::genSizeT(1)), a.getRows());
    Matrix scalar;
    try {
        scalar = (a * b);
    } catch (const DimensionMismatch &eDM) {
        return true;
    } catch (...) {}
    return false;
}

bool TestMathBaseOperations::ScalarMX() {
    Matrix a = utils::genMatrix();
    Matrix b = a;
    const double coef = utils::genDouble();
    Matrix x;
    try {
        x = (a * coef);
    } catch (...) {
        return false;
    }
    for (size_t i = 0; i < b.getRows(); ++i) {
        for (size_t j = 0; j < b.getCols(); ++j) {
            b(i, j) *= coef;
        }
    }
    return (x == b);
}

bool TestMathBaseOperations::ScalarXM() {
    Matrix a = utils::genMatrix();
    Matrix b = a;
    const double coef = utils::genDouble();
    Matrix x;
    try {
        x = (a * coef);
    } catch (...) {
        return false;
    }
    for (size_t i = 0; i < b.getRows(); ++i) {
        for (size_t j = 0; j < b.getCols(); ++j) {
            b(i, j) *= coef;
        }
    }
    return (x == b);
}


