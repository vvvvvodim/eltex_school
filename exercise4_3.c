#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "locale.h"

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
    SocialProfile* social;
    int social_count;
} Contact;

typedef struct Node {
    Contact contact;
    struct Node* left;
    struct Node* right;
} Node;

// Вспомогательная функция очистки буфера ввода
void cleanBuff() {
    fseek(stdin, 0, SEEK_END);
}

// Функция создания нового узла дерева
Node* createNode(Contact contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция добавления контакта в дерево
Node* addContact(Node* root, Contact contact) {
    if (root == NULL) {
        return createNode(contact);
    }

    if (strcmp(contact.name, root->contact.name) < 0) {
        root->left = addContact(root->left, contact);
    }
    else if (strcmp(contact.name, root->contact.name) > 0) {
        root->right = addContact(root->right, contact);
    }

    return root;
}

// Функция поиска минимального узла в дереве
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Функция удаления контакта из дерева
Node* deleteContact(Node* root, char* name) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(name, root->contact.name) < 0) {
        root->left = deleteContact(root->left, name);
    }
    else if (strcmp(name, root->contact.name) > 0) {
        root->right = deleteContact(root->right, name);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->contact = temp->contact;
        root->right = deleteContact(root->right, temp->contact.name);
    }

    return root;
}

// Функция поиска контакта в дереве
Node* findContact(Node* root, char* name) {
    if (root == NULL || strcmp(name, root->contact.name) == 0) {
        return root;
    }

    if (strcmp(name, root->contact.name) < 0) {
        return findContact(root->left, name);
    }
    else {
        return findContact(root->right, name);
    }
}

// Функция добавления нового контакта с вводом данных
Node* inputContact(Node* root) {
    Contact newContact;
    Email newEmail;
    SocialProfile* newSocial = NULL;
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
            return root;
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

    newContact.social = newSocial;
    newContact.social_count = social_count;

    return addContact(root, newContact);
}

// Функция изменения контакта
void editContact(Node* root) {
    if (root == NULL) {
        printf("Ошибка: Телефонная книга пуста.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Введите имя контакта для редактирования: ");
    scanf("%s", nameToEdit);

    Node* contactNode = findContact(root, nameToEdit);
    if (contactNode == NULL) {
        printf("Ошибка: Контакт с именем '%s' не найден.\n", nameToEdit);
        return;
    }

    printf("Введите новое имя: ");
    scanf("%s", contactNode->contact.name);

    printf("Введите новое место работы: ");
    cleanBuff();
    fgets(contactNode->contact.job, sizeof(contactNode->contact.job), stdin);
    contactNode->contact.job[strcspn(contactNode->contact.job, "\n")] = '\0';

    printf("Введите новый номер телефона: ");
    cleanBuff();
    fgets(contactNode->contact.phone, sizeof(contactNode->contact.phone), stdin);
    contactNode->contact.phone[strcspn(contactNode->contact.phone, "\n")] = '\0';

    printf("Введите новый адрес рабочей электронной почты: ");
    cleanBuff();
    fgets(contactNode->contact.email.work, sizeof(contactNode->contact.email.work), stdin);
    contactNode->contact.email.work[strcspn(contactNode->contact.email.work, "\n")] = '\0';

    printf("Введите новый адрес домашней электронной почты: ");
    cleanBuff();
    fgets(contactNode->contact.email.home, sizeof(contactNode->contact.email.home), stdin);
    contactNode->contact.email.home[strcspn(contactNode->contact.email.home, "\n")] = '\0';

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

    contactNode->contact.social = newSocial;
    contactNode->contact.social_count = social_count;

    printf("Контакт успешно отредактирован.\n\n");
}

// Функция вывода всех контактов (обход дерева)
void printContacts(Node* root) {
    if (root != NULL) {
        printContacts(root->left);
        printf("Имя: %s\n", root->contact.name);
        printf("Место работы: %s\n", root->contact.job);
        printf("Номер телефона: %s\n", root->contact.phone);
        printf("Адрес рабочей электронной почты: %s\n", root->contact.email.work);
        printf("Адрес домашней электронной почты: %s\n", root->contact.email.home);
        for (int i = 0; i < root->contact.social_count; i++) {
            printf("Название социальной сети: %s\n", root->contact.social[i].social_network);
            printf("Ссылка на социальную сеть: %s\n", root->contact.social[i].social_address);
            printf("Никнейм: %s\n", root->contact.social[i].nickname);
        }
        printf("\n");
        printContacts(root->right);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    Node* root = NULL;
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
            root = inputContact(root);
            break;
        case 2:
            printf("\033[0d\033[2J");
            editContact(root);
            break;
        case 3: {
            printf("\033[0d\033[2J");
            char nameToDelete[MAX_LENGTH];
            printf("Введите имя контакта для удаления: ");
            scanf("%s", nameToDelete);
            root = deleteContact(root, nameToDelete);
            break;
        }
        case 4:
            printf("\033[0d\033[2J");
            printContacts(root);
            break;
        case 5:
            printf("\033[0d\033[2J");
            printf("Выход...\n");
            break;
        default:
            printf("\033[0d\033[2J");
            printf("Ошибка: Некорректный выбор.\n");
            break;
        }
    } while (tmp != 5);

    return 0;
}