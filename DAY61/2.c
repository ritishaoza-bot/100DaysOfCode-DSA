/*There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]*/

#include <stdio.h>
#include <stdlib.h>

void dfs(int** isConnected, int isConnectedSize, int* visited, int i) {
    for (int j = 0; j < isConnectedSize; j++) {
        if (isConnected[i][j] == 1 && !visited[j]) {
            visited[j] = 1;
            dfs(isConnected, isConnectedSize, visited, j);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int* visited = (int*)calloc(isConnectedSize, sizeof(int));
    int provinces = 0;

    for (int i = 0; i < isConnectedSize; i++) {
        if (!visited[i]) {
            dfs(isConnected, isConnectedSize, visited, i);
            provinces++;
        }
    }

    free(visited);
    return provinces;
}

int main() {
    int n = 3;
    int* isConnected[3];
    int row1[] = {1, 1, 0};
    int row2[] = {1, 1, 0};
    int row3[] = {0, 0, 1};
    isConnected[0] = row1;
    isConnected[1] = row2;
    isConnected[2] = row3;

    int colSize = 3;
    printf("Total Provinces: %d\n", findCircleNum(isConnected, n, &colSize));

    return 0;
}