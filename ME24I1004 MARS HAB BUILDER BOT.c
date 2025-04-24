//ME24I1004 VS GEETHA RANJANI
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTS 6
#define STORAGE_SIZE 5

// -----------------------------
// a) Part Delivery (Queue) + Bot Task Manager (Stack)
// -----------------------------
int queue[MAX_PARTS];
int front=-1;
int rear=-1;
//Enqueue function for Part Delivery System
void enqueue(char x){
	if(rear==MAX_PARTS-1){
		printf("OVERFLOW");
	}
	else if(front==-1&&rear==-1){
		front=rear=0;
		queue[rear]=x;
	}
}
//Dequeue function for art Delivery System
void dequeue(){
	if(front==-1&&rear==-1){
		printf("UNDERFLOW");
	}
	else if(front==rear){
		front=rear=-1;
	}
	else{
		printf("%d", queue[front]);
		front++
	}
}

int stack[MAX_PARTS];
int top=-1;
//Push function for Part Delivery System
void push(char x){
	if(top==-1){
		printf("OVERFLOW");
	}
	else{
		top++;
		stack[top]=x;
	}
}
//Pop function for Part Delivery System
void pop(){
	int item;
	if(top==-1){
		printf("UNDERFLOW");
	}
	else{
		printf("%d", stack[top]);
	}
}
// -----------------------------
// b) Assembly Storage Unit (Array)
// -----------------------------
char storage[STORAGE_SIZE];
int storageIndex= 0;

void storeHabitat(char name) {
    storage[storageIndex]= name;
    printf("Storing %s at slot %d\n", name, storageIndex);
    storageIndex = (storageIndex + 1) % STORAGE_SIZE;
}

// -----------------------------
// c) Damaged -> Repaired Tracker
// -----------------------------
typedef struct SinglyNode {
    char name;
    struct SinglyNode* next;
} SinglyNode;

typedef struct DoublyNode {
    char name;
    struct DoublyNode* next;
    struct DoublyNode* prev;
} DoublyNode;

SinglyNode * insertDamaged(SinglyNode* head, char name) {
    SinglyNode* newNode = malloc(sizeof(SinglyNode));
    newNode->name= name;
    newNode->next= head;
    return newNode;
}

SinglyNode* removeDamaged(SinglyNode* head, char name, int* found) {
    SinglyNode *temp= head, *prev= NULL;
    while (temp!=NULL) {
        if (strcmp(temp->name, name) == 0) {
            	*found = 1;
            	if (prev == NULL){
            		return temp->next;
				}
            	prev->next = temp->next;
            	free(temp);
            	return head;
        }
        prev= temp;
        temp= temp->next;
    }
    return head;
}

DoublyNode* insertRepaired(DoublyNode *head, char name) {
    DoublyNode *newNode= malloc(sizeof(DoublyNode));
    newNode->name= name;
    newNode->next= NULL;
    newNode->prev= NULL;

    if (head==NULL){
    	return newNode;
	}
    DoublyNode *temp = head;
    while (temp->next!= NULL){
    	temp=temp->next;
	}
    temp->next= newNode;
    newNode->prev= temp;
    return head;
}

void traverseForward(DoublyNode* head) {
    while(head){
        printf("Forward: %s\n", head->name);
        head = head->next;
    }
}

void traverseBackward(DoublyNode* tail) {
    while(tail){
        printf("Backward: %s\n", tail->name);
        tail = tail->prev;
    }
}

// -----------------------------
// d) Circular Linked List: Priority Upgrades
// -----------------------------
typedef struct CircularNode {
    char name;
    struct CircularNode* next;
} CircularNode;

CircularNode* insertCircular(CircularNode* head, char name) {
    CircularNode* newNode = malloc(sizeof(CircularNode));
    newNode->name= name;
    if (head==NULL) {
        newNode->next=newNode;
        return newNode;
    }
    CircularNode* temp=head;
    while (temp->next!= head){
    	temp= temp->next;
	}
    temp->next= newNode;
    newNode->next= head;
    return head;
}

void traverseCircular(CircularNode* head, int times) {
    if (!head) return;
    CircularNode* temp = head;
    for (int i = 0; i < times; ++i) {
        printf("Upgrading: %s\n", temp->name);
        temp = temp->next;
    }
}

// -----------------------------
// MAIN FUNCTION
// -----------------------------
int main() {
    printf("=== Mars Habitat Builder Bot ===\n\n");

    //TASK A
    printf("\n[Task A] Construction Queue & Stack:\n");
    char parts[MAX_PARTS] = {"Wall", "Roof", "Door", "Window", "Airlock", "Vent"};

    for (int i = 0; i < MAX_PARTS; i++) enqueue(parts[i]);
    for (int i = 0; i < MAX_PARTS; i++) push(dequeue());

    char part;
    while((part=pop())) {
        printf("Installing: %s\n", part);
    }
    // LIFO fits because 'Vent' is installed last for air-sealing after core structure.

    //TASK B
    printf("\n[Task B] Habitat Storage (Circular Array):\n");
    char habitats[7] = {"Hab1", "Hab2", "Hab3", "Hab4", "Hab5", "Hab6", "Hab7"};
    for(int i = 0; i < 7; i++){
    	storeHabitat(habitats[i]);
	}
    // Older habitats are overwritten due to settler arrival and limited Martian real estate.

    //TASK C
    printf("\n[Task C] Damaged and Repaired Habitat Tracker:\n");
    SinglyNode* damagedList= NULL;
    damagedList= insertDamaged(damagedList, "Hab6");
    damagedList= insertDamaged(damagedList, "Hab3");

    int found = 0;
    damagedList= removeDamaged(damagedList, "Hab3", &found);

    DoublyNode* repairedList= NULL;
    if(found){
    	repairedList= insertRepaired(repairedList, "Hab3");
	}

    traverseForward(repairedList);
    DoublyNode* tail= repairedList;
    while(tail && tail->next){
    	tail = tail->next;
	}
    traverseBackward(tail);
    printf("// Hab3’s door was cracked by a Martian dust storm, bots sealed it using polymer patches.\n");

    //TASK D
    printf("\n[Task D] Priority Upgrade Circular Tracker:\n");
    CircularNode* upgradeList = NULL;
    upgradeList = insertCircular(upgradeList, "Hab1");
    upgradeList = insertCircular(upgradeList, "Hab4");
    traverseCircular(upgradeList, 4);
    printf("// Hab1 got smart solar panels. Hab4 received a greenhouse dome for fresh produce.\n");

    return 0;
}

