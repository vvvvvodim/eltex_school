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


// ��������������� ������� ������� ������ �����
void cleanBuff() {
    fseek(stdin, 0, SEEK_END);
}

// ��������������� ������� �������� ������ ��������
Contact* createContact() {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    newContact->social = NULL;
    newContact->social_count = 0;
    newContact->prev = NULL;
    newContact->next = NULL;
    return newContact;
}

// ������� ���������� ��������
void addContact(ContactList* list) {
    if (list->count >= MAX_CONTACTS) {
        printf("������: ���������� ������������ ���������� ���������.\n");
        return;
    }

    Contact* newContact = createContact();
    if (newContact == NULL) return;

    Email newEmail;
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("������� ���: ");
    scanf("%s", newContact->name);

    printf("������� ����� ������: ");
    cleanBuff();
    fgets(newContact->job, sizeof(newContact->job), stdin);
    newContact->job[strcspn(newContact->job, "\n")] = '\0';

    printf("������� ����� ��������: ");
    cleanBuff();
    fgets(newContact->phone, sizeof(newContact->phone), stdin);
    newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

    printf("������� ����� ������� ����������� �����: ");
    cleanBuff();
    fgets(newEmail.work, sizeof(newEmail.work), stdin);
    newEmail.work[strcspn(newEmail.work, "\n")] = '\0';

    printf("������� ����� �������� ����������� �����: ");
    cleanBuff();
    fgets(newEmail.home, sizeof(newEmail.home), stdin);
    newEmail.home[strcspn(newEmail.home, "\n")] = '\0';

    newContact->email = newEmail;

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("������ ��������� ������ ��� ���������� �����.\n");
            return;
        }

        printf("������� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
        newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

        printf("������� ����� � ���� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
        newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

        printf("������� ������� � ���� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
        newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

        social_count++;

        printf("������ �������� ��� ���� ���������� ����? (y/n): ");
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

    printf("������� ������� ��������.\n\n");
}

// ������� ��������� ��������
void editContact(ContactList* list) {
    if (list->count == 0) {
        printf("������: ���������� ����� �����.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("������� ��� �������� ��� ��������������: ");
    scanf("%s", nameToEdit);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToEdit) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("������: ������� � ������ '%s' �� ������.\n", nameToEdit);
        return;
    }

    printf("������� ����� ���: ");
    scanf("%s", current->name);

    printf("������� ����� ����� ������: ");
    cleanBuff();
    fgets(current->job, sizeof(current->job), stdin);
    current->job[strcspn(current->job, "\n")] = '\0';

    printf("������� ����� ����� ��������: ");
    cleanBuff();
    fgets(current->phone, sizeof(current->phone), stdin);
    current->phone[strcspn(current->phone, "\n")] = '\0';

    printf("������� ����� ����� ������� ����������� �����: ");
    cleanBuff();
    fgets(current->email.work, sizeof(current->email.work), stdin);
    current->email.work[strcspn(current->email.work, "\n")] = '\0';

    printf("������� ����� ����� �������� ����������� �����: ");
    cleanBuff();
    fgets(current->email.home, sizeof(current->email.home), stdin);
    current->email.home[strcspn(current->email.home, "\n")] = '\0';

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("������ ��������� ������ ��� ���������� �����.\n");
            return;
        }

        printf("������� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].social_network, sizeof(newSocial[social_count].social_network), stdin);
        newSocial[social_count].social_network[strcspn(newSocial[social_count].social_network, "\n")] = '\0';

        printf("������� ����� � ���� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].social_address, sizeof(newSocial[social_count].social_address), stdin);
        newSocial[social_count].social_address[strcspn(newSocial[social_count].social_address, "\n")] = '\0';

        printf("������� ������� � ���� ���������� ����: ");
        cleanBuff();
        fgets(newSocial[social_count].nickname, sizeof(newSocial[social_count].nickname), stdin);
        newSocial[social_count].nickname[strcspn(newSocial[social_count].nickname, "\n")] = '\0';

        social_count++;

        printf("������ �������� ��� ���� ���������� ����? (y/n): ");
        moreSocial = getchar();
        cleanBuff();

    } while (moreSocial == 'y' || moreSocial == 'Y');

    current->social = newSocial;
    current->social_count = social_count;

    printf("������� ������� ��������������.\n\n");
}

// ������� �������� ��������
void deleteContact(ContactList* list) {
    if (list->count == 0) {
        printf("������: ���������� ����� �����.\n");
        return;
    }

    char nameToDelete[MAX_LENGTH];
    printf("������� ��� �������� ��� ��������: ");
    scanf("%s", nameToDelete);

    Contact* current = list->head;
    while (current != NULL && strcmp(current->name, nameToDelete) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("������: ������� � ������ '%s' �� ������.\n", nameToDelete);
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

    printf("������� ������� ������.\n\n");
}

// �������, ������� ������� ������ � �������� 
void printContact(Contact* contact) {
    printf("���: %s\n", contact->name);
    printf("����� ������: %s\n", contact->job);
    printf("����� ��������: %s\n", contact->phone);
    printf("����� ������� ����������� �����: %s\n", contact->email.work);
    printf("����� �������� ����������� �����: %s\n", contact->email.home);
    for (int i = 0; i < contact->social_count; i++) {
        printf("�������� ���������� ����: %s\n", contact->social[i].social_network);
        printf("������ �� ���������� ����: %s\n", contact->social[i].social_address);
        printf("�������: %s\n\n", contact->social[i].nickname);
    }
}

void printAllContacts(ContactList* list) {
    if (list->count == 0) {
        printf("���������� ����� �����.\n");
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
            printf("�����...\n");
            break;
        default:
            printf("������: ������������ �����.\n");
            break;
        }
    } while (tmp != 5);

    return 0;
}