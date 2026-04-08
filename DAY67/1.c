/*Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS. */

#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0
#define VISITING 1
#define VISITED 2

int has_cycle = 0;

void dfs(int u, int numCourses, int** adj, int* adjSize, int* visited, int* stack, int* top) {
    if (has_cycle) return;

    visited[u] = VISITING;

    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (visited[v] == VISITING) {
            has_cycle = 1;
            return;
        }
        if (visited[v] == UNVISITED) {
            dfs(v, numCourses, adj, adjSize, visited, stack, top);
        }
    }

    visited[u] = VISITED;
    stack[(*top)--] = u;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* returnSize) {
    int** adj = (int**)malloc(numCourses * sizeof(int*));
    int* adjSize = (int*)calloc(numCourses, sizeof(int));
    
    int* tempCount = (int*)calloc(numCourses, sizeof(int));
    for (int i = 0; i < prerequisitesSize; i++) {
        tempCount[prerequisites[i][1]]++;
    }
    for (int i = 0; i < numCourses; i++) {
        adj[i] = (int*)malloc(tempCount[i] * sizeof(int));
    }
    free(tempCount);

    int* currentAdjIdx = (int*)calloc(numCourses, sizeof(int));
    for (int i = 0; i < prerequisitesSize; i++) {
        int u = prerequisites[i][1];
        int v = prerequisites[i][0];
        adj[u][currentAdjIdx[u]++] = v;
        adjSize[u]++;
    }
    free(currentAdjIdx);

    int* visited = (int*)calloc(numCourses, sizeof(int));
    int* stack = (int*)malloc(numCourses * sizeof(int));
    int top = numCourses - 1;
    has_cycle = 0;

    for (int i = 0; i < numCourses; i++) {
        if (visited[i] == UNVISITED) {
            dfs(i, numCourses, adj, adjSize, visited, stack, &top);
        }
    }

    for (int i = 0; i < numCourses; i++) free(adj[i]);
    free(adj);
    free(adjSize);
    free(visited);

    if (has_cycle) {
        *returnSize = 0;
        free(stack);
        return NULL;
    }

    *returnSize = numCourses;
    return stack;
}

int main() {
    int numCourses = 4;
    int prerequisitesSize = 4;
    
    int p0[] = {1, 0};
    int p1[] = {2, 0};
    int p2[] = {3, 1};
    int p3[] = {3, 2};
    int* prerequisites[] = {p0, p1, p2, p3};

    int returnSize;
    int* result = findOrder(numCourses, prerequisites, prerequisitesSize, &returnSize);

    if (result == NULL) {
        printf("Cycle detected! No valid topological order.\n");
    } else {
        printf("Topological Order: ");
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}