/*Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
 

Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int top;
} Stack;

Stack* createStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (int*)malloc(capacity * sizeof(int));
    s->top = -1;
    return s;
}

void stackPush(Stack* s, int x) {
    s->data[++(s->top)] = x;
}

int stackPop(Stack* s) {
    return s->data[(s->top)--];
}

int stackPeek(Stack* s) {
    return s->data[s->top];
}

bool stackEmpty(Stack* s) {
    return s->top == -1;
}

typedef struct {
    Stack* input;
    Stack* output;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->input = createStack(100);
    obj->output = createStack(100);
    return obj;
}

void myQueuePush(MyQueue* obj, int x) {
    stackPush(obj->input, x);
}

int myQueuePop(MyQueue* obj) {
    if (stackEmpty(obj->output)) {
        while (!stackEmpty(obj->input)) {
            stackPush(obj->output, stackPop(obj->input));
        }
    }
    return stackPop(obj->output);
}

int myQueuePeek(MyQueue* obj) {
    if (stackEmpty(obj->output)) {
        while (!stackEmpty(obj->input)) {
            stackPush(obj->output, stackPop(obj->input));
        }
    }
    return stackPeek(obj->output);
}

bool myQueueEmpty(MyQueue* obj) {
    return stackEmpty(obj->input) && stackEmpty(obj->output);
}

void myQueueFree(MyQueue* obj) {
    free(obj->input->data);
    free(obj->input);
    free(obj->output->data);
    free(obj->output);
    free(obj);
}

int main() {
    MyQueue* q = myQueueCreate();
    myQueuePush(q, 1);
    myQueuePush(q, 2);
    printf("%d\n", myQueuePeek(q)); 
    printf("%d\n", myQueuePop(q));  
    printf("%s\n", myQueueEmpty(q) ? "true" : "false");
    myQueueFree(q);
    return 0;
}