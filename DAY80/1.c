/*Problem: Given a weighted graph with n vertices, implement the Floyd-Warshall algorithm to compute the shortest distances between every pair of vertices. The graph may contain positive or negative edge weights, but it does not contain any negative weight cycles.

Input:
- First line: integer n representing the number of vertices
- Next n lines: n space-separated integers representing the adjacency matrix of the graph
  (use -1 to indicate no direct edge between two vertices)

Output:
- Print the shortest distance matrix where the value at row i and column j represents the shortest distance from vertex i to vertex j

Example:
Input:
4
0 5 -1 10
-1 0 3 -1
-1 -1 0 1
-1 -1 -1 0

Output:
0 5 8 9
-1 0 3 4
-1 -1 0 1
-1 -1 -1 0

Explanation:
The Floyd-Warshall algorithm works by considering each vertex as an intermediate point and updating the shortest paths between all pairs of vertices. For example, the shortest path from vertex 1 to vertex 3 is improved via vertex 2 with total cost 8. This process is repeated for all vertices, resulting in the final shortest distance matrix.*/

#include <stdio.h>
#include <stdlib.h>

void floydWarshall(int n, int **dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    int newDist = dist[i][k] + dist[k][j];
                    if (dist[i][j] == -1 || newDist < dist[i][j]) {
                        dist[i][j] = newDist;
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int **dist = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    floydWarshall(n, dist);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", dist[i][j], j == n - 1 ? '\n' : ' ');
        }
    }

    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);

    return 0;
}