#include "stdio.h"
#include "stdarg.h"

int subtract(int n, ...) {
	va_list factor;
	va_start(factor, n);
	int result = va_arg(factor, int);
	for (int i = 1; i < n; i++) {
		result -= va_arg(factor, int);
	}
	va_end(factor);
	return result;
}