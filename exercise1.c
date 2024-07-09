#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "locale.h"

#define MAX_CONTACTS 100
#define MAX_LENGTH 50

typedef struct {
    char name[MAX_LENGTH];
    char job[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
    char social[MAX_LENGTH];
    char telegram[MAX_LENGTH];
} Contact;

// Функция добавления контакта
void addContact(Contact contacts[], int* count) {
    if (*count >= MAX_CONTACTS) {
        printf("Ошибка: Достигнуто максимальное количество контактов.\\n");
        return;
    }

    Contact newContact;
    //memset(&newContact, 0, sizeof(Contact));

    printf("Введите имя: ");
    scanf("%s", newContact.name);

    printf("Введите место работы: ");
    scanf("%s", newContact.job);

    printf("Введите номер телефона: ");
    scanf("%s", newContact.phone);

    printf_s("Введите адрес электронной почты: ");
    scanf("%s", newContact.email);

    printf_s("Введите ссылку на страницу в соцсети: ");
    scanf("%s", newContact.social);

    printf_s("Введите имя пользователя в Telegram: ");
    scanf("%s", newContact.telegram);

    contacts[*count] = newContact;
    (*count)++;

    printf("Контакт успешно добавлен.\n");
}

// Функция изменения контакта
void editContact(Contact contacts[], int count) {
    if (count == 0) {
        printf("Ошибка: Телефонная книга пуста.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    printf("Введите имя контакта для редактирования: ");
    scanf("%s", nameToEdit);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, nameToEdit) == 0) {
            printf("Введите новое имя: ");
            scanf("%s", contacts[i].name);

            printf("Введите новое место работы: ");
            scanf("%s", contacts[i].job);

            printf("Введите новый номер телефона: ");
            scanf("%s", contacts[i].phone);

            printf("Введите новый адрес электронной почты: ");
            scanf("%s", contacts[i].email);

            printf("Введите новую ссылку на страницу в соцсети: ");
            scanf("%s", contacts[i].social);

            printf("Введите новый профиль в мессенджере:");
            scanf("%s", contacts[i].telegram);

            printf("Контакт успешно отредактирован.\n");
            return;
        }
    }

    printf("Ошибка: Контакт с именем '%s' не найден.\n", nameToEdit);
}

// Функция удаления контакта
void deleteContact(Contact contacts[], int* count) {
    if (*count == 0) {
        printf("Ошибка: Телефонная книга пуста.\n");
        return;
    }

    char nameToDelete[MAX_LENGTH];
    printf("Введите имя контакта для удаления: ");
    scanf("%s", nameToDelete);

    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, nameToDelete) == 0) {
            (*count)--;
            for (int j = i; j < *count; j++) {
                contacts[j] = contacts[j + 1];
            }
            printf("Контакт успешно удален.\n");
            return;
        }
    }

    printf("Ошибка: Контакт с именем '%s' не найден.\n", nameToDelete);
}

// Функция, которая выводит данные о контакте 
void printContact(Contact contact) {
    printf("Имя: %s\n", contact.name);
    printf("Место работы: %s\n", contact.job);
    printf("Номер телефона: %s\n", contact.phone);
    printf("Адрес электронной почты: %s\n", contact.email);
    printf("Ссылка на страницу в соцсети: %s\n", contact.social);
    printf("Профиль в мессенджере: %s\n\n", contact.telegram);
}

int main() {
    setlocale(LC_ALL, "Rus");

    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int tmp = 0;

    do {
        printf("Телефонная книга\n");
        printf("1. Добавить контакт\n");
        printf("2. Редактировать контакт\n");
        printf("3. Удалить контакт\n");
        printf("4. Вывести все контакты\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &tmp);

        switch (tmp) {
        case 1:
            printf("\033[0d\033[2J");
            addContact(contacts, &count);
            break;
        case 2:
            printf("\033[0d\033[2J");
            editContact(contacts, &count);
            break;
        case 3:
            printf("\033[0d\033[2J");
            deleteContact(contacts, &count);
            break;
        case 4:
            printf("\033[0d\033[2J");
            for (int i = 0; i < count; i++) {
                printContact(contacts[i]);
            }
            break;
        case 5:
            printf("\033[0d\033[2J");
            printf("Выход...\n");
            break;
        default:
            printf("Ошибка: Некорректный выбор.\n");
            break;
        }
    } while (tmp != 5);

    return 0;
}