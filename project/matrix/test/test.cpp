#include "test.h"

static STSL::TrueTest tt(true, 0, std::string("Филимонов Степан"));


void matrixtest::baseOperation() {
	tt.NewGroup("Base operation");
	tt.mt(TestBaseOperations::Constructor00());
	tt.mt(TestBaseOperations::ConstructorXX());
	tt.mt(TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_00));
	tt.mt(TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_01));
	tt.mt(TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_02));
	tt.mt(TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_03));
	tt.mt(TestBaseOperations::ConstructorStream(TestBaseOperations::FN_MC_04));
	tt.mt(TestBaseOperations::ConstructorCopy(TestBaseOperations::FN_MC_00));
	tt.mt(TestBaseOperations::ConstructorCopy(TestBaseOperations::FN_MC_01));
	tt.mt(TestBaseOperations::EquallyCall(TestBaseOperations::FN_MC_00));
	tt.mt(TestBaseOperations::EquallyCall(TestBaseOperations::FN_MC_01));
	tt.mt(TestBaseOperations::CheckGetterRowCol());
	tt.mt(TestBaseOperations::AccessControl());
	tt.mt(TestBaseOperations::CheckingFlow());
}

void matrixtest::mathBaseOperation() {
	tt.NewGroup("Math base operation");
	tt.mt(TestMathBaseOperations::EqualYes());
	tt.mt(TestMathBaseOperations::EqualNo());
	tt.mt(TestMathBaseOperations::NoEqualYes());
	tt.mt(TestMathBaseOperations::NoEqualNo());
	tt.mt(TestMathBaseOperations::Sum(TestMathBaseOperations::FN_A_SUM_00,                                          
									  TestMathBaseOperations::FN_B_SUM_00,
                                      TestMathBaseOperations::FN_X_SUM_00));
	tt.mt(TestMathBaseOperations::ErrorSum());
	tt.mt(TestMathBaseOperations::Sub(TestMathBaseOperations::FN_A_SUB_00,
								   	  TestMathBaseOperations::FN_B_SUB_00,
                                      TestMathBaseOperations::FN_X_SUB_00));
	tt.mt(TestMathBaseOperations::ErrorSub());
	tt.mt(TestMathBaseOperations::Scalar(TestMathBaseOperations::FN_A_SCA_00,
                                         TestMathBaseOperations::FN_B_SCA_00,
                                         TestMathBaseOperations::FN_X_SCA_00));
	tt.mt(TestMathBaseOperations::Scalar(TestMathBaseOperations::FN_A_SCA_00,
										 TestMathBaseOperations::FN_B_SCA_01,
                                         TestMathBaseOperations::FN_X_SCA_01));
	tt.mt(TestMathBaseOperations::ErrorScalar());
	tt.mt(TestMathBaseOperations::ScalarMX());
	tt.mt(TestMathBaseOperations::ScalarXM());
}

void matrixtest::mathProOperation() {
	tt.NewGroup("Math pro operation");
	tt.mt(TestMathProOperations::Transp());
	tt.mt(TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__00,
                                     TestMathProOperations::FN_DET_OUT_00));
	tt.mt(TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__01,
                                     TestMathProOperations::FN_DET_OUT_01));
	tt.mt(TestMathProOperations::Det(TestMathProOperations::FN_DET_IN__02,
                                     TestMathProOperations::FN_DET_OUT_02));
	tt.mt(TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__00,
                                     TestMathProOperations::FN_ADJ_OUT_00));
	tt.mt(TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__01,
                                     TestMathProOperations::FN_ADJ_OUT_01));
	tt.mt(TestMathProOperations::Adj(TestMathProOperations::FN_ADJ_IN__02,
                                     TestMathProOperations::FN_ADJ_OUT_02));
	tt.mt(TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__00,
                                     TestMathProOperations::FN_INV_OUT_00));
	tt.mt(TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__01,
									 TestMathProOperations::FN_INV_OUT_01));
	tt.mt(TestMathProOperations::Inv(TestMathProOperations::FN_INV_IN__02,
                                     TestMathProOperations::FN_INV_OUT_02));
}
	
void matrixtest::make() {
	baseOperation();
	mathBaseOperation();
	mathProOperation();
    tt.result_to_terminal();
}


