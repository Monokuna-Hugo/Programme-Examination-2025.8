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

// 检查双向链表是否存在环
// 参数: list - 待检查的双向链表指针
// 返回值: 如果链表存在环返回 true，否则返回 false
bool hasCycle(DoubleLinkedList* list){
    // 若链表为空或者链表中只有一个节点，不可能存在环，直接返回 false
    if (isEmpty(list) || list->size <=1){
        return false;
    }

    // 创建一个指针 current，初始指向链表的头节点，用于遍历链表
    Node* current = list->head;
    // 开始遍历链表，直到 current 指针为 NULL
    while (current != NULL){
        // 检查当前节点的下一个节点是否存在，并且下一个节点的前驱指针是否指向当前节点
        // 如果不指向当前节点，说明链表结构异常，存在环，返回 true
        if (current->next != NULL && current->next->prev != current){
            return true;
        }
        // 将 current 指针移动到下一个节点
        current = current->next;
        // 检查 current 指针是否又回到了头节点，如果是则说明存在环，返回 true
        if (current == list->head){
            return true;
        }
    }
    // 遍历结束未发现环，返回 false
    return false;
}

// 合并两个已排序的双向链表，返回一个新的已排序双向链表
DoubleLinkedList* merge2Lists(DoubleLinkedList* list1,DoubleLinkedList* list2){
    // 创建一个新的双向链表，用于存储合并后的结果
    DoubleLinkedList* res = createDoubleLinkedList();
    
    // 创建指针 current1 指向 list1 的头节点，用于遍历 list1
    Node* current1 = list1->head;
    // 创建指针 current2 指向 list2 的头节点，用于遍历 list2
    Node* current2 = list2->head;

    // 同时遍历两个链表，直到其中一个链表遍历完
    while (current1 != NULL && current2 !=NULL){
        // 比较当前两个节点的数据，将较小的数据节点添加到结果链表的尾部
        if (current1->data < current2->data){
            insertAtTail(res,current1->data);
            // 移动 current1 指针到下一个节点
            current1 = current1->next;
        } else {
            insertAtTail(res,current2->data);
            // 移动 current2 指针到下一个节点
            current2 = current2->next;
        }
    }

    // 如果 list1 还有剩余节点，将剩余节点依次添加到结果链表的尾部
    while (current1 != NULL){
        insertAtTail(res,current1->data);
        // 移动 current1 指针到下一个节点
        current1 = current1->next;
    }
    // 如果 list2 还有剩余节点，将剩余节点依次添加到结果链表的尾部
    while (current2 != NULL){
        insertAtTail(res,current2->data);
        // 移动 current2 指针到下一个节点
        current2 = current2->next;
    }
    // 返回合并后的结果链表
    return res;
}

Node* findMiddleNode(DoubleLinkedList* list){
    if (isEmpty(list)){
        return NULL;
    }
    // 使用快慢指针
    Node* slow = list->head;
    Node* fast = list->head;
    // 快指针每次走两步，慢指针每次走一步
    // 当快指针到达尾部时，慢指针就在中间
    while (fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main(){
    DoubleLinkedList* list = createDoubleLinkedList();
    insertAtTail(list,1);
    insertAtTail(list,2);
    insertAtTail(list,3);
    printListForward(list);
    printf(hasCycle(list) ? "true" : "false");
    printf("\n");

    DoubleLinkedList* list2 = createDoubleLinkedList();
    insertAtTail(list2,4);
    insertAtTail(list2,5);
    insertAtTail(list2,6);
    insertAtTail(list2,7);
    printListForward(list2);
    printf(hasCycle(list2) ? "true" : "false");
    printf("\n%d",findMiddleNode(list2)->data);
    printf("\n");

    DoubleLinkedList* list3 = merge2Lists(list,list2);
    printListForward(list3);


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
