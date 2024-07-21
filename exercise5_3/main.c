#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <dlfcn.h>
#include <string.h>

// Определение типа функции операции
typedef int (*operation_func)(int, ...);

// Структура для хранения информации об операции
typedef struct {
    const char* name;
    operation_func func;
} Operation;

Operation* functions = NULL;
int func_count = 0;

// Функция для добавления операции в массив functions
void add_operation(const char* name, operation_func func) {
    functions = (Operation*)realloc(functions, sizeof(Operation) * (func_count + 1));
    functions[func_count].name = strdup(name);
    functions[func_count].func = func;
    func_count++;
}

int main() {
    setlocale(LC_ALL, "Rus");

    void* handleAdd;
    void* handleSub;
    void* handleMult;
    void* handleDvd;
    void* handleMax;
    void* handleMin;

    operation_func add;
    operation_func subtract;
    operation_func multiply;
    operation_func divide;
    operation_func max;
    operation_func min;

    char* error;

    handleAdd = dlopen("./libadd.so", RTLD_LAZY);
    if (!handleAdd) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    add = (operation_func)dlsym(handleAdd, "add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Add", add);

    handleSub = dlopen("./libsubtract.so", RTLD_LAZY);
    if (!handleSub) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    subtract = (operation_func)dlsym(handleSub, "subtract");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Subtract", subtract);

    handleMult = dlopen("./libmultiply.so", RTLD_LAZY);
    if (!handleMult) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    multiply = (operation_func)dlsym(handleMult, "multiply");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Multiply", multiply);

    handleDvd = dlopen("./libdivide.so", RTLD_LAZY);
    if (!handleDvd) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    divide = (operation_func)dlsym(handleDvd, "divide");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Divide", divide);

    handleMax = dlopen("./libmax.so", RTLD_LAZY);
    if (!handleMax) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    max = (operation_func)dlsym(handleMax, "max");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Maximum", max);

    handleMin = dlopen("./libmin.so", RTLD_LAZY);
    if (!handleMin) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    min = (operation_func)dlsym(handleMin, "min");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    add_operation("Minimum", min);

    int tmp;
    int result = 0;
    int args_count = 0;

    do {
        printf("Calculator.\n");
        printf("Choose operation: \n");
        for (int i = 0; i < func_count; i++) {
            printf("%d. %s\n", i + 1, functions[i].name);
        }
        printf("%d. Exit\n", func_count + 1);
        scanf("%d", &tmp);

        if (tmp >= 1 && tmp <= func_count) {
            printf("\033[0d\033[2J");
            printf("%s\n", functions[tmp - 1].name);
            printf("---------------\n");
            printf("Enter count of numbers: ");
            if (scanf("%d", &args_count) != 1) {
                printf("Error: Please, enter only digit.\n");
                while (getchar() != '\n'); // Очистка буфера ввода
                continue;
            }
            int* numbers = (int*)malloc(args_count * sizeof(int));
            printf("Enter numbers:\n");
            for (int i = 0; i < args_count; i++) {
                scanf("%d", &numbers[i]);
            }

            result = functions[tmp - 1].func(args_count, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);

            printf("---------------\n");
            printf("Result: %d\n\n", result);
            free(numbers);
        }
    } while (tmp != func_count + 1);

    printf("\033[0d\033[2J");
    printf("Exit...");

    dlclose(handleAdd);
    dlclose(handleSub);
    dlclose(handleMult);
    dlclose(handleDvd);
    dlclose(handleMax);
    dlclose(handleMin);

    // Освобождение памяти
    for (int i = 0; i < func_count; i++) {
        free((void*)functions[i].name);
    }
    free(functions);

    return 0;
}