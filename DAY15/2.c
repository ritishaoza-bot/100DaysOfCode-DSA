/*Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

 

Example 1:


Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Example 2:


Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 

Constraints:

m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-231 <= matrix[i][j] <= 231 - 1*/

#include <stdio.h>
#include <stdlib.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    int n = matrixColSize[0];
    int col0 = 1;

    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) col0 = 0;
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 1; j--) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
        if (col0 == 0) matrix[i][0] = 0;
    }
}

int main() {
    int m = 3, n = 3;
    int* matrixColSize = (int*)malloc(sizeof(int) * m);
    int** matrix = (int**)malloc(sizeof(int*) * m);

    int data[3][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * n);
        matrixColSize[i] = n;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = data[i][j];
        }
    }

    setZeroes(matrix, m, matrixColSize);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++) free(matrix[i]);
    free(matrix);
    free(matrixColSize);

    return 0;
}