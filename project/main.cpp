#include <iostream>
#include <random>
#include <filesystem>
#include <fstream>
//#include "./StepanTestScriptLibrary/project/StepanTestScriptLibrary.h"

#include <vector>
#include "./matrix/matrix.h"
#include "./matrix/exceptions.h"

//// utils.h

namespace utils {
    using MatrixData = std::vector<std::vector<double>>;
    using MatrixRow = std::vector<double>;

    MatrixData createMatrixData(std::istream& is);
    std::ostream& operator<<(std::ostream& os, const MatrixData& matrix_data);

    const size_t MAX_SIZE = 10;
    [[maybe_unused]] const double MIN_VAL = -100.0;
    [[maybe_unused]] const double MAX_VAL = 100.0;

    double genDouble(double from = MIN_VAL, double to = MAX_VAL);
    size_t genSizeT(size_t from = 0, size_t to = MAX_SIZE);
    Matrix genMatrix(size_t rows = 0, size_t cols = 0);
    Matrix readFromFile(const std::string &fn);

    static std::random_device engine;

    bool operator==(const Matrix &matrix, const MatrixData &matrix_data);
    bool operator==(const MatrixData &matrix_data, const Matrix &matrix);

    MatrixData createMatrixData(std::istream &is) {
        size_t rows = 0;
        size_t cols = 0;

        is >> rows >> cols;
        if (!is) {
            throw std::runtime_error("MatrixData чтение не удалось");
        }

        MatrixData matrix_data(rows, MatrixRow(cols, 0.0));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                is >> matrix_data[i][j];
                if (!is) {
                    throw std::runtime_error("MatrixData чтение с ошибкой");
                }
            }
        }

        return matrix_data;
    }

    std::ostream& operator<<(std::ostream &os, const MatrixData &matrix_data) {
        auto rows = matrix_data.size();
        auto cols = matrix_data[0].size();

        os << rows << ' ' << cols << std::endl;

        for (auto& row: matrix_data) {
            for (auto& data: row) {
                os << data << ' ';
            }
            os << std::endl;
        }

        return os;
    }

    bool operator==(const Matrix &matrix, const MatrixData &matrix_data) {
        auto rows = matrix_data.size();
        auto cols = matrix_data[0].size();

        if (matrix.getRows() != rows || matrix.getCols() != cols) {
            return false;
        }

        for (size_t i = 0; i < matrix_data.size(); ++i) {
            for (size_t j = 0; j < matrix_data[i].size(); ++j) {
                if (matrix(i, j) != matrix_data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator==(const MatrixData &matrix_data, const Matrix &matrix) {
        return matrix == matrix_data;
    }

    double genDouble(double from, double to) {
        return std::uniform_real_distribution<double>(from, to)(engine);
    }

    size_t genSizeT(size_t from, size_t to) {
        return std::uniform_int_distribution<size_t>(from, to)(engine);
    }

    Matrix genMatrix(size_t rows, size_t cols) {
        size_t rows_ = rows ? rows : genSizeT(1);
        size_t cols_ = cols ? cols : genSizeT(1);

        Matrix matrix(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                matrix(i, j) = genDouble();
            }
        }

        return matrix;
    }

    Matrix readFromFile(const std::string &fn) {
        std::ifstream in(fn.c_str(), (std::ios_base::in));
        Matrix matrix(in);
        in.close();
        return matrix;
    }


};

//// base test

namespace TestBaseOperations {
    
    /** @brief Тест конструктора с параметрами 0х0. Если не нулевая то вернет false, так же проверка метода
     *         isNull()
     */
    bool Constructor00() {
        Matrix M;
        return M.isNull();
    }

    /** @brief Тест конструктора с параметрами XxX. Если метод isNull возвращает true, та значит массив не
     *         создан, тест не пройден. После осуществляется проверка заполнения матрицы нулями, если хотя 
     *         бы одно значение не нулевой, вернуть false.
     * */
    bool ConstructorXX() {
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

    const std::string FN_MC_00 = "./project/matrix/data/base_operation/matrix_creation/case_0.txt";
    const std::string FN_MC_01 = "./project/matrix/data/base_operation/matrix_creation/case_1.txt";
    const std::string FN_MC_02 = "./project/matrix/data/base_operation/matrix_creation_neg/bad_format.txt";
    const std::string FN_MC_03 = "./project/matrix/data/base_operation/matrix_creation_neg/corrupted_data.txt";
    const std::string FN_MC_04 = "./project/matrix/data/base_operation/matrix_creation_neg/empty_file.txt";

    /** @brief Тест ошибки при чтении, когда мы передаем файл.
     * */
    bool ConstructorStream(const std::string &fn) {
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

    /** @brief Тест конструктора копирования
     * */
    bool ConstructorCopy(const std::string &fn) {
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

    /** @brief тест перегрузки оператора =
     * */
    bool EquallyCall(const std::string &fn) {
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

    /** @brief Тест получения колонок и строк
     * */
    bool CheckGetterRowCol() {
        const size_t _rows = utils::genSizeT(1);
        const size_t _cols = utils::genSizeT(1);
        
        Matrix M(_rows, _cols);
        if (M.isNull())
            return false;

        if ((M.getCols() == _cols) && (M.getRows() == _rows))
            return true;
        return false;
    }

    /** @brief Тест перегруженного оператора доступа ()
     * */
    bool AccessControl() {
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

    /** @brief Тест потока вывода
     * */
    bool CheckingFlow() {
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

};

//// base operation

namespace TestMathBaseOperations {
    /** @brief тест оператора ==
     * */
    bool EqualYes() {
        const Matrix M1 = utils::genMatrix();
        const Matrix M2(M1);
        return ((M1 == M2) ? true : false);
    }

    /** @brief тест оператора ==
     * */
    bool EqualNo() {
        const Matrix M1 = utils::genMatrix();
        const Matrix M2 = utils::genMatrix();
        return ((M1 == M2) ? false : true);
    }

    /** @brief тест оператора !=
     * */
    bool NoEqualYes() {
        const Matrix M1 = utils::genMatrix();
        const Matrix M2(M1);
        return ((M1 != M2) ? false : true);
    }

    /** @brief тест оператора !=
     * */
    bool NoEqualNo() {
        const Matrix M1 = utils::genMatrix();
        const Matrix M2 = utils::genMatrix();
        return ((M1 != M2) ? true : false);
    }
    const std::string FN_PATH = "./project/matrix/data/math_base_operation/matrix_";

    //// SUM
    const std::string FN_A_SUM_00 = (FN_PATH + "sum/case_a_00.txt");
    const std::string FN_B_SUM_00 = (FN_PATH + "sum/case_b_00.txt");
    const std::string FN_X_SUM_00 = (FN_PATH + "sum/case_x_00.txt");
    
    //// SUB
    const std::string FN_A_SUB_00 = (FN_PATH + "sub/case_a_00.txt");
    const std::string FN_B_SUB_00 = (FN_PATH + "sub/case_b_00.txt");
    const std::string FN_X_SUB_00 = (FN_PATH + "sub/case_x_00.txt");
  
    //// SCALAR
    const std::string FN_A_SCA_00 = (FN_PATH + "scalar/case_a_00.txt");
    const std::string FN_B_SCA_00 = (FN_PATH + "scalar/case_b_00.txt");
    const std::string FN_B_SCA_01 = (FN_PATH + "scalar/case_b_01.txt");
    const std::string FN_X_SCA_00 = (FN_PATH + "scalar/case_x_00.txt");
    const std::string FN_X_SCA_01 = (FN_PATH + "scalar/case_x_01.txt");

    /** @brief Тест оператора +
     * */
    bool Sum(const std::string &A, const std::string &B, const std::string &X) {
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

    /** @brief Тест оператора +
     * */
    bool ErrorSum() {
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

    /** @brief Тест оператора -
     * */
    bool Sub(const std::string &A, const std::string &B, const std::string &X) {
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

    /** @brief Тест оператора -
     * */
    bool ErrorSub() {
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

    /** @brief Тест оператора M * M
     * */
    bool Scalar(const std::string &A, const std::string &B, const std::string &X) {
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

    /** @brief Тест оператора M * M
     * */
    bool ErrorScalar() {
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

    /** @brief Тест умножения матрицы на число
     * */
    bool ScalarMX() {
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

    /** @brief Тест умножения матрицы на число
     * */
    bool ScalarXM() {
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
};

//// pro opration

namespace TestMathProOperations {
    //// TODO придумать тест для проверки минора

    bool Transp() {
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

    const std::string FN_PATH = "./project/matrix/data/math_pro_operation/matrix_";

    //// Det
    const std::string FN_DET_IN__00 = (FN_PATH + "det/case_0/in.txt");
    const std::string FN_DET_OUT_00 = (FN_PATH + "det/case_0/out.txt");
    const std::string FN_DET_IN__01 = (FN_PATH + "det/case_1/in.txt");
    const std::string FN_DET_OUT_01 = (FN_PATH + "det/case_1/out.txt");
    const std::string FN_DET_IN__02 = (FN_PATH + "det/case_2/in.txt");
    const std::string FN_DET_OUT_02 = "";


    bool Det(const std::string &m, const std::string &d = "") {
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

    const std::string FN_ADJ_IN__00 = (FN_PATH + "adj/case_0/in.txt");
    const std::string FN_ADJ_OUT_00 = (FN_PATH + "adj/case_0/out.txt");
    const std::string FN_ADJ_IN__01 = (FN_PATH + "adj/case_1/in.txt");
    const std::string FN_ADJ_OUT_01 = (FN_PATH + "adj/case_1/out.txt");
    const std::string FN_ADJ_IN__02 = (FN_PATH + "adj/case_2/in.txt");
    const std::string FN_ADJ_OUT_02 = (FN_PATH + "adj/case_2/out.txt");

    bool Adj(const std::string &in, const std::string &out) {
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

    const std::string FN_INV_IN__00 = (FN_PATH + "inv/case_0/in.txt");
    const std::string FN_INV_OUT_00 = (FN_PATH + "inv/case_0/out.txt");
    const std::string FN_INV_IN__01 = (FN_PATH + "inv/case_1/in.txt");
    const std::string FN_INV_OUT_01 = (FN_PATH + "inv/case_1/out.txt");
    const std::string FN_INV_IN__02 = (FN_PATH + "inv/case_2/in.txt");
    const std::string FN_INV_OUT_02 = (FN_PATH + "inv/case_2/out.txt");

    bool Inv(const std::string &in, const std::string &out) {
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

};

//// SLE

int main() {
#if 0  // TestBaseOperations
    std::cout << TestBaseOperations::Constructor00() << std::endl;
    std::cout << TestBaseOperations::ConstructorXX() << std::endl;
    std::cout << TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_00) << std::endl;
    std::cout << TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_01) << std::endl;
    std::cout << TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_02) << std::endl;
    std::cout << TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_03) << std::endl;
    std::cout << TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_04) << std::endl;
    std::cout << TestBaseOperations::ConstructorCopy(TestBaseOperations::FN_MC_00) << std::endl;
    std::cout << TestBaseOperations::ConstructorCopy(TestBaseOperations::FN_MC_01) << std::endl;
    std::cout << TestBaseOperations::EquallyCall(TestBaseOperations::FN_MC_00) << std::endl;
    std::cout << TestBaseOperations::EquallyCall(TestBaseOperations::FN_MC_01) << std::endl;
    std::cout << TestBaseOperations::CheckGetterRowCol() << std::endl;
    std::cout << TestBaseOperations::AccessControl() << std::endl;
    std::cout << TestBaseOperations::CheckingFlow() << std::endl;
#endif

#if 0  // TestMathBaseOperations
    std::cout << TestMathBaseOperations::EqualYes() << std::endl;
    std::cout << TestMathBaseOperations::EqualNo() << std::endl;
    std::cout << TestMathBaseOperations::NoEqualYes() << std::endl;
    std::cout << TestMathBaseOperations::NoEqualNo() << std::endl;
    std::cout << TestMathBaseOperations::Sum(TestMathBaseOperations::FN_A_SUM_00,
                                             TestMathBaseOperations::FN_B_SUM_00,
                                             TestMathBaseOperations::FN_X_SUM_00) << std::endl;
    std::cout << TestMathBaseOperations::ErrorSum() << std::endl;
    std::cout << TestMathBaseOperations::Sub(TestMathBaseOperations::FN_A_SUB_00,
                                             TestMathBaseOperations::FN_B_SUB_00,
                                             TestMathBaseOperations::FN_X_SUB_00) << std::endl;
    std::cout << TestMathBaseOperations::ErrorSub() << std::endl;
    std::cout << TestMathBaseOperations::Scalar(TestMathBaseOperations::FN_A_SCA_00,
                                                TestMathBaseOperations::FN_B_SCA_00,
                                                TestMathBaseOperations::FN_X_SCA_00) << std::endl;
    std::cout << TestMathBaseOperations::Scalar(TestMathBaseOperations::FN_A_SCA_00,
                                                TestMathBaseOperations::FN_B_SCA_01,
                                                TestMathBaseOperations::FN_X_SCA_01) << std::endl;
    std::cout << TestMathBaseOperations::ErrorScalar() << std::endl;
    std::cout << TestMathBaseOperations::ScalarMX() << std::endl;
    std::cout << TestMathBaseOperations::ScalarXM() << std::endl;
#endif

#if 1  // TestMathProOperations
    std::cout << TestMathProOperations::Transp() << std::endl;
    std::cout << TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__00,
                                            TestMathProOperations::FN_DET_OUT_00) << std::endl;
    std::cout << TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__01,
                                            TestMathProOperations::FN_DET_OUT_01) << std::endl;
    std::cout << TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__02,
                                            TestMathProOperations::FN_DET_OUT_02) << std::endl;
    std::cout << TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__00,
                                            TestMathProOperations::FN_ADJ_OUT_00) << std::endl;
    std::cout << TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__01,
                                            TestMathProOperations::FN_ADJ_OUT_01) << std::endl;
    std::cout << TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__02,
                                            TestMathProOperations::FN_ADJ_OUT_02) << std::endl;
    std::cout << TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__00,
                                            TestMathProOperations::FN_INV_OUT_00) << std::endl;
    std::cout << TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__01,
                                            TestMathProOperations::FN_INV_OUT_01) << std::endl;
    std::cout << TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__02,
                                            TestMathProOperations::FN_INV_OUT_02) << std::endl;
#endif
#if 0
	Matrix A(4, 4);

	A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3; A(0, 3) = 4;
	A(1, 0) = 3; A(1, 1) = 5; A(1, 2) = 1; A(1, 3) = 7;
	A(2, 0) = 4; A(2, 1) = 1; A(2, 2) = 0; A(2, 3) = -1;
	A(3, 0) = 2; A(3, 1) = 2; A(3, 2) = 2; A(3, 3) = 3;

	Matrix B(4, 1);
	B(0, 0) = 22; B(1, 0) = 38; B(2, 0) = 8; B(3, 0) = 20;
	Matrix x = SLEmethodGauss(A, B);

	std::cout << x.transp() << std::endl;
#endif
	return 0;
}


