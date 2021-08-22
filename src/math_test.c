#include "test.h"
#include "math.c"

void TestAbs() {
	int got = Abs(-1);
	if (got != 1) {
		Errorf("Abs(-1) = %d; want 1", got);
	}
}

void TestAbs2() {
	Fail();
	int got = Abs(1);
	if (got != 0) {
	}
}

TestMain(TestAbs, TestAbs2);
