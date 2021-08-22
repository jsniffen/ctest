#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static bool total_pass = true;
static bool pass = true;
static bool verbose = false;

#define Errorf(msg, ...) _Errorf(__func__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
void _Errorf(const char *func, char *file, int line, const char *msg, ...) {
	pass = false;

	if (!verbose) printf("--- FAIL: %s\n", func);

	printf("    %s:%d: ", file, line);
	va_list ap;
	va_start(ap, msg);
	vprintf(msg, ap);
	va_end(ap);
}

#define AssertIntEquals(x, y) _AssertEquals(x, y, #x, #y, __FILE__, __func__, __LINE__)
bool _AssertEquals(int x, int y, char *x_name, char *y_name, char *file, const char *func, int line) {
	if (x != y) {
		printf("--- FAIL: %s %s == %s\n", func, x_name, y_name);
		printf("    expected: %d, got %d\n", x, y);
		printf("    %s:%d\n", file, line);
	}
	return false;
}

# define Assert(exp) _Assert(exp, #exp, __FILE__, __func__, __LINE__)
bool _Assert(bool pass, char *exp, char *file, const char *func, int line) {
	if (!pass) {
		printf("--- FAIL: %s %s\n", func, exp);
		printf("    %s:%d\n", file, line);
	}

	return pass;
}

#define Run(...) _Run(__FILE__, __VA_ARGS__, 0)
void _Run(char *file, ...) {
	va_list ap;
	va_start(ap, file);
	bool (*func)();
	while ((func = va_arg(ap, bool(*)())) != 0) {
		(*func)();
	}
	va_end(ap);

	if (pass) {
		printf("PASS\nok\t%s\n", file);
	} else {
		printf("FAIL\nFAIL\t%s\n", file);
	}
}

#define Test(args...) _Test(#args, args)
void _Test(char *args, ...) {
	printf("%s\n", args);
}

#define TestMain(fargs...) void main(int argv, char **args) {_TestMain(argv, args, __FILE__, #fargs, fargs, 0);}
void _TestMain(int argv, char **args, char *file, char *fargs, ...) {
	for (int i = 0; i < argv; ++i) {
		if (strcmp(args[i], "-v") == 0) {
			verbose = true;
		}
	}

	va_list ap;
	va_start(ap, fargs);
	bool (*func)();

	char buffer[1024];
	strcpy(buffer, fargs);
	char *pch = strtok(buffer, ",");
	while ((func = va_arg(ap, bool(*)())) != 0) {
		pass = true;
		if (verbose) {
			printf("=== RUN    %s\n", pch);
		}
		(*func)();

		if (pass) {
			if (verbose) printf("--- PASS:  %s\n", pch);
		} else {
			total_pass = false;
			if (verbose) printf("--- FAIL:  %s\n", pch);
		}

		pch = strtok(0, " ,");
	}
	va_end(ap);

	if (total_pass) {
		printf("PASS\nok\t%s\n", file);
	} else {
		printf("FAIL\t%s\n", file);
	}
}

