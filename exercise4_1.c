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

typedef struct Contact {
    char name[MAX_LENGTH];
    char job[MAX_LENGTH];
    char phone[MAX_LENGTH];
    Email email;
    SocialProfile* social;
    int social_count;
    struct Contact* prev;
    struct Contact* next;
} Contact;

typedef struct {
    Contact* head;
    Contact* tail;
    int count;
} ContactList;


// Вспомогательная функция очистки буфера ввода
void cleanBuff() {
    fseek(stdin, 0, SEEK_END);
}

// Вспомогательная функция создания нового контакта
Contact* createContact() {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    newContact->social = NULL;
    newContact->social_count = 0;
    newContact->prev = NULL;
    newContact->next = NULL;
    return newContact;
}

// Функция добавления контакта
void addContact(ContactList* list) {
    if (list->count >= MAX_CONTACTS) {
        printf("Ошибка: Достигнуто максимальное количество контактов.\n");
        return;
    }

    Contact* newContact = createContact();
    if (newContact == NULL) return;

    Email newEmail;
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Введите имя: ");
    scanf("%s", newContact->name);

    printf("Введите место работы: ");
    cleanBuff();
    fgets(newContact->job, sizeof(newContact->job), stdin);
    newContact->job[strcspn(newContact->job, "\n")] = '\0';

    printf("Введите номер телефона: ");
    cleanBuff();
    fgets(newContact->phone, sizeof(newContact->phone), stdin);
    newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

    printf("Введите адрес рабочей электронной почты: ");
    cleanBuff();
    fgets(newEmail.work, sizeof(newEmail.work), stdin);
    newEmail.work[strcspn(newEmail.work, "\n")] = '\0';

    printf("Введите адрес домашней электронной почты: ");
    cleanBuff();
    fgets(newEmail.home, sizeof(newEmail.home), stdin);
    newEmail.home[strcspn(newEmail.home, "\n")] = '\0';

    newContact->email = newEmail;

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

    newContact->social = newSocial;
    newContact->social_count = social_count;

    if (list->head == NULL) {
        list->head = list->tail = newContact;
    }
    else {
        Contact* current = list->head;
        while (current != NULL && strcmp(current->name, newContact->name) < 0) {
            current = current->next;
        }

        if (current == NULL) {
            newContact->prev = list->tail;
            list->tail->next = newContact;
            list->tail = newContact;
        }
        else if (current == list->head) {
            newContact->next = list->head;
            list->head->prev = newContact;
            list->head = newContact;
        }
        else {
            newContact->prev = current->prev;
            newContact->next = current;
            current->prev->next = newContact;
            current->prev = newContact;
        }
    }

    list->count++;

    printf("Контакт успешно добавлен.\n\n");
}

// Функция изменения контакта
void editContact(ContactList* list) {
    if (list->count == 0) {
        printf("Ошибка: Телефонная книга пуста.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Введите имя контакта для редактирования: ");
    scanf("%s", nameToEdit);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToEdit) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Ошибка: Контакт с именем '%s' не найден.\n", nameToEdit);
        return;
    }

    printf("Введите новое имя: ");
    scanf("%s", current->name);

    printf("Введите новое место работы: ");
    cleanBuff();
    fgets(current->job, sizeof(current->job), stdin);
    current->job[strcspn(current->job, "\n")] = '\0';

    printf("Введите новый номер телефона: ");
    cleanBuff();
    fgets(current->phone, sizeof(current->phone), stdin);
    current->phone[strcspn(current->phone, "\n")] = '\0';

    printf("Введите новый адрес рабочей электронной почты: ");
    cleanBuff();
    fgets(current->email.work, sizeof(current->email.work), stdin);
    current->email.work[strcspn(current->email.work, "\n")] = '\0';

    printf("Введите новый адрес домашней электронной почты: ");
    cleanBuff();
    fgets(current->email.home, sizeof(current->email.home), stdin);
    current->email.home[strcspn(current->email.home, "\n")] = '\0';

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
        cleanBuff();

    } while (moreSocial == 'y' || moreSocial == 'Y');

    current->social = newSocial;
    current->social_count = social_count;

    printf("Контакт успешно отредактирован.\n\n");
}

// Функция удаления контакта
void deleteContact(ContactList* list) {
    if (list->count == 0) {
        printf("Ошибка: Телефонная книга пуста.\n");
        return;
    }

    char nameToDelete[MAX_LENGTH];
    printf("Введите имя контакта для удаления: ");
    scanf("%s", nameToDelete);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToDelete) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Ошибка: Контакт с именем '%s' не найден.\n", nameToDelete);
        return;
    }

    if (current == list->head) {
        list->head = current->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    }
    else if (current == list->tail) {
        list->tail = current->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    free(current->social);
    free(current);
    list->count--;

    printf("Контакт успешно удален.\n\n");
}

// Функция, которая выводит данные о контакте 
void printContact(Contact* contact) {
    printf("Имя: %s\n", contact->name);
    printf("Место работы: %s\n", contact->job);
    printf("Номер телефона: %s\n", contact->phone);
    printf("Адрес рабочей электронной почты: %s\n", contact->email.work);
    printf("Адрес домашней электронной почты: %s\n", contact->email.home);
    for (int i = 0; i < contact->social_count; i++) {
        printf("Название социальной сети: %s\n", contact->social[i].social_network);
        printf("Ссылка на социальную сеть: %s\n", contact->social[i].social_address);
        printf("Никнейм: %s\n\n", contact->social[i].nickname);
    }
}

void printAllContacts(ContactList* list) {
    if (list->count == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    Contact* current = list->head;
    while (current != NULL) {
        printContact(current);
        current = current->next;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    ContactList list;
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
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
            addContact(&list);
            break;
        case 2:
            printf("\033[0d\033[2J");
            editContact(&list);
            break;
        case 3:
            printf("\033[0d\033[2J");
            deleteContact(&list);
            break;
        case 4:
            printf("\033[0d\033[2J");
            printAllContacts(&list);
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