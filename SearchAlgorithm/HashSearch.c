#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable{
    int size;
    int capacity;
    Node** buckets;
    float loadFactor;
} HashTable;

Node* createNode(char* key, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

HashTable* createHashTable(int capacity){
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->buckets = (Node**)calloc(capacity,sizeof(Node*));
    hashTable->size = 0;
    hashTable->loadFactor = 0.75f;
    hashTable->capacity = capacity;
    return hashTable;
}

int hash(char* key,int capacity){
    int hash = 0;
    while (*key){
        hash = (hash * 31 + *key) % capacity;
        key++;
    }
    return hash;
}

void resize(HashTable* table,int newCapacity);

// 向哈希表中插入或更新键值对
void put(HashTable* hashTable,char* key, int value){
    // 检查当前哈希表的负载因子是否超过预设值
    // 如果超过，则调用resize函数将哈希表容量扩大为原来的两倍
    if ((float)hashTable->size / hashTable->capacity >= hashTable->loadFactor){
        resize(hashTable, hashTable->capacity * 2);
    }

    // 计算键对应的哈希索引
    int index = hash(key, hashTable->capacity);
    // 创建一个新的节点，存储要插入的键值对
    Node* newNode = createNode(key,value);

    // 如果该索引位置的桶为空，直接将新节点放入该位置
    if (hashTable->buckets[index] == NULL){
        hashTable->buckets[index] = newNode;
        // 哈希表中元素数量加1
        hashTable->size++;
        return;
    }

    // 如果该索引位置的桶不为空，获取该位置的第一个节点
    Node* current = hashTable->buckets[index];
    // 遍历链表，查找是否已存在相同的键
    while (current != NULL){
        // 如果找到相同的键，更新该节点的值
        if (strcmp(current->key, key) == 0){
            current->value = value;
            // 释放之前创建的新节点的内存，避免内存泄漏
            free(newNode->key);
            free(newNode);
            return;
        }

        // 如果当前节点是链表的最后一个节点，跳出循环
        if (current->next == NULL){
            break;
        }

        // 移动到下一个节点继续查找
        current = current->next;
    }

    // 将新节点插入到链表的末尾
    current->next = newNode;
    // 哈希表中元素数量加1
    hashTable->size++;
}

void resize(HashTable* table,int newCapacity){
    // 检查新容量是否小于等于当前容量
    if (newCapacity <= table->capacity){
        return;
    }

    Node** oldBuckets = table->buckets;
    int oldCapacity = table->capacity;

    // 创建一个新的哈希表，容量为新容量
    table->buckets = (Node**)calloc(newCapacity,sizeof(Node*));
    table->capacity = newCapacity;
    table->size = 0;

    // 遍历旧哈希表的每个桶
    for (int i = 0; i < oldCapacity; i++){
        // 获取当前桶的第一个节点
        Node* current = oldBuckets[i];
        // 遍历链表，将每个节点重新哈希到新哈希表中
        while (current != NULL){
            Node* next = current->next;
            // 将当前节点插入到新哈希表的对应桶中
            put(table,current->key,current->value);
            // 移动到下一个节点继续处理
            free(current->key);
            free(current);
            current = next;
        }
    }
    // 释放旧哈希表的内存
    free(oldBuckets);
}

bool get(HashTable* table, char* key, int* value){
    // 获取哈希索引
    int index = hash(key, table->capacity);
    // 获取该索引位置的第一个节点
    Node* current = table->buckets[index];
    // 遍历链表查找匹配的键
    while (current != NULL){
        if (strcmp(current->key,key) == 0){
            *value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool removeKey(HashTable* table, char* key){
    int index = hash(key, table->capacity);
    Node* current = table->buckets[index];
    Node* prev = NULL;

    //遍历链表查找目标节点
    while (current != NULL){
        if (strcmp(current->key, key) == 0){
            break;
        }
        prev = current;
        current = current->next;
    }
    //未找到目标节点，返回false
    if (current == NULL){
        return false;
    }
    //找到目标节点时，删除该节点
    if (prev == NULL){
        table->buckets[index] = current->next;
    }else {
        prev->next = current->next;
    }
    // 释放目标节点的内存
    free(current->key);
    free(current);
    table->size--;
    return true;
}

void freeHashTable(HashTable* table){
    // 遍历哈希表的每个桶
    for (int i = 0; i < table->capacity; i++){
        // 获取当前桶的第一个节点
        Node* current = table->buckets[i];
        // 遍历链表，释放每个节点的内存
        while (current != NULL){
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    // 释放哈希表的内存
    free(table->buckets);
    free(table);
}

int main(){
    HashTable* table = createHashTable(10);
    put(table, "key1", 100);
    put(table, "key2", 200);
    put(table, "key3", 300);
    put(table, "key4", 400);

    int value;
    if (get(table, "key4", &value)){
        printf("key4: %d\n", value);
    }
    if (removeKey(table, "key2")){
        printf("key2 removed\n");
    }
    freeHashTable(table);
    return 0;
}
