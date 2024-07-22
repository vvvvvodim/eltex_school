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

// ��������������� ������� ������� ������ �����
void cleanBuff() {
    fseek(stdin, 0, SEEK_END);
}

// ������� �������� ������ ���� ������
Node* createNode(Contact contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� ���������� �������� � ������
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

// ������� ������ ������������ ���� � ������
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// ������� �������� �������� �� ������
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

// ������� ������ �������� � ������
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

// ������� ���������� ������ �������� � ������ ������
Node* inputContact(Node* root) {
    Contact newContact;
    Email newEmail;
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("������� ���: ");
    scanf("%s", newContact.name);

    printf("������� ����� ������: ");
    cleanBuff();
    fgets(newContact.job, sizeof(newContact.job), stdin);
    newContact.job[strcspn(newContact.job, "\n")] = '\0';

    printf("������� ����� ��������: ");
    cleanBuff();
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    printf("������� ����� ������� ����������� �����: ");
    cleanBuff();
    fgets(newEmail.work, sizeof(newEmail.work), stdin);
    newEmail.work[strcspn(newEmail.work, "\n")] = '\0';

    printf("������� ����� �������� ����������� �����: ");
    cleanBuff();
    fgets(newEmail.home, sizeof(newEmail.home), stdin);
    newEmail.home[strcspn(newEmail.home, "\n")] = '\0';

    newContact.email = newEmail;

    do {
        newSocial = realloc(newSocial, (social_count + 1) * sizeof(SocialProfile));
        if (newSocial == NULL) {
            printf("������ ��������� ������ ��� ���������� �����.\n");
            return root;
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

    newContact.social = newSocial;
    newContact.social_count = social_count;

    return addContact(root, newContact);
}

// ������� ��������� ��������
void editContact(Node* root) {
    if (root == NULL) {
        printf("������: ���������� ����� �����.\n");
        return;
    }

    char nameToEdit[MAX_LENGTH];
    SocialProfile* newSocial = NULL;
    int social_count = 0;
    char moreSocial;

    printf("������� ��� �������� ��� ��������������: ");
    scanf("%s", nameToEdit);

    Node* contactNode = findContact(root, nameToEdit);
    if (contactNode == NULL) {
        printf("������: ������� � ������ '%s' �� ������.\n", nameToEdit);
        return;
    }

    printf("������� ����� ���: ");
    scanf("%s", contactNode->contact.name);

    printf("������� ����� ����� ������: ");
    cleanBuff();
    fgets(contactNode->contact.job, sizeof(contactNode->contact.job), stdin);
    contactNode->contact.job[strcspn(contactNode->contact.job, "\n")] = '\0';

    printf("������� ����� ����� ��������: ");
    cleanBuff();
    fgets(contactNode->contact.phone, sizeof(contactNode->contact.phone), stdin);
    contactNode->contact.phone[strcspn(contactNode->contact.phone, "\n")] = '\0';

    printf("������� ����� ����� ������� ����������� �����: ");
    cleanBuff();
    fgets(contactNode->contact.email.work, sizeof(contactNode->contact.email.work), stdin);
    contactNode->contact.email.work[strcspn(contactNode->contact.email.work, "\n")] = '\0';

    printf("������� ����� ����� �������� ����������� �����: ");
    cleanBuff();
    fgets(contactNode->contact.email.home, sizeof(contactNode->contact.email.home), stdin);
    contactNode->contact.email.home[strcspn(contactNode->contact.email.home, "\n")] = '\0';

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

    contactNode->contact.social = newSocial;
    contactNode->contact.social_count = social_count;

    printf("������� ������� ��������������.\n\n");
}

// ������� ������ ���� ��������� (����� ������)
void printContacts(Node* root) {
    if (root != NULL) {
        printContacts(root->left);
        printf("���: %s\n", root->contact.name);
        printf("����� ������: %s\n", root->contact.job);
        printf("����� ��������: %s\n", root->contact.phone);
        printf("����� ������� ����������� �����: %s\n", root->contact.email.work);
        printf("����� �������� ����������� �����: %s\n", root->contact.email.home);
        for (int i = 0; i < root->contact.social_count; i++) {
            printf("�������� ���������� ����: %s\n", root->contact.social[i].social_network);
            printf("������ �� ���������� ����: %s\n", root->contact.social[i].social_address);
            printf("�������: %s\n", root->contact.social[i].nickname);
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
            root = inputContact(root);
            break;
        case 2:
            printf("\033[0d\033[2J");
            editContact(root);
            break;
        case 3: {
            printf("\033[0d\033[2J");
            char nameToDelete[MAX_LENGTH];
            printf("������� ��� �������� ��� ��������: ");
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
            printf("�����...\n");
            break;
        default:
            printf("\033[0d\033[2J");
            printf("������: ������������ �����.\n");
            break;
        }
    } while (tmp != 5);

    return 0;
}