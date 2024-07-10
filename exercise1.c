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

// ������� ���������� ��������
void addContact(Contact contacts[], int* count) {
    if (*count >= MAX_CONTACTS) {
        printf("������: ���������� ������������ ���������� ���������.\n");
        return;
    }

    Contact newContact;
    Email newEmail;
    SocialProfile newSocial;

    printf("������� ���: ");
    scanf("%s", newContact.name);

    printf("������� ����� ������: ");
    scanf("%s", newContact.job);

    printf("������� ����� ��������: ");
    scanf("%s", newContact.phone);

    printf_s("������� ����� ������� ����������� �����: ");
    scanf("%s", newEmail.work);

    printf_s("������� ����� �������� ����������� �����: ");
    scanf("%s", newEmail.home);

    newContact.email = newEmail;

    printf_s("������� ���������� ����: ");
    scanf("%s", newSocial.social_network);

    printf_s("������� ����� � ���� ���������� ����: ");
    scanf("%s", newSocial.social_address);

    printf_s("������� ������� � ���� ���������� ����: ");
    scanf("%s", newSocial.nickname);

    newContact.social = newSocial;

    contacts[*count] = newContact;
    (*count)++;

    printf("������� ������� ��������.\n\n");
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

            printf("������� ����� ����� ������� ����������� �����: ");
            scanf("%s", contacts[i].email.work);

            printf("������� ����� ����� �������� ����������� �����: ");
            scanf("%s", contacts[i].email.home);

            printf("������� ����� ���������� ����: ");
            scanf("%s", contacts[i].social.social_network);

            printf("������� ����� ����� �� ���������� ����: ");
            scanf("%s", contacts[i].social.social_address);

            printf("������� ����� ������� � ���������� ����: ");
            scanf("%s", contacts[i].social.nickname);

            printf("������� ������� ��������������.\n\n");
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
            printf("������� ������� ������.\n\n");
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
    printf("����� ������� ������������ �����: %s\n", contact.email.work);
    printf("����� �������� ������������ �����: %s\n", contact.email.work);
    printf("�������� ���������� ����: %s\n", contact.social.social_network);
    printf("������ �� ���������� ����: %s\n", contact.social.social_address);
    printf("�������: %s\n\n", contact.social.nickname);
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