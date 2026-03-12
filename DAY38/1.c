/*Problem: Deque (Double-Ended Queue)

A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

Common Operations:
1. push_front(value): Insert an element at the front of the deque.
2. push_back(value): Insert an element at the rear of the deque.
3. pop_front(): Remove an element from the front of the deque.
4. pop_back(): Remove an element from the rear of the deque.
5. front(): Return the front element of the deque.
6. back(): Return the rear element of the deque.
7. empty(): Check whether the deque is empty.
8. size(): Return the number of elements in the deque.

Additional Operations:
- clear(): Remove all elements from the deque.
- erase(): Remove one or more elements from the deque.
- swap(): Swap contents of two deques.
- emplace_front(): Insert an element at the front without copying.
- emplace_back(): Insert an element at the rear without copying.
- resize(): Change the size of the deque.
- assign(): Replace elements with new values.
- reverse(): Reverse the order of elements.
- sort(): Sort the elements in ascending order.

Time Complexity:
- push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
- clear, erase, resize, assign, reverse: O(n)
- sort: O(n log n)

Input:
- Sequence of deque operations with values (if applicable)

Output:
- Results of operations such as front, back, size, or the final state of the deque after all operations*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int count;
} Deque;

Deque* createDeque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->front = dq->rear = NULL;
    dq->count = 0;
    return dq;
}

bool empty(Deque* dq) {
    return dq->count == 0;
}

int size(Deque* dq) {
    return dq->count;
}

void push_front(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = dq->front;

    if (empty(dq)) {
        dq->rear = newNode;
    } else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
    dq->count++;
}

void push_back(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dq->rear;

    if (empty(dq)) {
        dq->front = newNode;
    } else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
    dq->count++;
}

void pop_front(Deque* dq) {
    if (empty(dq)) return;
    Node* temp = dq->front;
    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    free(temp);
    dq->count--;
}

void pop_back(Deque* dq) {
    if (empty(dq)) return;
    Node* temp = dq->rear;
    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    free(temp);
    dq->count--;
}

int front(Deque* dq) {
    if (empty(dq)) return -1;
    return dq->front->data;
}

int back(Deque* dq) {
    if (empty(dq)) return -1;
    return dq->rear->data;
}

void clear(Deque* dq) {
    while (!empty(dq)) {
        pop_front(dq);
    }
}

void reverse(Deque* dq) {
    if (empty(dq)) return;
    Node* curr = dq->front;
    Node* temp = NULL;
    dq->rear = dq->front;
    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        dq->front = curr;
        curr = curr->prev;
    }
}

int main() {
    Deque* dq = createDeque();

    push_back(dq, 10);
    push_back(dq, 20);
    push_front(dq, 5);

    printf("Front: %d\n", front(dq));
    printf("Back: %d\n", back(dq));
    printf("Size: %d\n", size(dq));

    reverse(dq);
    printf("After Reverse - Front: %d, Back: %d\n", front(dq), back(dq));

    pop_front(dq);
    printf("After Pop Front - Front: %d\n", front(dq));

    clear(dq);
    printf("Is empty: %s\n", empty(dq) ? "Yes" : "No");

    free(dq);
    return 0;
}