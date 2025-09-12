#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct SingleLinkedList{
    Node* head;
} SingleLinkedList;

//初始化链表
/*
    1.为链表分配内存
    2.如果分配失败，则返回空指针
    3.如果分配成功，则将头节点指向空
*/
SingleLinkedList* createLinkedList(){
    SingleLinkedList* list = (SingleLinkedList*)malloc(sizeof(SingleLinkedList));
    if (list == NULL){
        printf("内存分配失败");
        return NULL;
    }
    list->head = NULL;
    return list;
}

//判断链表是否为空，只需要判断头节点是否为空就行
/*
    1.判断头节点是否为空
    2.如果为空，则返回true
    3.如果不为空，则返回false
*/
bool isEmpty(SingleLinkedList* list){
    return list->head == NULL;
}

//创建新节点
/*
    1.为新节点分配内存
    2.如果分配失败，则返回空指针
    3.如果分配成功，则将数据赋值给新节点
    4.将新节点的下一个节点指针指向空
*/

Node* createNode(int data){
    //1.为新节点分配内存
    Node* newNode = (Node*)malloc(sizeof(Node));
    //2.如果分配失败，则返回空指针
    if (newNode == NULL){
        printf("内存分配失败");
        return NULL;
    }
    //3.如果分配成功，则将数据赋值给新节点
    newNode->data = data;
    //4.将新节点的下一个节点指针指向空
    newNode->next = NULL;
    //5.返回新节点
    return newNode;
}

//在链表头插入节点
/*
    1.创建新节点
    2.如果创建失败，则返回
    3.如果创建成功，则将新节点的下一个节点指针指向头节点
*/

void insertAtHead(SingleLinkedList* list,int ddta){
    //1.创建新节点
    Node* newNode = createNode(ddta);
    //2.如果创建失败，则返回
    if (isEmpty(list)){
        //如果链表为空，则将新节点赋值给头节点
        list->head = newNode;
    } else {
        //3.如果创建成功，则将新节点的下一个节点指针指向头节点
        newNode->next = list->head;
        //4.将头节点指向新节点
        list->head = newNode;
    }
}

//在链表尾插入节点
/*
    1.创建新节点
    2.如果创建失败，则返回
    3.遍历链表，找到最后一个节点
    4.将新节点赋值给最后一个节点的下一个节点指针
*/
void insertAtTail(SingleLinkedList* list,int ddta){
    //1.创建新节点
    Node* newNode = createNode(ddta);
    //2.如果创建失败，则返回
    if (isEmpty(list)){
        list->head = newNode;
        return;
    }
    //3.遍历链表，找到最后一个节点
    Node* current = list->head;
    while (current->next != NULL){
        current = current->next;
    }
    //4.将新节点赋值给最后一个节点的下一个节点指针
    current->next = newNode;
}

//在指定位置插入节点
/*
    1.判断位置是否有效
    2.定义前后节点
    3.遍历链表，找到指定位置的前一个节点
    4.将新节点赋值给前一个节点的下一个节点指针
    5.将当前节点赋值给新节点的下一个节点指针
*/
void insertAtPosition(SingleLinkedList* list,int ddta,int position){
    //1.判断位置是否有效
    switch (position)
    {
    case 0 :
        /* code */
        printf("位置无效");
        return;
    case 1:
        insertAtHead(list,ddta);
        return;
    }
    //2. 定义前后节点
    Node* newNode = createNode(ddta);
    Node* current = list->head;
    Node* previous = NULL;
    int count = 0;
    //3. 遍历链表，找到指定位置的前一个节点
    while (current != NULL && count < position){
        previous = current;
        current = current->next;
        count++;
    }
    //4. 将新节点赋值给前一个节点的下一个节点指针
    previous->next = newNode;
    //5. 将当前节点赋值给新节点的下一个节点指针
    newNode->next = current;
}

//删除指定节点
/*
    1.判断链表是否为空
    2.找到了链表头节点对应的数据
    3.遍历链表，找到指定位置的前一个节点数据
    4.如果找到了指定节点，就把当前节点的下一个节点指针赋值给前一个节点的下一个节点指针
*/
void deleteNode(SingleLinkedList* list,int data){
   //1.判断链表是否为空
    if (isEmpty(list)){
        printf("链表为空");
        return;
    }
    //2.找到了链表头节点对应的数据
    if (list->head->data == data){
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }
    //3. 遍历链表，找到指定位置的前一个节点数据
    Node* current = list->head;
    Node* previous = NULL;
    while (current != NULL && current->data != data){
        previous = current;
        current = current->next;
    }
    //4. 如果找到了指定节点，就把当前节点的下一个节点指针赋值给前一个节点的下一个节点指针
    if (current != NULL){
        previous->next = current->next;
        free(current);
        printf("删除成功");
    } else {
        printf("未找到指定节点");
    }
}

