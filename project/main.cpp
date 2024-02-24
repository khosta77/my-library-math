#include <iostream>

#include "./StepanTestScriptLibrary/project/StepanTestScriptLibrary.h"

inline int sum(const int &a, const int &b) {
	return (a + b);
}

bool test_sum(const int &d1, const int &d2, const int& answer) {
	auto A = sum(d1, d2);
	if (A == answer)
		return true;
	return false;
}

int main() {
    STSL::TrueTest tt(true, 1, std::string("Ефимов Ефим Ефимович"));
	tt.NewGroup("Sum");
	tt.mt(test_sum(0, 0, 0));
	tt.mt(test_sum(1, 1, 2));
	tt.mt(test_sum(2, 3, 5));
	tt.NewGroup("Error");
	tt.mt(test_sum(0, 0, 0));
	tt.mt(test_sum(1, 1, 3));
	tt.mt(test_sum(2, 3, 5));
	tt.result_to_tex();
	return 0;
}


