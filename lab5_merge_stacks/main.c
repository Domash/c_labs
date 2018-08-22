//
//  main.c
//  LAB5
//
//  Created by Денис Домашевич on 04.05.2018.
//  Copyright © 2018 Денис Домашевич. All rights reserved.
//

#include <mm_malloc.h>
#include <stdbool.h>
#include <stdio.h>

int getInt() {
    int res;
    while(true) {
        if(scanf("%d", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

typedef struct Node {
    int data;
    struct Node *next;
} StackNode;

typedef struct {
    int len;
    StackNode *top;
} Stack;

void init(Stack *myStack) {
    myStack -> top = NULL;
    myStack -> len = 0;
}

void push(Stack *myStack, int data) {
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode -> data = data;
    newNode -> next = myStack -> top;
    myStack -> top = newNode;
    myStack -> len = myStack -> len + 1;
}

void pop(Stack *myStack) {
    StackNode *oldTop = myStack -> top;
    myStack -> top = oldTop -> next;
    free(oldTop);
    myStack -> len = myStack -> len - 1;
}

void show(Stack *myStack) {
    StackNode *currNode = myStack -> top;
    while(currNode != NULL) {
        printf("%d ", currNode -> data);
        currNode = currNode -> next;
    }
    printf("\n");
}

int min(int a, int b) {
    return a > b ? b : a;
}

Stack* mergeStacks(Stack *a, Stack *b) {
    Stack *newStack = malloc(sizeof(Stack));
    init(newStack);
    int newElement;
    while(true) {
        if(a -> top == NULL && b -> top == NULL) {
            break;
        } else if(a -> top == NULL && b -> top != NULL) {
            newElement = b -> top -> data;
            push(newStack, newElement);
            while(b -> top != NULL) {
                if(newElement == b -> top -> data) {
                    pop(b);
                } else {
                    break;
                }
            }
        } else if(b -> top == NULL && a -> top != NULL) {
            newElement = a -> top -> data;
            push(newStack, newElement);
            while(a -> top != NULL) {
                if(newElement == a -> top -> data) {
                    pop(a);
                } else {
                    break;
                }
            }
        } else {
            newElement = min(b -> top -> data, a -> top -> data);
            push(newStack, newElement);
            while(a -> top != NULL) {
                if(newElement == a -> top -> data) {
                    pop(a);
                } else {
                    break;
                }
            }
            while(b -> top != NULL) {
                if(newElement == b -> top -> data) {
                    pop(b);
                } else {
                    break;
                }
            }
        }
    }
    return newStack;
}

void StackinTheStack(Stack *myStack) {
    while(true) {
        printf("1.Add Element\n");
        printf("2.Stop\n");
        int command = getInt();
        switch (command) {
            case 1:
                push(myStack, getInt());
                break;
            case 2:
                return;
                break;
            default:
                printf("Invalid command, try again\n");
        }
    }
}

void deleteStack(Stack *stack) {
    while(stack -> len != 0) {
        pop(stack);
    }
    free(stack);
}

int main() {
    
    Stack *stack1 = malloc(sizeof(Stack));
    Stack *stack2 = malloc(sizeof(Stack));
    
    init(stack1);
    init(stack2);
    
    printf("Add elements in stack N1\n");
    StackinTheStack(stack1);
    printf("Add elements in stack N2\n");
    StackinTheStack(stack2);
    
    printf("Elements of stack N1\n");
    show(stack1);
    printf("Elements of stack N2\n");
    show(stack2);
    
    Stack *stack = mergeStacks(stack1, stack2);
    
    printf("Elements of new stack\n");
    show(stack);
    
    deleteStack(stack);
    deleteStack(stack1);
    deleteStack(stack2);
    
    return 0;
}
