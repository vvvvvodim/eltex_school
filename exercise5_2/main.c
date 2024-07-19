#include <locale.h>
#include "contact_list.h"

#define MAX_CONTACTS 100

int main() {
    setlocale(LC_ALL, "Rus");

    ContactList list;
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
    int tmp = 0;

    do {
        printf("Phone book\n");
        printf("1. Add new contact\n");
        printf("2. Edit contact\n");
        printf("3. Delete contact\n");
        printf("4. Print all contacts\n");
        printf("5. Exit\n");
        printf("Choose: ");
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