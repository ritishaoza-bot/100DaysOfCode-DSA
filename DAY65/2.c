/*Given an undirected graph with V vertices and E edges, represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes an edge between vertices u and v, determine whether the graph contains a cycle or not.

Note: The graph can have multiple component.

Examples:

Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: true
Explanation: 
 
1 -> 2 -> 0 -> 1 is a cycle.
Input: V = 4, E = 3, edges[][] = [[0, 1], [1, 2], [2, 3]]
Output: false
Explanation: 
 
No cycle in the graph.
Constraints:
1 ≤ V, E ≤ 105
0 ≤ edges[i][0], edges[i][1] < V
*/

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

bool hasCycleDFS(struct Graph* g, int v, int parent, bool* visited) {
    visited[v] = true;
    struct Node* temp = g->adj[v];

    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            if (hasCycleDFS(g, neighbor, v, visited))
                return true;
        } else if (neighbor != parent) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int main() {
    int V = 4, E = 4;
    struct Graph g;
    g.V = V;
    g.adj = malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) g.adj[i] = NULL;

    int edges[4][2] = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    for (int i = 0; i < E; i++) {
        addEdge(&g, edges[i][0], edges[i][1]);
    }

    bool* visited = calloc(V, sizeof(bool));
    bool result = false;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (hasCycleDFS(&g, i, -1, visited)) {
                result = true;
                break;
            }
        }
    }

    if (result) printf("true\n");
    else printf("false\n");

    return 0;
}