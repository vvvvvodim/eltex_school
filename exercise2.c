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
		printf("������: ������� �� ����.\n");
		return 0;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	int tmp;
	double number1, number2, result;

	do
	{
		printf("�����������.\n");
		printf("�������� ��������: \n");
		printf("1. ��������\n");
		printf("2. ���������\n");
		printf("3. ���������\n");
		printf("4. �������\n");
		printf("5. �����\n");
		scanf("%d", &tmp);

		if (tmp >= 1 && tmp <= 4) {
			printf("\033[0d\033[2J");
			printf("������� ������ �����: ");
			if (scanf("%lf", &number1) != 1) {
				printf("������: ����������, ������� ������ �����.\n");
				while (getchar() != '\n'); // ������� ������ �����
				continue;
			}

			printf("������� ������ �����: ");
			if (scanf("%lf", &number2) != 1) {
				printf("������: ����������, ������� ������ �����.\n");
				while (getchar() != '\n'); // ������� ������ �����
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
			printf("�����...");
			break;
		default:
			printf("������: ������������ �����.\n");
			break;
		}
	} while (tmp != 5);

	return 0;
}