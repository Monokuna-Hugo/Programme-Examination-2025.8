#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoubleLinkedList{
    Node* head;
    Node* tail;
    int size;
} DoubleLinkedList;

DoubleLinkedList* createDoubleLinkedList(){
    DoubleLinkedList* list = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    if (list == NULL){
        printf("创建失败");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL){
        printf("创建失败");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

bool isEmpty(DoubleLinkedList* list){
    return list->head == NULL;
}


int size(DoubleLinkedList* list){
    return list->size;
}

void insertAtHead(DoubleLinkedList* list,int data){
    Node* newNode = createNode(data);
    if (isEmpty(list)){
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}

void insertAtTail(DoubleLinkedList* list,int data){
    Node* newNode = createNode(data);
    if (isEmpty(list)){
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
}

void insertAtPosition(DoubleLinkedList* list,int data,int position){
    if (position < 0 || position > list->size){
        return;
    }

    if (position == 0){
        insertAtHead(list,data);
        return;
    }

    if (position == list->size){
        insertAtTail(list,data);
        return;
    }

    Node* newNode = createNode(data);
    Node* current;

    if (position <= list->size / 2){
        current = list->head;
        for (int i = 0;i < position ;i++){
            current = current->next;
        }
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    } else {
        current = list->tail;
        for (int i = list->size-1;i>position;i--){
            current = current->prev;
        }
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        
    }
    list->size++;
}

    


void deleteAtHead(DoubleLinkedList* list){
    if (isEmpty(list)){
        return;
    }
    Node* temp = list->head;
    if (list->head == list->tail){
        list->head == NULL;
        list->tail == NULL;
    }else{
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    free(temp);
    list->size--;
}

void deleteAtTail(DoubleLinkedList* list){
    if (isEmpty(list)){
        return;
    }
    Node* temp = list->tail;
    if (list->head == list->tail){
        list->head == NULL;
        list->tail == NULL;
        free(temp);
        return;
    }
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(temp);
}

void deleteAtPosition(DoubleLinkedList* list,int position){
    if (position < 0 || position > list->size){
        return;
    }
    
    if (position == 0){
        deleteAtHead(list);
        return;
    }

    if (position == list->size){
        deleteAtTail(list);
        return;
    }

    Node* current;
    if (position <= list->size / 2){
        current = list -> head;
        for (int i = 0; i<position; i++){
            current = current->next;
        }
    } else {
        current = list->tail;
        for (int i = list->size-1;i>position;i--){
            current = current->prev;
        }
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    list->size--;
}

void deleteNode(DoubleLinkedList* list,int data){
    if (isEmpty(list)){
        return;
    }

    if (list->head->data == data){
        deleteAtHead(list);
        return;
    }

    if (list->tail->data == data){
        deleteAtTail(list);
        return;
    }

    Node* current = list->head->next;
    while (current != NULL && current != list->tail){
        if (current->data == data){
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            list->size--;
            return;
        }
        current = current->next;
    }
}

bool searchNode(DoubleLinkedList* list,int data){
    if (isEmpty(list)){
        return false;
    }

    Node* current = list->head;
    while (current != NULL){
        if (current->data == data){
            return true;
        }
        current = current->next;
    }
    return false;
}

void printListForward(DoubleLinkedList* list){
    if (isEmpty(list)){
        return;
    }
    printf("NULL <- ");
    Node* current = list->head;
    while (current != NULL){
        printf("%d ",current->data);
        if (current->next != NULL){
            printf(" <-> ");
        } else {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("NULL\n");
}

void printListBackward(DoubleLinkedList* list){
    if (isEmpty(list)){
        return;
    }
    printf("NULL <- ");
    Node* current = list->tail;
    while (current != NULL){
        printf("%d ",current->data);
        if (current->prev != NULL){
            printf(" <-> ");
        } else {
            printf(" -> ");
        }
        current = current->prev;
    }
    printf("NULL\n");
}

void freeList(DoubleLinkedList* list){
    Node* current = list->head;
    Node* next;

    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main(){
    DoubleLinkedList* list = createDoubleLinkedList();
    insertAtTail(list,1);
    insertAtTail(list,2);
    insertAtTail(list,3);
    printListForward(list);

    


    insertAtPosition(list,4,2);
    printListForward(list);


    deleteNode(list,4);
    printListForward(list);


    deleteAtHead(list);
    printListForward(list);


    deleteAtTail(list);
    printListForward(list);


    freeList(list);
    return 0;
}
