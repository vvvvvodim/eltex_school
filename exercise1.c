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

// ������� ���������� ��������
void addContact(Contact contacts[], int* count) {
    if (*count >= MAX_CONTACTS) {
        printf("������: ���������� ������������ ���������� ���������.\\n");
        return;
    }

    Contact newContact;
    //memset(&newContact, 0, sizeof(Contact));

    printf("������� ���: ");
    scanf("%s", newContact.name);

    printf("������� ����� ������: ");
    scanf("%s", newContact.job);

    printf("������� ����� ��������: ");
    scanf("%s", newContact.phone);

    printf_s("������� ����� ����������� �����: ");
    scanf("%s", newContact.email);

    printf_s("������� ������ �� �������� � �������: ");
    scanf("%s", newContact.social);

    printf_s("������� ��� ������������ � Telegram: ");
    scanf("%s", newContact.telegram);

    contacts[*count] = newContact;
    (*count)++;

    printf("������� ������� ��������.\n");
}

// ������� ��������� ��������
void editContact(Contact contacts[], int count) {
    if (count == 0) {
        printf("������: ���������� ����� �����.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    printf("������� ��� �������� ��� ��������������: ");
    scanf("%s", nameToEdit);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, nameToEdit) == 0) {
            printf("������� ����� ���: ");
            scanf("%s", contacts[i].name);

            printf("������� ����� ����� ������: ");
            scanf("%s", contacts[i].job);

            printf("������� ����� ����� ��������: ");
            scanf("%s", contacts[i].phone);

            printf("������� ����� ����� ����������� �����: ");
            scanf("%s", contacts[i].email);

            printf("������� ����� ������ �� �������� � �������: ");
            scanf("%s", contacts[i].social);

            printf("������� ����� ������� � �����������:");
            scanf("%s", contacts[i].telegram);

            printf("������� ������� ��������������.\n");
            return;
        }
    }

    printf("������: ������� � ������ '%s' �� ������.\n", nameToEdit);
}

// ������� �������� ��������
void deleteContact(Contact contacts[], int* count) {
    if (*count == 0) {
        printf("������: ���������� ����� �����.\n");
        return;
    }

    char nameToDelete[MAX_LENGTH];
    printf("������� ��� �������� ��� ��������: ");
    scanf("%s", nameToDelete);

    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, nameToDelete) == 0) {
            (*count)--;
            for (int j = i; j < *count; j++) {
                contacts[j] = contacts[j + 1];
            }
            printf("������� ������� ������.\n");
            return;
        }
    }

    printf("������: ������� � ������ '%s' �� ������.\n", nameToDelete);
}

// �������, ������� ������� ������ � �������� 
void printContact(Contact contact) {
    printf("���: %s\n", contact.name);
    printf("����� ������: %s\n", contact.job);
    printf("����� ��������: %s\n", contact.phone);
    printf("����� ����������� �����: %s\n", contact.email);
    printf("������ �� �������� � �������: %s\n", contact.social);
    printf("������� � �����������: %s\n\n", contact.telegram);
}

int main() {
    setlocale(LC_ALL, "Rus");

    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int tmp = 0;

    do {
        printf("���������� �����\n");
        printf("1. �������� �������\n");
        printf("2. ������������� �������\n");
        printf("3. ������� �������\n");
        printf("4. ������� ��� ��������\n");
        printf("5. �����\n");
        printf("�������� ��������: ");
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
            printf("�����...\n");
            break;
        default:
            printf("������: ������������ �����.\n");
            break;
        }
    } while (tmp != 5);

    return 0;
}