//查找指定节点
/*
    1.判断链表是否为空
    2.遍历链表，查找指定节点
    3.如果找到指定节点，就返回true
    4.如果没有找到指定节点，就返回false
    5.返回查找结果
*/
bool searchNode(SingleLinkedList* list, int data){
    //1.判断链表是否为空
    if (isEmpty(list)){
        printf("链表为空");
        return false;
    }
    //2.遍历链表，查找指定节点
    Node* current = list->head;
    while (current != NULL){
        if (current->data == data){
            return true;
        }
        current = current->next;
    }
    return false;
}

//打印链表
/*
    1.判断链表是否为空
    2.遍历链表，打印链表
*/
void displayList(SingleLinkedList* list){
    //1.判断链表是否为空
    if (isEmpty(list)){
        printf("链表为空");
        return;
    }
    //2.遍历链表，打印链表
    Node* current = list->head;
    while (current != NULL){
        printf("%d -> ",current->data);
        current = current->next;
    }
    printf("NULL");
}

//统计链表节点数量
/*
    1.遍历链表，统计节点数量
    2.返回节点数量
*/
int countLinkedListNode(SingleLinkedList* list){
    //遍历链表，统计节点数量
    int count = 0;
    Node* current = list->head;
    while (current != NULL){
        count++;
        current = current->next;
    }
    return count;
}
//释放链表内存
/*
    1.遍历链表，释放每个节点的内存
    2.释放链表头节点的内存
*/
void freeLinkedList(SingleLinkedList* list){
    Node* current = list->head;
    Node* next;
    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

//反转链表
/*
    1.定义前一个节点指针，当前节点指针，下一个节点指针
    2.遍历链表，反转链表
    3.将链表头节点指针赋值为前一个节点指针
    4.返回反转后的链表
*/
void reverseLinkedList(SingleLinkedList* list){
    Node* previous = NULL;
    Node* next = NULL;
    Node* current = list->head;

    while (current != NULL){
        next = current->next; // 1. 保存当前节点的下一个节点指针
        current->next = previous; // 2. 将当前节点的下一个节点指针赋值为前一个节点指针
        previous = current; // 3. 将前一个节点指针赋值为当前节点指针
        current = next; // 4. 将当前节点指针赋值为下一个节点指针
    }
    list->head = previous; // 5. 将链表头节点指针赋值为前一个节点指针
    printf("链表反转成功\n");
}

SingleLinkedList* mergeLinkedList(SingleLinkedList* list1,SingleLinkedList* list2){
    SingleLinkedList* mergedList = createLinkedList();
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    while (current1 != NULL){
        insertAtTail(mergedList,current1->data);
        current1 = current1->next;
    }
    while (current2 != NULL){
        insertAtTail(mergedList,current2->data);
        current2 = current2->next;
    }
    return mergedList;
}

// 单链表的取值算法，获取指定位置的节点数据
/*
    1. 判断链表是否为空或位置是否无效
    2. 初始化计数器和当前节点指针
    3. 遍历链表找到指定位置的节点
    4. 如果找到指定位置节点，返回其数据；否则返回 -1 表示未找到
*/
int getValueAtPosition(SingleLinkedList* list, int position) {
    // 1. 判断链表是否为空或位置是否无效
    if (isEmpty(list) || position <= 0) {
        printf("链表为空或位置无效\n");
        return -1;
    }

    // 2. 初始化计数器和当前节点指针
    int count = 1;
    Node* current = list->head;

    // 3. 遍历链表找到指定位置的节点
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }

    // 4. 如果找到指定位置节点，返回其数据；否则返回 -1 表示未找到
    if (current != NULL) {
        return current->data;
    } else {
        printf("未找到指定位置的节点\n");
        return -1;
    }
}


int main(){
    SingleLinkedList* list = createLinkedList();

    insertAtTail(list,11);
    insertAtTail(list,20);
    insertAtTail(list,31);
    insertAtTail(list,40);
    insertAtTail(list,51);
    displayList(list);
    printf("\n");
    //统计链表节点数量
    printf("链表节点数量: %d", countLinkedListNode(list));
    printf("\n");

    insertAtPosition(list,100,3);
    displayList(list);
    printf("\n");
    //统计链表节点数量
    printf("链表节点数量: %d", countLinkedListNode(list));
    printf("\n");

    deleteNode(list,100);
    printf("\n");
    displayList(list);
    printf("\n");
    //统计链表节点数量
    printf("链表节点数量: %d", countLinkedListNode(list));
    printf("\n");

    printf("查找结果: %s", searchNode(list, 20) ? "true" : "false");  // 输出: 查找结果: true
    printf("\n");


    printf("链表长度: %d", countLinkedListNode(list));                         // 输出: 链表长度: 4
    printf("\n");

    reverseLinkedList(list);
    displayList(list);
    printf("\n");

    freeLinkedList(list);


    return 0;

}
