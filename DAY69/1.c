/*Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int node;
    int dist;
} Element;

typedef struct {
    Element* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->data = (Element*)malloc(sizeof(Element) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(Element* a, Element* b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* h, int node, int dist) {
    h->data[h->size].node = node;
    h->data[h->size].dist = dist;
    int i = h->size++;
    while (i != 0 && h->data[(i - 1) / 2].dist > h->data[i].dist) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Element pop(MinHeap* h) {
    Element root = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int smallest = 2 * i + 1;
        if (smallest + 1 < h->size && h->data[smallest + 1].dist < h->data[smallest].dist)
            smallest++;
        if (h->data[i].dist <= h->data[smallest].dist) break;
        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
    return root;
}

void dijkstra(int n, int adj[n+1][n+1], int src) {
    int dist[n + 1];
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    MinHeap* pq = createHeap(n * n);
    push(pq, src, 0);

    while (pq->size > 0) {
        Element top = pop(pq);
        int u = top.node;
        int d = top.dist;

        if (d > dist[u]) continue;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != -1) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    push(pq, v, dist[v]);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) printf("Node %d: Unreachable\n", i);
        else printf("Node %d: %d\n", i, dist[i]);
    }

    free(pq->data);
    free(pq);
}

int main() {
    int n = 4;
    int adj[5][5];
    for(int i=0; i<=n; i++)
        for(int j=0; j<=n; j++) adj[i][j] = -1;

    adj[1][2] = 1;
    adj[1][3] = 4;
    adj[2][3] = 2;
    adj[2][4] = 6;
    adj[3][4] = 3;

    dijkstra(n, adj, 1);
    return 0;
}