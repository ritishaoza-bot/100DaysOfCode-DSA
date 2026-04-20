/*Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges. The graph is represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes a direct edge from vertex u to v. Find the number of strongly connected components in the graph.

Examples:

Input: V = 5, E = 5, edges[][] = [[0, 2], [0, 3], [1, 0], [2, 1], [3, 4]]


Output: 3
Explanation: We can clearly see that there are 3 Strongly Connected Components in the Graph.
 
Input: V = 3, E = 3, edges[][] = [[0, 1], [1, 2], [2, 0]]

Output: 1
Explanation: All of the nodes are connected to each other. So, there's only one SCC.
Input: V = 2, E = 1, edges[][] = [[0, 1]]
Output: 2
Constraints:
1 ≤ V ≤ 106
0 ≤ E ≤ 106
0 ≤ edges[i][0], edges[i][1] < V

 */

 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int dest;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adj;
};

struct Node* createNode(int d) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = d;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;
}

void dfs1(int v, struct Graph* g, bool visited[], int stack[], int* top) {
    visited[v] = true;
    struct Node* temp = g->adj[v];
    while (temp) {
        if (!visited[temp->dest]) dfs1(temp->dest, g, visited, stack, top);
        temp = temp->next;
    }
    stack[++(*top)] = v;
}

void dfs2(int v, struct Graph* g, bool visited[]) {
    visited[v] = true;
    struct Node* temp = g->adj[v];
    while (temp) {
        if (!visited[temp->dest]) dfs2(temp->dest, g, visited);
        temp = temp->next;
    }
}

int countSCCs(int V, int E, int edges[][2]) {
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
    struct Graph* gr = (struct Graph*)malloc(sizeof(struct Graph));
    g->V = V; gr->V = V;
    g->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    gr->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    
    for (int i = 0; i < V; i++) {
        g->adj[i] = NULL;
        gr->adj[i] = NULL;
    }

    for (int i = 0; i < E; i++) {
        addEdge(g, edges[i][0], edges[i][1]);
        addEdge(gr, edges[i][1], edges[i][0]);
    }

    bool* visited = (bool*)calloc(V, sizeof(bool));
    int* stack = (int*)malloc(V * sizeof(int));
    int top = -1;

    for (int i = 0; i < V; i++)
        if (!visited[i]) dfs1(i, g, visited, stack, &top);

    for (int i = 0; i < V; i++) visited[i] = false;

    int count = 0;
    while (top != -1) {
        int v = stack[top--];
        if (!visited[v]) {
            dfs2(v, gr, visited);
            count++;
        }
    }

    return count;
}

int main() {
    int V = 5, E = 5;
    int edges[5][2] = {{0, 2}, {0, 3}, {1, 0}, {2, 1}, {3, 4}};
    printf("%d\n", countSCCs(V, E, edges));
    return 0;
}