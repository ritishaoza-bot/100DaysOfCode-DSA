/*Given an undirected connected graph with V vertices and adjacency list adj. You are required to find all the vertices removing which (and edges through it) disconnects the graph into 2 or more components and return it in sorted manner.
Note: Indexing is zero-based i.e nodes numbering from (0 to V-1). There might be loops present in the graph.

Example 1:

Input:

Output:{1,4}
Explanation: Removing the vertex 1 will
discconect the graph as-

Removing the vertex 4 will disconnect the
graph as-

 

Your Task:
You don't need to read or print anything. Your task is to complete the function articulationPoints() which takes V and adj as input parameters and returns a list containing all the vertices removing which turn the graph into two or more disconnected components in sorted order. If there are no such vertices then returns a list containing -1.
 

Expected Time Complexity: O(V + E)
Expected Auxiliary Space: O(V)
 

Constraints:
1 ≤ V ≤ 105*/

#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct Node {
    int data;
    struct Node* next;
};

void addEdge(struct Node** adj, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

void dfs(int u, int p, int *timer, int disc[], int low[], int vis[], int isPoint[], struct Node** adj) {
    vis[u] = 1;
    disc[u] = low[u] = ++(*timer);
    int children = 0;
    struct Node* temp = adj[u];
    while (temp != NULL) {
        int v = temp->data;
        if (v == p) {
            temp = temp->next;
            continue;
        }
        if (vis[v]) {
            low[u] = MIN(low[u], disc[v]);
        } else {
            dfs(v, u, timer, disc, low, vis, isPoint, adj);
            low[u] = MIN(low[u], low[v]);
            if (low[v] >= disc[u] && p != -1) isPoint[u] = 1;
            children++;
        }
        temp = temp->next;
    }
    if (p == -1 && children > 1) isPoint[u] = 1;
}

int main() {
    int V = 5;
    struct Node** adj = (struct Node**)calloc(V, sizeof(struct Node*));
    
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);
    addEdge(adj, 3, 4);
    addEdge(adj, 0, 4);

    int* disc = (int*)malloc(V * sizeof(int));
    int* low = (int*)malloc(V * sizeof(int));
    int* vis = (int*)calloc(V, sizeof(int));
    int* isPoint = (int*)calloc(V, sizeof(int));
    int timer = 0;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs(i, -1, &timer, disc, low, vis, isPoint, adj);
    }

    int found = 0;
    for (int i = 0; i < V; i++) {
        if (isPoint[i]) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found) printf("-1");
    printf("\n");

    return 0;
}