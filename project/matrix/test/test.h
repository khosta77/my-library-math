#ifndef TEST_H_
#define TEST_H_

#include "utils.h"
#include "test_base_operation.h"
#include "test_math_base_operation.h"
#include "test_math_pro_operation.h"
#include "test_math_high_operation.h"

#include "../../StepanTestScriptLibrary/project/StepanTestScriptLibrary.h"

namespace matrixtest {

	void baseOperation();

	void mathBaseOperation();

	void mathProOperation();

	void mathHighOperation();
	
	void make();

};  // matrixtest

#endif  // TEST_H_
