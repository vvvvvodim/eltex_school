#include "stdio.h"
#include "stdarg.h"

int max(int n, ...) {
	int result = -1000;
	int temp;

	va_list factor;
	va_start(factor, n);
	for (int i = 0; i < n; i++) {
		temp = va_arg(factor, int);
		if (temp > result) result = temp;
	}
	va_end(factor);
	return result;
}