#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "locale.h"

double add(double x, double y) {
	return x + y;
}

double subtract(double x, double y) {
	return x - y;
}

double multiply(double x, double y) {
	return x * y;
}

double divide(double x, double y) {
	if (y != 0) return x / y;
	else {
		printf("Ошибка: Деление на ноль.\n");
		return 0;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	int tmp;
	double number1, number2, result;

	do
	{
		printf("Калькулятор.\n");
		printf("Выберите действие: \n");
		printf("1. Сложение\n");
		printf("2. Вычитание\n");
		printf("3. Умножение\n");
		printf("4. Деление\n");
		printf("5. Выход\n");
		scanf("%d", &tmp);

		if (tmp >= 1 && tmp <= 4) {
			printf("\033[0d\033[2J");
			printf("Введите первое число: ");
			if (scanf("%lf", &number1) != 1) {
				printf("Ошибка: Пожалуйста, вводите только числа.\n");
				while (getchar() != '\n'); // Очистка буфера ввода
				continue;
			}

			printf("Введите второе число: ");
			if (scanf("%lf", &number2) != 1) {
				printf("Ошибка: Пожалуйста, вводите только числа.\n");
				while (getchar() != '\n'); // Очистка буфера ввода
				continue;
			}
			printf("\033[0d\033[2J");
		}

		switch (tmp) {
		case 1:
			result = add(number1, number2);
			printf("%.2lf + %.2lf = %.2lf\n\n", number1, number2, result);
			break;
		case 2:
			result = subtract(number1, number2);
			printf("%.2lf + %.2lf = %.2lf\n\n", number1, number2, result);
			break;
		case 3:
			result = multiply(number1, number2);
			printf("%.2lf + %.2lf = %.2lf\n\n", number1, number2, result);
			break;
		case 4:
			result = divide(number1, number2);
			printf("%.2lf + %.2lf = %.2lf\n\n", number1, number2, result);
			break;
		case 5:
			printf("\033[0d\033[2J");
			printf("Выход...");
			break;
		default:
			printf("Ошибка: Некорректный выбор.\n");
			break;
		}
	} while (tmp != 5);

	return 0;
}