#include "stdio.h"
#include "stdarg.h"

int multiply(int n, ...) {
	int result = 1;
	va_list factor;
	va_start(factor, n);
	for (int i = 1; i < n; i++) {
		result *= va_arg(factor, int);
	}
	va_end(factor);
	return result;
}