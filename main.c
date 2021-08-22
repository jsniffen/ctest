#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define COMPILER "gcc"
#define COMPILER_FLAGS "-std=c99"

void test(char *filename) {
	char cmd[256];
	sprintf(cmd, "%s %s %s -o test", COMPILER, COMPILER_FLAGS, filename);
	system(cmd);
	system("./test");
	system("rm -rf test");
	return;
}

int main(int argc, char *argv[]) {
	char *fn = "src/math_test.c";

	FILE *fp = fopen(fn, "r");
	if (fp == 0) {
		printf("invalid file\n");
		return -1;
	}

	char *line = 0;
	int len;
	ssize_t read;

	while ((read = getline(&line, &len, fp)) != -1) {
		printf("%s", line);
	}

	return 0;
}
