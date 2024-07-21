#include <stdio.h>
#include <locale.h>
#include <dlfcn.h>
#include "contact_list.h"

#define MAX_CONTACTS 100

int main() {
    setlocale(LC_ALL, "Rus");

    void* handle;
    void (*addContact)(ContactList*);
    void (*editContact)(ContactList*);
    void (*deleteContact)(ContactList*);
    void (*printAllContacts)(ContactList*);

    char* error;
    handle = dlopen("/home/NSTU/pmi-b1506/eltex/exercise5_2/libcontact_list.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    addContact = dlsym(handle, "addContact");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    editContact = dlsym(handle, "editContact");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    deleteContact = dlsym(handle, "deleteContact");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    printAllContacts = dlsym(handle, "printAllContacts");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

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
            printf("Exit...\n");
            break;
        default:
            printf("Error: Incorrect choice.\n");
            break;
        }
    } while (tmp != 5);

    dlclose(handle);

    return 0;
}