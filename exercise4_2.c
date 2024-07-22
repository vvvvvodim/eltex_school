#include <stdio.h>
#include <stdlib.h>

#define MIN_PRIORITY 0
#define MAX_PRIORITY 255

// Структура элемента очереди
typedef struct Node {
    int priority;
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура очереди
typedef struct PriorityQueue {
    Node* head;
    Node* tail;
} PriorityQueue;

// Создание новой (пустой) очереди
PriorityQueue* createQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    pq->tail = NULL;
    return pq;
}

// Добавить новый элемент в очередь
void addInQueue(PriorityQueue* pq, int data, int priority) {
    if (priority < MIN_PRIORITY || priority > MAX_PRIORITY) {
        printf("Invalid priority\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (pq->head == NULL) {
        pq->head = pq->tail = newNode;
    }
    else if (pq->head->priority > priority) {
        newNode->next = pq->head;
        pq->head->prev = newNode;
        pq->head = newNode;
    }
    else {
        Node* temp = pq->head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = newNode;
        }
        else {
            pq->tail = newNode;
        }
        temp->next = newNode;
    }
}

// Извлечение первого элемента очереди
int getFromQueue(PriorityQueue* pq) {
    if (pq->head == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    Node* temp = pq->head;
    int data = temp->data;
    pq->head = pq->head->next;

    if (pq->head != NULL) {
        pq->head->prev = NULL;
    }
    else {
        pq->tail = NULL;
    }

    free(temp);
    return data;
}

// Извлечение элемента из очереди с указанным приоритетом
int getFromQueueWithPriority(PriorityQueue* pq, int priority) {
    if (pq->head == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    Node* temp = pq->head;

    while (temp != NULL && temp->priority != priority) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No element with priority %d found\n", priority);
        return -1;
    }

    int data = temp->data;

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    else {
        pq->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    else {
        pq->tail = temp->prev;
    }

    free(temp);
    return data;
}

// Извлечение элемента из очереди с минимально возможным приоритетом
int getFromQueueWithMinPriority(PriorityQueue* pq, int minPriority) {
    if (pq->head == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    Node* temp = pq->head;

    while (temp != NULL && temp->priority < minPriority) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No element with priority >= %d found\n", minPriority);
        return -1;
    }

    int data = temp->data;

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    else {
        pq->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    else {
        pq->tail = temp->prev;
    }

    free(temp);
    return data;
}

// Выводит содержимое очереди на экран
void printQueue(PriorityQueue* pq) {
    Node* temp = pq->head;
    while (temp != NULL) {
        printf("Data: %d, Priority: %d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

void freeQueue(PriorityQueue* pq) {
    while (pq->head != NULL) {
        Node* temp = pq->head;
        pq->head = pq->head->next;
        free(temp);
    }
    free(pq);
}

int main() {
    PriorityQueue* pq = createQueue();

    addInQueue(pq, 10, 5);
    addInQueue(pq, 20, 1);
    addInQueue(pq, 30, 4);
    addInQueue(pq, 40, 3);

    printf("Initial queue:\n");
    printQueue(pq);

    printf("\nGet from queue with priority 4:\n");
    int data = getFromQueueWithPriority(pq, 4);
    printf("Dequeued data: %d\n", data);
    printQueue(pq);

    printf("\nGet from queue with minimum priority 2:\n");
    data = getFromQueueWithMinPriority(pq, 2);
    printf("Dequeued data: %d\n", data);
    printQueue(pq);

    printf("\nGet from queue first element:\n");
    data = getFromQueue(pq);
    printf("Dequeued data: %d\n", data);
    printQueue(pq);

    freeQueue(pq);
    return 0;
}