#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTS 6
#define STORAGE_SIZE 5

// -----------------------------
// a) Part Delivery and Bot Construction Order (Queue + Stack using Arrays)
// -----------------------------
char* partQueue[MAX_PARTS];
int front = -1, rear = -1;

void enqueue(char* part) {
    if (rear == MAX_PARTS - 1) {
        printf("Queue is full! Cannot add more parts.\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    partQueue[rear] = part;
}

char* dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty!\n");
        return NULL;
    }
    return partQueue[front++];
}

char* partStack[MAX_PARTS];
int top = -1;

void push(char* part) {
    if (top == MAX_PARTS - 1) {
        printf("Stack overflow! Too many parts to install.\n");
        return;
    }
    top++;
    partStack[top] = part;
}

char* pop() {
    if (top == -1) {
        return NULL;
    }
    return partStack[top--];
}

// -----------------------------
// b) Assembly Storage Unit (Circular Array)
// -----------------------------
char* habitatStorage[STORAGE_SIZE];
int storageIndex = 0;

void storeHabitat(char* habitat) {
    habitatStorage[storageIndex] = habitat;
    printf("Storing habitat: %s at slot %d\n", habitat, storageIndex);
    storageIndex = (storageIndex + 1) % STORAGE_SIZE;
}

// -----------------------------
// c) Damaged -> Repaired Tracker
// -----------------------------
typedef struct SinglyNode {
    char* name;
    struct SinglyNode* next;
} SinglyNode;

typedef struct DoublyNode {
    char* name;
    struct DoublyNode* next;
    struct DoublyNode* prev;
} DoublyNode;

SinglyNode* insertDamaged(SinglyNode* head, char* name) {
    SinglyNode* newNode = malloc(sizeof(SinglyNode));
    newNode->name = strdup(name);
    newNode->next = head;
    return newNode;
}

SinglyNode* removeDamaged(SinglyNode* head, char* name, int* found) {
    SinglyNode *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            *found = 1;
            if (prev == NULL) {
                SinglyNode* next = temp->next;
                free(temp->name);
                free(temp);
                return next;
            } else {
                prev->next = temp->next;
                free(temp->name);
                free(temp);
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

DoublyNode* insertRepaired(DoublyNode* head, char* name) {
    DoublyNode* newNode = malloc(sizeof(DoublyNode));
    newNode->name = strdup(name);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) return newNode;

    DoublyNode* temp = head;
    while (temp->next != NULL) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

void traverseForward(DoublyNode* head) {
    while (head != NULL) {
        printf("Repaired (forward): %s\n", head->name);
        head = head->next;
    }
}

void traverseBackward(DoublyNode* tail) {
    while (tail != NULL) {
        printf("Repaired (backward): %s\n", tail->name);
        tail = tail->prev;
    }
}

// -----------------------------
// d) Priority Upgrade Circular Linked List
// -----------------------------
typedef struct CircularNode {
    char* name;
    struct CircularNode* next;
} CircularNode;

CircularNode* insertCircular(CircularNode* head, char* name) {
    CircularNode* newNode = malloc(sizeof(CircularNode));
    newNode->name = strdup(name);

    if (head == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    CircularNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

void traverseCircular(CircularNode* head, int times) {
    if (head == NULL) return;

    CircularNode* temp = head;
    int i=0;
    for (i; i < times; i++) {
        printf("Upgrade cycle: %s\n", temp->name);
        temp = temp->next;
    }
}

// -----------------------------
// Main Menu System for User Interaction
// -----------------------------
int main() {
    int choice;
    char* parts[MAX_PARTS] = {"Wall", "Roof", "Door", "Window", "Airlock", "Vent"};
    char* habitats[7] = {"Hab1", "Hab2", "Hab3", "Hab4", "Hab5", "Hab6", "Hab7"};
    SinglyNode* damagedList = NULL;
    DoublyNode* repairedList = NULL;
    CircularNode* upgradeList = NULL;

    printf("=== Mars Habitat Construction Bot ===\n");

    while (1) {
        // Display the menu
        printf("\nSelect an action:\n");
        printf("1. Task A: Part Delivery and Bot Construction Order\n");
        printf("2. Task B: Assembly Storage Unit\n");
        printf("3. Task C: Damaged Habitat Tracker\n");
        printf("4. Task D: Priority Upgrades\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Task A: Part Delivery and Bot Stack
                printf("\n[Task A] Part Delivery Queue and Bot Stack:\n");

                // Enqueue all parts
                int i=0;
                for (i; i < MAX_PARTS; i++) {
                    enqueue(parts[i]);
                }

                // Dequeue and push onto stack
                char* part;
                while ((part = dequeue()) != NULL) {
                    push(part);
                }

                // Pop from stack (LIFO order)
                while ((part = pop()) != NULL) {
                    printf("Bot installing: %s\n", part);
                }

                printf("Note: LIFO ensures 'Vent' is installed last to seal the structure after all major parts are set.\n");
                break;
            }
            case 2: {
                // Task B: Habitat Assembly Storage
                printf("\n[Task B] Habitat Assembly Storage:\n");
                int i=0;
                for (i; i < 7; i++) {
                    storeHabitat(habitats[i]);
                }
                printf("Note: Limited Martian land forces newer arrivals (Hab6 & Hab7) to overwrite older, settled habitats.\n");
                break;
            }
            case 3: {
                // Task C: Damaged Habitat Tracker
                printf("\n[Task C] Damaged and Repaired Habitat Tracker:\n");

                damagedList = insertDamaged(damagedList, "Hab6");
                damagedList = insertDamaged(damagedList, "Hab3");

                int found = 0;
                damagedList = removeDamaged(damagedList, "Hab3", &found);

                if (found) {
                    repairedList = insertRepaired(repairedList, "Hab3");
                }

                // Traverse repaired list
                traverseForward(repairedList);

                DoublyNode* tail = repairedList;
                while (tail && tail->next) {
                    tail = tail->next;
                }
                traverseBackward(tail);

                printf("Note: Hab3’s door cracked during a Martian dust storm. Repair bots patched it using a polymer sealant.\n");
                break;
            }
            case 4: {
                // Task D: Priority Habitat Upgrades
                printf("\n[Task D] Priority Habitat Upgrades:\n");

                upgradeList = insertCircular(upgradeList, "Hab1");
                upgradeList = insertCircular(upgradeList, "Hab4");

                traverseCircular(upgradeList, 4);

                printf("Note: Hab1 was upgraded with solar panels, while Hab4 received a greenhouse dome for food.\n");
                break;
            }
            case 5:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
