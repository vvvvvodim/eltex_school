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
    SocialProfile *social;
    int social_count;
} Contact;


// Вспомогательная функция очистки буфера ввода
void cleanBuff() {
    fseek(stdin, 0, SEEK_END);
}

// Функция добавления контакта
void addContact(Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Ошибка: Достигнуто максимальное количество контактов.\n");
        return;
    }

    Contact newContact;
    Email newEmail;
    SocialProfile *newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Введите имя: ");
    scanf("%s", newContact.name);

    printf("Введите место работы: ");
    cleanBuff();
    fgets(newContact.job, sizeof(newContact.job), stdin);
    newContact.job[strcspn(newContact.job, "\n")] = '\0';

    printf("Введите номер телефона: ");
    cleanBuff();
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    printf("Введите адрес рабочей электронной почты: ");
    cleanBuff();
    fgets(newEmail.work, sizeof(newEmail.work), stdin);
    newEmail.work[strcspn(newEmail.work, "\n")] = '\0';

    printf("Введите адрес домашней электронной почты: ");
    cleanBuff();
    fgets(newEmail.home, sizeof(newEmail.home), stdin);
    newEmail.home[strcspn(newEmail.home, "\n")] = '\0';

    newContact.email = newEmail;

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("Ошибка выделения памяти для социальных сетей.\n");
            return;
        }

        printf("Введите социальную сеть: ");
        cleanBuff();
        fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
        newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

        printf("Введите адрес в этой социальной сети: ");
        cleanBuff();
        fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
        newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

        printf("Введите никнейм в этой социальной сети: ");
        cleanBuff();
        fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
        newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

        social_count++;

        printf("Хотите добавить ещё одну социальную сеть? (y/n): ");
        moreSocial = getchar();
        cleanBuff;

    } while (moreSocial == 'y' || moreSocial == 'Y');

    newContact.social = newSocial;
    newContact.social_count = social_count;

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
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Введите имя контакта для редактирования: ");
    scanf("%s", nameToEdit);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, nameToEdit) == 0) {
            printf("Введите новое имя: ");
            scanf("%s", contacts[i].name);

            printf("Введите новое место работы: ");
            cleanBuff();
            fgets(contacts[i].job, sizeof(contacts[i].job), stdin);
            contacts[i].job[strcspn(contacts[i].job, "\n")] = '\0';

            printf("Введите новый номер телефона: ");
            cleanBuff();
            fgets(contacts[i].phone, sizeof(contacts[i].phone), stdin);
            contacts[i].phone[strcspn(contacts[i].phone, "\n")] = '\0';

            printf("Введите новый адрес рабочей электронной почты: ");
            cleanBuff();
            fgets(contacts[i].email.work, sizeof(contacts[i].email.work), stdin);
            contacts[i].email.work[strcspn(contacts[i].email.work, "\n")] = '\0';

            printf("Введите новый адрес домашней электронной почты: ");
            cleanBuff();
            fgets(contacts[i].email.home, sizeof(contacts[i].email.home), stdin);
            contacts[i].email.home[strcspn(contacts[i].email.home, "\n")] = '\0';

            do {
                newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
                if (newSocial == NULL) {
                    printf("Ошибка выделения памяти для социальных сетей.\n");
                    return;
                }

                printf("Введите социальную сеть: ");
                cleanBuff();
                fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
                newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

                printf("Введите адрес в этой социальной сети: ");
                cleanBuff();
                fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
                newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

                printf("Введите никнейм в этой социальной сети: ");
                cleanBuff();
                fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
                newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

                social_count++;

                printf("Хотите добавить ещё одну социальную сеть? (y/n): ");
                moreSocial = getchar();
                cleanBuff;

            } while (moreSocial == 'y' || moreSocial == 'Y');

            contacts[i].social = newSocial;
            contacts[i].social_count = social_count;

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
    for (int i = 0; i < contact.social_count; i++) {
        printf("Название социальной сети: %s\n", contact.social[i].social_network);
        printf("Ссылка на социальную сеть: %s\n", contact.social[i].social_address);
        printf("Никнейм: %s\n\n", contact.social[i].nickname);
    }
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