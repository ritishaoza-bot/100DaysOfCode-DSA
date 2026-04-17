/*Problem Statement
Using DFS or BFS, count number of connected components.

Input Format
n m
edges

Output Format
Number of connected components.

Sample Input
6 3
1 2
2 3
5 6

Sample Output
3

Explanation
Components: {1,2,3}, {4}, {5,6}*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int dest;
    struct Node* next;
};

void dfs(int u, struct Node** adj, int* visited) {
    visited[u] = 1;
    struct Node* curr = adj[u];
    while (curr) {
        if (!visited[curr->dest]) {
            dfs(curr->dest, adj, visited);
        }
        curr = curr->next;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    struct Node** adj = (struct Node**)calloc(n + 1, sizeof(struct Node*));
    int* visited = (int*)calloc(n + 1, sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        struct Node* newNodeV = (struct Node*)malloc(sizeof(struct Node));
        newNodeV->dest = v;
        newNodeV->next = adj[u];
        adj[u] = newNodeV;

        struct Node* newNodeU = (struct Node*)malloc(sizeof(struct Node));
        newNodeU->dest = u;
        newNodeU->next = adj[v];
        adj[v] = newNodeU;
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i, adj, visited);
        }
    }

    printf("%d\n", count);

    for (int i = 1; i <= n; i++) {
        struct Node* curr = adj[i];
        while (curr) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adj);
    free(visited);

    return 0;
}