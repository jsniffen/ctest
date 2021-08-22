#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

static bool total_pass = true;
static bool pass = true;
static bool verbose = false;

static char global_file[256];
static char global_func[256];
static char global_message[256];
static int global_line;

#define Errorf(msg, ...) _Errorf(__func__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
void _Errorf(const char *func, char *file, int line, const char *msg, ...) {
	strcpy(global_file, file);
	strcpy(global_func, func);
	global_line = line;

	pass = false;

	va_list ap;
	va_start(ap, msg);
	vsprintf(global_message, msg, ap);
	va_end(ap);
}

#define TestMain(fargs...) void main(int argv, char **args) {_TestMain(argv, args, __FILE__, #fargs, fargs, 0);}
void _TestMain(int argv, char **args, char *file, char *fargs, ...) {
	double total_time = 0;

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

		clock_t start = clock();
		(*func)();
		clock_t end = clock();
		double time = ((double) (end - start)) / CLOCKS_PER_SEC;
		total_time += time;

		if (pass) {
			if (verbose) printf("--- PASS:  %s (%0.3fs)\n", pch, time);
		} else {
			total_pass = false;

			if (verbose) {
				printf("    %s:%d: %s\n", global_file, global_line, global_message);
				printf("--- FAIL:  %s (%0.3fs)\n", pch, time);
			} else {
				printf("--- FAIL:  %s (%0.3fs)\n", pch, time);
				printf("    %s:%d: %s\n", global_file, global_line, global_message);
			}
		}

		pch = strtok(0, " ,");
	}
	va_end(ap);

	if (total_pass) {
		printf("PASS\nok\t%s\n", file);
	} else {
		printf("FAIL\t%s\t%0.3fs\n", file, total_time);
	}
}

