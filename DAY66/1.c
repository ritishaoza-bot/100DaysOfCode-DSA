/*Problem: Detect cycle in directed graph using DFS and recursion stack.

Output:
- YES if cycle exists*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adj;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* g, int u, int v) {
    struct Node* node = createNode(v);
    node->next = g->adj[u];
    g->adj[u] = node;
}

bool dfsCycle(struct Graph* g, int v, bool* visited, bool* recStack) {
    visited[v] = true;
    recStack[v] = true;

    struct Node* temp = g->adj[v];
    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            if (dfsCycle(g, neighbor, visited, recStack))
                return true;
        } else if (recStack[neighbor]) {
            return true;
        }
        temp = temp->next;
    }

    recStack[v] = false;
    return false;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    struct Graph g;
    g.V = n;
    g.adj = malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) g.adj[i] = NULL;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    bool* visited = calloc(n, sizeof(bool));
    bool* recStack = calloc(n, sizeof(bool));
    bool hasCycle = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCycle(&g, i, visited, recStack)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) printf("YES\n");
    else printf("NO\n");

    free(visited);
    free(recStack);
    return 0;
}