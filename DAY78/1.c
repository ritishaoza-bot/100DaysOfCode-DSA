/*Problem Statement
Given weighted undirected graph, compute total weight of Minimum Spanning Tree using Prim’s algorithm.

Input Format
n m
u v w
...

Output Format
Total weight of MST.

Sample Input
4 5
1 2 3
1 3 5
2 3 1
2 4 4
3 4 2

Sample Output
6

Explanation
One possible MST edges: (2-3), (3-4), (1-2)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

int findMinKey(int key[], bool mstSet[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(int **graph, int n) {
    int key[n];
    bool mstSet[n];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0; 
    int totalWeight = 0;

    for (int count = 0; count < n; count++) {
        int u = findMinKey(key, mstSet, n);
        mstSet[u] = true;
        totalWeight += key[u];

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
            }
        }
    }

    printf("%d\n", totalWeight);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)calloc(n, sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        // Adjusting 1-based indexing to 0-based
        graph[u-1][v-1] = w;
        graph[v-1][u-1] = w;
    }

    primMST(graph, n);

    for (int i = 0; i < n; i++) free(graph[i]);
    free(graph);

    return 0;
}