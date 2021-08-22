#include "test.h"
#include "math.c"

void TestAbs() {
	int got = Abs(-1);
	if (got != 1) {
		Errorf("Abs(-1) = %d; want 1\n", got);
	}
}

void TestAbs2() {
	int got = Abs(1);
	if (got != 1) {
		Errorf("Abs(-1) = %d; want 1\n", got);
	}
}

TestMain(TestAbs, TestAbs2);
