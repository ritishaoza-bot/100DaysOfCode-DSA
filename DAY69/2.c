/*You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

 

Example 1:


Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
 

Constraints:

1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
All the pairs (ui, vi) are unique. (i.e., no multiple edges.)*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int to;
    int weight;
} Edge;

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    int dist[101];
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[k] = 0;

    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < timesSize; j++) {
            int u = times[j][0];
            int v = times[j][1];
            int w = times[j][2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }

    int maxWait = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        if (dist[i] > maxWait) maxWait = dist[i];
    }
    return maxWait;
}

int main() {
    int row1[] = {2, 1, 1};
    int row2[] = {2, 3, 1};
    int row3[] = {3, 4, 1};
    int* times[] = {row1, row2, row3};
    int timesColSize[] = {3, 3, 3};
    
    int result = networkDelayTime(times, 3, timesColSize, 4, 2);
    printf("Result: %d\n", result);
    
    return 0;
}