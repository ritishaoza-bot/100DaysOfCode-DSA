/*Problem Statement:
Implement a Priority Queue using an array. An element with smaller value has higher priority.

Supported Operations:
- insert x
- delete
- peek

Input Format:
- First line contains integer N
- Next N lines contain operations

Output Format:
- Print the deleted or peeked element
- Print -1 if the queue is empty

Example:
Input:
5
insert 30
insert 10
insert 20
delete
peek

Output:
10
20*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (int*)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue* pq, int x) {
    if (pq->size == pq->capacity) return;
    pq->data[pq->size] = x;
    int i = pq->size;
    pq->size++;
    while (i != 0 && pq->data[(i - 1) / 2] > pq->data[i]) {
        swap(&pq->data[i], &pq->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void minHeapify(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < pq->size && pq->data[left] < pq->data[smallest])
        smallest = left;
    if (right < pq->size && pq->data[right] < pq->data[smallest])
        smallest = right;
    if (smallest != i) {
        swap(&pq->data[i], &pq->data[smallest]);
        minHeapify(pq, smallest);
    }
}

int deleteMin(PriorityQueue* pq) {
    if (pq->size <= 0) return -1;
    if (pq->size == 1) {
        pq->size--;
        return pq->data[0];
    }
    int root = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    minHeapify(pq, 0);
    return root;
}

int peek(PriorityQueue* pq) {
    if (pq->size <= 0) return -1;
    return pq->data[0];
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    PriorityQueue* pq = createQueue(n);
    char op[10];
    int val;

    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (strcmp(op, "insert") == 0) {
            scanf("%d", &val);
            insert(pq, val);
        } else if (strcmp(op, "delete") == 0) {
            printf("%d\n", peek(pq));
        }
    }

    free(pq->data);
    free(pq);
    return 0;
}