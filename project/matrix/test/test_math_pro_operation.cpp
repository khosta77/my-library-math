#include "test_math_pro_operation.h"

// TODO придумать тест для проверки минора

bool TestMathProOperations::Transp() {
    const Matrix a = utils::genMatrix();
    Matrix b;
    try {
        b = a.transp();
    } catch (...) {
        return false;
    }

    if ((a.getRows() != b.getCols()) || (a.getCols() != b.getRows()))
        return false;

    for (size_t i = 0; i < b.getRows(); ++i)
        for (size_t j = 0; j < b.getCols(); ++j)
            if (a(j, i) != b(i, j))
                return false;
    return true;
}

bool TestMathProOperations::Det(const std::string &m, const std::string &d) {
    const Matrix a = utils::readFromFile(m);
    double x = 0.0;
    try {
        x = a.det();
    } catch (const DimensionMismatch &eDM) {
        return ((d.empty()) ? true : false);
    } catch (...) {
        return false;
    }
    std::ifstream in(d.c_str(), (std::ios_base::in));
    double control = 0.0;
    in >> control;
    in.close();

    return (std::abs(x - control) < 1e-7);
}

bool TestMathProOperations::Adj(const std::string &in, const std::string &out) {
    const Matrix a = utils::readFromFile(in);
    Matrix res;
    try {
        res = a.adj();
    } catch (const DimensionMismatch &eDM) {
        try {    a.det(); }
        catch (const DimensionMismatch &eDM) {    return true; }
        catch (...) {    return false; }
        return false;
    } catch (const SingularMatrix &eSM) {
        double buffer = 0.0;
        try {    buffer = a.det(); }
        catch (const DimensionMismatch &eDM) {    return true; }
        catch (...) {    return false; }
        return ((std::abs(buffer - 0.0000000) < 1e-7) ? true : false);
    } catch (...) {    return false;}
    const Matrix b = utils::readFromFile(out);
    return (res == b);
}

bool TestMathProOperations::Inv(const std::string &in, const std::string &out) {
    const Matrix a = utils::readFromFile(in);
    Matrix res;
    try {
        res = a.inv();
    } catch (const DimensionMismatch &eDM) {
        try {    a.det(); }
        catch (const DimensionMismatch &eDM) {    return true; }
        catch (...) {    return false; }
        return false;
    } catch (const SingularMatrix &eSM) {
        double buffer = 0.0;
        try {    buffer = a.det(); }
        catch (const DimensionMismatch &eDM) {    return true; }
        catch (...) {    return false; }
        return ((std::abs(buffer - 0.0000000) < 1e-7) ? true : false);
    } catch (...) {    return false;}
    const Matrix b = utils::readFromFile(out);
    return (res == b);
}


