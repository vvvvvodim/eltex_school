#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdarg.h"
#include "locale.h"

typedef int (*operation_func)(int, ...);

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

int divide(int n, ...) {
	va_list factor;
	va_start(factor, n);
	int result = va_arg(factor, int);
	for (int i = 1; i < n; i++) {
		result /= va_arg(factor, int);
	}
	va_end(factor);
	return result;
}

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

int min(int n, ...) {
	int result = 1000;
	int temp;

	va_list factor;
	va_start(factor, n);
	for (int i = 0; i < n; i++) {
		temp = va_arg(factor, int);
		if (temp < result) result = temp;
	}
	va_end(factor);
	return result;
}

typedef struct {
	const char* name;
	operation_func func;
} Operation;

Operation functions[] = {
	{"Сложение", add},
	{"Вычитание", subtract},
	{"Умножение", multiply},
	{"Деление", divide},
	{"Максимум", max},
	{"Минимум", min}
};


int main() {
	setlocale(LC_ALL, "Rus");

	int func_count = sizeof(functions) / sizeof(functions[0]);
	int tmp;
	int result = 0;
	int args_count = 0;

	do
	{
		printf("Калькулятор.\n");
		printf("Выберите действие: \n");
		for (int i = 0; i < func_count; i++) {
			printf("%d. %s\n", i + 1, functions[i].name);
		}
		printf("%d. Выход\n", func_count + 1);
		scanf("%d", &tmp);

		if (tmp >= 1 && tmp <= func_count) {
			printf("\033[0d\033[2J");
			printf("%s\n", functions[tmp - 1].name);
			printf("---------------\n");
			printf("Введите количество чисел, которые будут переданы: ");
			if (scanf("%d", &args_count) != 1) {
				printf("Ошибка: Пожалуйста, вводите только числа.\n");
				while (getchar() != '\n'); // Очистка буфера ввода
				continue;
			}
			int *numbers = (int*)malloc(args_count*sizeof(int));
			printf("Введите числа:\n");
			for (int i = 0; i < args_count; i++) {
				scanf("%d", &numbers[i]);
			}

			switch (args_count) {
			case 1:
				result = functions[tmp - 1].func(args_count, numbers[0]);
				break;
			case 2:
				result = functions[tmp - 1].func(args_count, numbers[0], numbers[1]);
				break;
			case 3:
				result = functions[tmp - 1].func(args_count, numbers[0], numbers[1], numbers[2]);
				break;
			case 4:
				result = functions[tmp - 1].func(args_count, numbers[0], numbers[1], numbers[2], numbers[3]);
				break;
			case 5:
				result = functions[tmp - 1].func(args_count, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
				break;
			}

			printf("---------------\n");
			printf("Результат: %d\n\n", result);

		}
	} while (tmp != func_count + 1);

	printf("\033[0d\033[2J");
	printf("Выход...");

	return 0;
}