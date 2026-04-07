/*You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c, t;
} Orange;

int solve(int** grid, int m, int n) {
    int fresh = 0, minutes = 0;
    Orange* queue = malloc(m * n * sizeof(Orange));
    int head = 0, tail = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                queue[tail++] = (Orange){i, j, 0};
            } else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (head < tail) {
        Orange curr = queue[head++];
        minutes = curr.t;

        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                grid[nr][nc] = 2;
                fresh--;
                queue[tail++] = (Orange){nr, nc, curr.t + 1};
            }
        }
    }

    free(queue);
    return fresh == 0 ? minutes : -1;
}

int main() {
    int m = 3, n = 3;
    int** grid = malloc(m * sizeof(int*));
    int data[3][3] = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

    for (int i = 0; i < m; i++) {
        grid[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            grid[i][j] = data[i][j];
        }
    }

    printf("%d\n", solve(grid, m, n));

    for (int i = 0; i < m; i++) free(grid[i]);
    free(grid);
    return 0;
}