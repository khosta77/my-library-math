#include "test_base_operation.h"

bool TestBaseOperations::Constructor00() {
    Matrix M;
    return M.isNull();
}

bool TestBaseOperations::ConstructorXX() {
    const auto _rows = utils::genSizeT(1);
    const auto _cols = utils::genSizeT(1);
    Matrix M(_rows, _cols);
    if (M.isNull())
        return false;
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            if (M(i, j) != 0)
                return false;
    return true;
}

bool TestBaseOperations::ConstructorStream(const std::string &fn) {
    std::ifstream in(fn.c_str());
    try {
        Matrix M(in);
        if (M.isNull())
            return false;
        in.close();
        std::ifstream in2(fn.c_str());
        const utils::MatrixData expected_matrix = utils::createMatrixData(in2);
        in2.close();
        return utils::operator==(expected_matrix, M);
    } catch (const InvalidMatrixStream &eIMS) {
        in.close();
        return true;
    } catch (...) {
        in.close();
        return false;
    };
    in.close();
    return false;
}

bool TestBaseOperations::ConstructorCopy(const std::string &fn) {
    std::ifstream in(fn.c_str());
    std::ifstream in2(fn.c_str());
    const utils::MatrixData expected_matrix = utils::createMatrixData(in2);
    in2.close();
    try {
        Matrix M1(in);
        in.close();
        if (M1.isNull())
            return false;
        Matrix M2(M1);
        if (M2.isNull())
            return false;
        return utils::operator==(expected_matrix, M2);
    } catch (...) {
        in.close();
        return false;
    };
    in.close();
    return false;
}

bool TestBaseOperations::EquallyCall(const std::string &fn) {
    std::ifstream in(fn.c_str());
    std::ifstream in2(fn.c_str());
    const utils::MatrixData expected_matrix = utils::createMatrixData(in2);
    in2.close();

    try {
        Matrix M1(in);
        in.close();
        if (M1.isNull())
            return false;
        Matrix M2;
        M2 = M1;
        if (M2.isNull())
            return false;
        return utils::operator==(expected_matrix, M2);
    } catch (...) {
        in.close();
        return false;
    };
    in.close();
    return false;
}

bool TestBaseOperations::CheckGetterRowCol() {
    const size_t _rows = utils::genSizeT(1);
    const size_t _cols = utils::genSizeT(1);

    Matrix M(_rows, _cols);
    if (M.isNull())
        return false;

    if ((M.getCols() == _cols) && (M.getRows() == _rows))
        return true;
    return false;
}

bool TestBaseOperations::AccessControl() {
    Matrix M;
    try {
        M = utils::genMatrix();
    } catch (...) {
        return false;
    }

    double b;
    try {
        for (size_t i = 0; i < M.getRows(); ++i) {
            for (size_t j = 0; j < M.getCols(); ++j) {
                b = M(i, j);
                if (M(i, j) != b)
                    return false;
                b += 1.0;
                M(i, j) += 1.0;
                if (M(i, j) != b)
                    return false;
            }
        }
    } catch (...) {
        return false;
    }

    bool tester = true;
    try {
        b = M((M.getRows() + 1), 0);
    } catch (const OutOfRange &eOOR) {
        tester = true;
    } catch (...) {
        return false;
    }
    try {
        b = M(0, (M.getCols() + 1));
    } catch (const OutOfRange &eOOR) {
        tester = true;
    } catch (...) {
        return false;
    }
    return tester;
}

bool TestBaseOperations::CheckingFlow() {
    std::string fn = "./flow_test.txt";
    const Matrix M = utils::genMatrix();
    std::ofstream out(fn.c_str(), (std::ios_base::binary | std::ios_base::trunc | std::ios_base::out));
    try {
        out << M;
    } catch (...) {
        out.close();
        std::filesystem::remove(fn.c_str());
        return false;
    }
    out.close();

    std::ifstream in(fn.c_str(), (std::ios_base::in));
    const utils::MatrixData expected_matrix = utils::createMatrixData(in);
    in.close();
    std::filesystem::remove(fn.c_str());
    try {
        return utils::operator==(expected_matrix, M);
    } catch (...) {}
    return false;
}


