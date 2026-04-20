/*Problem Statement
Find shortest distances from source vertex in a weighted graph with non-negative weights.

Input Format
n m
u v w
source

Output Format
Distances to all vertices.

Sample Input
5 6
1 2 2
1 3 4
2 3 1
2 4 7
3 5 3
4 5 1
1

Sample Output
0 2 3 9 6

Explanation
Shortest distances computed via priority queue.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return minHeap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left].dist < minHeap->array[smallest].dist) smallest = left;
    if (right < minHeap->size && minHeap->array[right].dist < minHeap->array[smallest].dist) smallest = right;
    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void push(MinHeap* minHeap, int v, int dist) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i].v = v;
    minHeap->array[i].dist = dist;
    while (i && minHeap->array[i].dist < minHeap->array[(i - 1) / 2].dist) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode pop(MinHeap* minHeap) {
    HeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    Node** adj = (Node**)malloc((n + 1) * sizeof(Node*));
    for (int i = 1; i <= n; i++) adj[i] = NULL;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Node* newNode = createNode(v, w);
        newNode->next = adj[u];
        adj[u] = newNode;
    }
    int source;
    scanf("%d", &source);
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[source] = 0;
    MinHeap* pq = createMinHeap(m * 2);
    push(pq, source, 0);
    while (pq->size != 0) {
        HeapNode top = pop(pq);
        int u = top.v;
        int d = top.dist;
        if (d > dist[u]) continue;
        Node* temp = adj[u];
        while (temp) {
            if (dist[u] + temp->weight < dist[temp->dest]) {
                dist[temp->dest] = dist[u] + temp->weight;
                push(pq, temp->dest, dist[temp->dest]);
            }
            temp = temp->next;
        }
    }
    for (int i = 1; i <= n; i++) printf("%d ", dist[i]);
    printf("\n");
    return 0;
}