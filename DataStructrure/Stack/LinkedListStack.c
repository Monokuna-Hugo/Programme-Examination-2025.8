#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef struct Node
{
    int data;
    struct Node* next;
} Node;


typedef struct LinkedListStack
{
    Node* top;
    int size;
} LinkedListStack;


void initStack(LinkedListStack* stack){
    stack->top = NULL;
}

bool isEmpty(LinkedListStack* stack){
    return stack->top == NULL;
}

bool isFull(LinkedListStack* stack){
    return stack->size == MAX_SIZE;
}

int size(LinkedListStack* stack){
    return stack->size;
}

void push(LinkedListStack* stack, int data){
    Node* popNode = (Node*)malloc(sizeof(Node));
    popNode->data = data;
    popNode->next = stack->top;
    stack->top = popNode;
    stack->size++;
}

int pop(LinkedListStack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    Node* popNode = stack->top;
    int data = popNode->data;
    stack->top = stack->top->next;
    free(popNode);
    stack->size--;
    return data;
}

int peek(LinkedListStack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    return stack->top->data;
}

int main(){
    LinkedListStack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    return 0;
}