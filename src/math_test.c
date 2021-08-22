#include "test.h"
#include "math.c"

void TestAbsNegative() {
	int got = Abs(-1);
	if (got != 1) {
		Errorf("Abs(-1) = %d; want 1", got);
	}
}

void TestAbsPositive() {
	int got = Abs(1);
	if (got != 1) {
		Errorf("Abs(1) = %d; want 1", got);
	}
}

TestMain(TestAbsNegative, TestAbsPositive);
