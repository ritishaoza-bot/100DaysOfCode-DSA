/*You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:


Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
 

Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int minCostConnectPoints(int points[][2], int pointsSize) {
    int min_cost = 0;
    int* dist = (int*)malloc(pointsSize * sizeof(int));
    bool* visited = (bool*)malloc(pointsSize * sizeof(bool));

    for (int i = 0; i < pointsSize; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[0] = 0;

    for (int i = 0; i < pointsSize; i++) {
        int u = -1;
        for (int v = 0; v < pointsSize; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = true;
        min_cost += dist[u];

        for (int v = 0; v < pointsSize; v++) {
            if (!visited[v]) {
                int d = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                if (d < dist[v]) {
                    dist[v] = d;
                }
            }
        }
    }

    free(dist);
    free(visited);
    return min_cost;
}

int main() {
    int points[][2] = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    int size = sizeof(points) / sizeof(points[0]);
    
    int result = minCostConnectPoints(points, size);
    printf("Minimum Cost: %d\n", result);

    return 0;
}