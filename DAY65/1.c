/*Problem: Using DFS and parent tracking, detect if undirected graph has a cycle.

Output:
- YES or NO.*/

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

    node = createNode(u);
    node->next = g->adj[v];
    g->adj[v] = node;
}

bool dfsCycle(struct Graph* g, int v, int parent, bool* visited) {
    visited[v] = true;
    struct Node* temp = g->adj[v];

    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            if (dfsCycle(g, neighbor, v, visited))
                return true;
        } else if (neighbor != parent) {
            return true;
        }
        temp = temp->next;
    }
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
    bool hasCycle = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCycle(&g, i, -1, visited)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) printf("YES\n");
    else printf("NO\n");

    free(visited);
    return 0;
}