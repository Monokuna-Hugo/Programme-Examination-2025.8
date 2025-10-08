#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
    int items[MAX_SIZE];
    int top;
} ArrayStack;

// 初始化栈
void initStack(ArrayStack* stack) {
    stack->top = -1;
}

//
bool isEmpty(ArrayStack* stack){
    return stack->top == -1;
}

bool isFull(ArrayStack* stack){
    return stack->top == MAX_SIZE - 1;
}

int size(ArrayStack* stack){
    return stack->top + 1;
}

int pop(ArrayStack* stack){
    if (isEmpty(stack)) return -1;
    stack->top--;
    return stack->items[stack->top + 1];
}

void push(ArrayStack* stack,int data){
    if (isFull(stack)) return;
    stack->top++;
    stack->items[stack->top] = data;
}

int peek(ArrayStack* stack){
    if (isEmpty(stack)) return -1;
    return stack->items[stack->top];
}


int main(){
    ArrayStack* stack;
    initStack(stack);

    push(stack,1);
    push(stack,2);
    push(stack,3);
    push(stack,4);
    push(stack,5);
    push(stack,6);
    push(stack,7);
    push(stack,8);
    push(stack,9);
    push(stack,10);
    printf("%d",peek(stack));

    
}

