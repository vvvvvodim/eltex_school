#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

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

void cleanBuff();
Contact* createContact();
void addContact(ContactList* list);
void editContact(ContactList* list);
void deleteContact(ContactList* list);
void printContact(Contact* contact);
void printAllContacts(ContactList* list);

#endif // CONTACT_LIST_H
