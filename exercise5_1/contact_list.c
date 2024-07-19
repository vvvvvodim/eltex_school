#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_list.h"

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
        printf("Error: The maximum number of contacts has been reached.\n");
        return;
    }

    Contact* newContact = createContact();
    if (newContact == NULL) return;

    Email newEmail;
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Enter name: ");
    scanf("%s", newContact->name);

    printf("Enter your place of work: ");
    cleanBuff();
    fgets(newContact->job, sizeof(newContact->job), stdin);
    newContact->job[strcspn(newContact->job, "\n")] = '\0';

    printf("Enter phone number: ");
    cleanBuff();
    fgets(newContact->phone, sizeof(newContact->phone), stdin);
    newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

    printf("Enter your work email address: ");
    cleanBuff();
    fgets(newEmail.work, sizeof(newEmail.work), stdin);
    newEmail.work[strcspn(newEmail.work, "\n")] = '\0';

    printf("Enter your home email address: ");
    cleanBuff();
    fgets(newEmail.home, sizeof(newEmail.home), stdin);
    newEmail.home[strcspn(newEmail.home, "\n")] = '\0';

    newContact->email = newEmail;

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("Error allocating memory for social networks.\n");
            return;
        }

        printf("Enter social network: ");
        cleanBuff();
        fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
        newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

        printf("Enter the address on this social network: ");
        cleanBuff();
        fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
        newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

        printf("Enter your nickname on this social network: ");
        cleanBuff();
        fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
        newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

        social_count++;

        printf("Want to add another social network? (y/n): ");
        moreSocial = getchar();
        cleanBuff();

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

    printf("The contact was successfully added.\n\n");
}

// Функция изменения контакта
void editContact(ContactList* list) {
    if (list->count == 0) {
        printf("Error: The phone book is empty.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("Enter the contact name to edit: ");
    scanf("%s", nameToEdit);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToEdit) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Contact named '%s' was not found.\n", nameToEdit);
        return;
    }

    printf("Enter a new name: ");
    scanf("%s", current->name);

    printf("Enter your new place of work: ");
    cleanBuff();
    fgets(current->job, sizeof(current->job), stdin);
    current->job[strcspn(current->job, "\n")] = '\0';

    printf("Enter a new phone number: ");
    cleanBuff();
    fgets(current->phone, sizeof(current->phone), stdin);
    current->phone[strcspn(current->phone, "\n")] = '\0';

    printf("Enter your new work email address: ");
    cleanBuff();
    fgets(current->email.work, sizeof(current->email.work), stdin);
    current->email.work[strcspn(current->email.work, "\n")] = '\0';

    printf("Enter your new home email address: ");
    cleanBuff();
    fgets(current->email.home, sizeof(current->email.home), stdin);
    current->email.home[strcspn(current->email.home, "\n")] = '\0';

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("Error allocating memory for social networks.\n");
            return;
        }

        printf("Enter social network: ");
        cleanBuff();
        fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
        newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

        printf("Enter the address on this social network: ");
        cleanBuff();
        fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
        newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

        printf("Enter your nickname on this social network: ");
        cleanBuff();
        fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
        newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

        social_count++;

        printf("Want to add another social network? (y/n): ");
        moreSocial = getchar();
        cleanBuff();

    } while (moreSocial == 'y' || moreSocial == 'Y');

    current->social = newSocial;
    current->social_count = social_count;

    printf("The contact has been successfully edited.\n\n");
}

// Функция удаления контакта
void deleteContact(ContactList* list) {
    if (list->count == 0) {
        printf("Error: The phone book is empty.\n");
        return;
    }

    char nameToDelete[MAX_LENGTH];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", nameToDelete);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToDelete) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Contact named '%s' was not found.\n", nameToDelete);
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

    printf("The contact was successfully deleted.\n\n");
}

// Функция, которая выводит данные о контакте 
void printContact(Contact* contact) {
    printf("Name: %s\n", contact->name);
    printf("Workplace: %s\n", contact->job);
    printf("Phone number: %s\n", contact->phone);
    printf("Work email address: %s\n", contact->email.work);
    printf("Home email address: %s\n", contact->email.home);
    for (int i = 0; i < contact->social_count; i++) {
        printf("Social network name: %s\n", contact->social[i].social_network);
        printf("Social network link: %s\n", contact->social[i].social_address);
        printf("Nickname: %s\n\n", contact->social[i].nickname);
    }
}

void printAllContacts(ContactList* list) {
    if (list->count == 0) {
        printf("The phone book is empty.\n");
        return;
    }

    Contact* current = list->head;
    while (current != NULL) {
        printContact(current);
        current = current->next;
    }
}