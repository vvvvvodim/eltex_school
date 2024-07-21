#include "stdio.h"
#include "stdarg.h"

int add(int n, ...) {
	int result = 0;
	va_list factor;
	va_start(factor, n);
	for (int i = 0; i < n; i++) {
		result += va_arg(factor, int);
	}
	va_end(factor);
	return result;
}