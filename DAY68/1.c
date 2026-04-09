/*Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void kahn(int n, int adj[MAX][MAX]) {
    int indegree[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int result[MAX], k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j]) {
                indegree[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        result[k++] = u;

        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (k != n) {
        printf("Cycle detected\n");
        return;
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int n, e;
    int adj[MAX][MAX] = {0};

    if (scanf("%d %d", &n, &e) != 2) return 0;

    for (int i = 0; i < e; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            adj[u][v] = 1;
        }
    }

    kahn(n, adj);

    return 0;
}