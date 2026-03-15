/*Problem Statement:
Given a queue of integers, reverse the queue using a stack.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers

Output Format:
- Print the reversed queue

Example:
Input:
5
10 20 30 40 50

Output:
50 40 30 20 10*/

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int *array;
    int front, rear, size, capacity;
};

struct Stack {
    int *array;
    int top, capacity;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void enqueue(struct Queue* queue, int item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

int main() {
    int n, temp;
    if (scanf("%d", &n) != 1) return 0;

    struct Queue* queue = createQueue(n);
    struct Stack* stack = createStack(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        enqueue(queue, temp);
    }

    while (queue->size > 0) {
        push(stack, dequeue(queue));
    }

    while (stack->top != -1) {
        enqueue(queue, pop(stack));
    }

    for (int i = 0; i < n; i++) {
        printf("%d%s", dequeue(queue), (i == n - 1) ? "" : " ");
    }
    printf("\n");

    free(queue->array);
    free(queue);
    free(stack->array);
    free(stack);

    return 0;
}