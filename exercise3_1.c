#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define STR_LEN 10

// Преобразование цифрового представления в буквенное
void num_to_str(int num, char* str) {
    strcpy(str, "---------");
    if (num & S_IRUSR) str[0] = 'r';
    if (num & S_IWUSR) str[1] = 'w';
    if (num & S_IXUSR) str[2] = 'x';
    if (num & S_IRGRP) str[3] = 'r';
    if (num & S_IWGRP) str[4] = 'w';
    if (num & S_IXGRP) str[5] = 'x';
    if (num & S_IROTH) str[6] = 'r';
    if (num & S_IWOTH) str[7] = 'w';
    if (num & S_IXOTH) str[8] = 'x';
}

// Преобразование буквенного представления в цифровое
int str_to_num(const char* str) {
    int num = 0;
    if (str[0] == 'r') num |= S_IRUSR;
    if (str[1] == 'w') num |= S_IWUSR;
    if (str[2] == 'x') num |= S_IXUSR;
    if (str[3] == 'r') num |= S_IRGRP;
    if (str[4] == 'w') num |= S_IWGRP;
    if (str[5] == 'x') num |= S_IXGRP;
    if (str[6] == 'r') num |= S_IROTH;
    if (str[7] == 'w') num |= S_IWOTH;
    if (str[8] == 'x') num |= S_IXOTH;
    return num;
}

// Преобразование цифрового представления в двоичное
void num_to_bin(int num, char* bin) {
    for (int i = 8; i >= 0; i--) {
        bin[8 - i] = (num & (1 << i)) ? '1' : '0';
    }
    bin[9] = '\0';
}

// Вывод информации о правах доступа
void print_permissions(int num) {
    char str[STR_LEN];
    char bin[10];

    num_to_str(num, str);
    num_to_bin(num, bin);

    printf("Literal: %s\n", str);
    printf("Digital: %o\n", num);
    printf("Bitwise: %s\n", bin);
}

// Основная функция
int main() {
    int choice;
    char input[STR_LEN];
    struct stat fileStat;

    while (1) {
        printf("Select action:\n");
        printf("1. Enter access rights (alphabetic or numeric designation)\n");
        printf("2. Enter the file name and display permissions\n");
        printf("3. Changing access rights\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter permissions (alphabetic or numeric): ");
            scanf("%s", input);
            int num;
            if (isdigit(input[0])) {
                // Можно сразу считывать в восьмеричную систему счисления
                sscanf(input, "%o", &num);
            }
            else {
                num = str_to_num(input);
            }
            print_permissions(num);
        }
        else if (choice == 2) {
            printf("Enter file name: ");
            scanf("%s", input);
            if (stat(input, &fileStat) < 0) {
                perror("Error getting file information");
                continue;
            }
            // Выполним побитовое "И" с 777 (фулл единицы) и вывведем результат
            print_permissions(fileStat.st_mode & 0777);
        }
        else if (choice == 3) {
            printf("Enter the current permissions (alphabetic or numeric): ");
            scanf("%s", input);
            int num;
            if (isdigit(input[0])) {
                sscanf(input, "%o", &num);
            }
            else {
                num = str_to_num(input);
            }
            print_permissions(num);

            printf("Enter commands to change rights (for example, +rwx, -r, =rwx): ");
            scanf("%s", input);

            for (char* cmd = input; *cmd; cmd++) {
                int tmp = 0;
                switch (*cmd) {
                case '+':
                    cmd++;
                    tmp = str_to_num(cmd);
                    num |= tmp;
                    break;
                case '-':
                    cmd++;
                    tmp = str_to_num(cmd);
                    num &= ~tmp;
                    break;
                case '=':
                    cmd++;
                    num = str_to_num(cmd);
                    break;
                }
                while (*cmd && (*cmd == 'r' || *cmd == 'w' || *cmd == 'x')) cmd++;
                cmd--;
            }
            print_permissions(num);
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Select the command.\n");
        }
    }

    return 0;
}