#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "locale.h"

#define MAX_CONTACTS 100
#define MAX_LENGTH 50

typedef struct {
    char work[MAX_LENGTH];
    char home[MAX_LENGTH];
} Email;

typedef struct {
    char social_network[MAX_LENGTH];
    char social_address[MAX_LENGTH];
    char nickname[MAX_LENGTH];
} SocialProfile;

typedef struct {
    char name[MAX_LENGTH];
    char job[MAX_LENGTH];
    char phone[MAX_LENGTH];
    Email email;
    SocialProfile social;
} Contact;

// Функция добавления контакта
void addContact(Contact contacts[], int* count) {
    if (*count >= MAX_CONTACTS) {
        printf("Ошибка: Достигнуто максимальное количество контактов.\n");
        return;
    }

    Contact newContact;
    Email newEmail;
    SocialProfile newSocial;

    printf("Введите имя: ");
    scanf("%s", newContact.name);

    printf("Введите место работы: ");
    scanf("%s", newContact.job);

    printf("Введите номер телефона: ");
    scanf("%s", newContact.phone);

    printf_s("Введите адрес рабочей электронной почты: ");
    scanf("%s", newEmail.work);

    printf_s("Введите адрес домашней электронной почты: ");
    scanf("%s", newEmail.home);

    newContact.email = newEmail;

    printf_s("Введите социальную сеть: ");
    scanf("%s", newSocial.social_network);

    printf_s("Введите адрес в этой социальной сети: ");
    scanf("%s", newSocial.social_address);

    printf_s("Введите никнейм в этой социальной сети: ");
    scanf("%s", newSocial.nickname);

    newContact.social = newSocial;

    contacts[*count] = newContact;
    (*count)++;

    printf("Контакт успешно добавлен.\n\n");
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

            printf("Введите новый адрес рабочей электронной почты: ");
            scanf("%s", contacts[i].email.work);

            printf("Введите новый адрес домашней электронной почты: ");
            scanf("%s", contacts[i].email.home);

            printf("Введите новую социальную сеть: ");
            scanf("%s", contacts[i].social.social_network);

            printf("Введите новый адрес на социальную сеть: ");
            scanf("%s", contacts[i].social.social_address);

            printf("Введите новый никнейм в социальной сети: ");
            scanf("%s", contacts[i].social.nickname);

            printf("Контакт успешно отредактирован.\n\n");
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
            printf("Контакт успешно удален.\n\n");
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
    printf("Адрес рабочей электройнной почты: %s\n", contact.email.work);
    printf("Адрес домашней электройнной почты: %s\n", contact.email.work);
    printf("Название социальной сети: %s\n", contact.social.social_network);
    printf("Ссылка на социальную сеть: %s\n", contact.social.social_address);
    printf("Никнейм: %s\n\n", contact.social.nickname);
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